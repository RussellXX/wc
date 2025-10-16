void print_error(const char *message, ...) {
    va_list args;
    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
    exit(1);
}

char *read_until_null_from_stdin() {
    char *line = (char *)malloc(MAX_LINE_LENGTH);
    if (line == NULL) {
        return NULL;
    }
    int idx = 0;
    int ch;
    while (idx < MAX_LINE_LENGTH - 1) {
        ch = getchar();
        if (ch == EOF) {
            break;
        }
        if ((char)ch == '\0') {
            break;
        }
        line[idx++] = (char)ch;
    }
    line[idx] = '\0';
    if (idx == 0) {
        free(line);
        return NULL;
    }
    return line;
}

char *read_until_null_from_file(FILE *file_handle) {
    char *line = (char *)malloc(MAX_LINE_LENGTH);
    if (line == NULL) {
        return NULL;
    }
    int idx = 0;
    int ch;
    while (idx < MAX_LINE_LENGTH - 1) {
        ch = fgetc(file_handle);
        if (ch == EOF) {
            break;
        }
        if ((char)ch == '\0') {
            break;
        }
        line[idx++] = (char)ch;
    }
    line[idx] = '\0';
    if (idx == 0) {
        free(line);
        return NULL;
    }
    return line;
}

void read_files_list(char *file) {
    if (strcmp(file, "-") == 0) {
        while (1) {
            char *file_name = read_until_null_from_stdin();
            if (file_name == NULL) {
                break;
            }
            if (strlen(file_name) > 0) {
                files_list = realloc(files_list, sizeof(char *) * (files_count + 1));
                files_list[files_count] = file_name;
                files_count++;
            } else {
                free(file_name);
            }
        }
    } else {
        FILE *file_handle = fopen(file, "rb");
        if (file_handle == NULL) {
            print_error("Error: Unable to open file %s.", file); 
        }
        while (1) {
            char *file_name = read_until_null_from_file(file_handle);
            if (file_name == NULL) {
                break;
            }
            if (strlen(file_name) > 0) {
                files_list = realloc(files_list, sizeof(char *) * (files_count + 1));
                files_list[files_count] = file_name;
                files_count++;
            } else {
                free(file_name);
            }
        }
        fclose(file_handle);
    }
}

void parse_arguments(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--bytes") == 0) {
            options_bytes = 1;
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--chars") == 0) {
            options_chars = 1;
        } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--words") == 0) {
            options_words = 1;
        } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--lines") == 0) {
            options_lines = 1;
        } else if (strcmp(argv[i], "-L") == 0 || strcmp(argv[i], "--max-line-length") == 0) {
            options_max_line_len = 1;
        } else if (strncmp(argv[i], "--total=", 8) == 0) {
            options_total = argv[i] + 8;
        } else if (strncmp(argv[i], "--files0-from=", 14) == 0) {
            char *file = argv[i] + 14;
            read_files_list(file);
            read_from_file = true;
        } else {
            files_list = realloc(files_list, sizeof(char *) * (files_count + 1));
            files_list[files_count] = argv[i];
            files_count++;
        }
    }
    if (!options_bytes && !options_chars && !options_words && !options_lines && !options_max_line_len) {
        options_lines = true;
        options_words = true;
        options_bytes = true;
    }
}
void clear_statistics() {
    global_bytes_count = 0;
    global_chars_count = 0;
    global_words_count = 0;
    global_lines_count = 0;
    global_max_line_length = 0;
}

bool is_whitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

void stat_file(FILE *file_handle) {
    clear_statistics();
    setlocale(LC_CTYPE, "");
    unsigned char buffer[MAX_BUF_SIZE];
    bool prev_space = true;
    size_t prev_unprocessed_bytes = 0;

    for (;;) {
        size_t bytes_read = fread(buffer + prev_unprocessed_bytes, 1, MAX_BUF_SIZE - prev_unprocessed_bytes, file_handle);
        
        if (bytes_read == 0) {
            if (ferror(file_handle)) {
                print_error("Error: unexpected read failure.");
            }
            break;
        }

        global_bytes_count += (int)bytes_read;
        size_t total_bytes = bytes_read + prev_unprocessed_bytes;
        size_t char_iter = 0;

        while (char_iter < total_bytes) {
            unsigned char byte = buffer[char_iter];

            if (byte <= 0x7F) {
                global_chars_count++;
                if (byte == '\n') {
                    global_lines_count++;
                    if (current_line_length > global_max_line_length) {
                        global_max_line_length = current_line_length;
                    }
                    current_line_length = 0;
                }
                if (byte == '\t') {
                    current_line_length += 8 - (current_line_length % 8);
                } else if (isprint(byte)) {
                    current_line_length++;
                }
                if (prev_space && !is_whitespace((char)byte)) {
                    global_words_count++;
                }
                prev_space = is_whitespace((char)byte);
                char_iter += 1;
            } else if (byte >= 0xC0 && byte <= 0xDF) {
                if (total_bytes - char_iter < 2) {
                    break;
                }
                global_chars_count++;
                wchar_t wc;
                int consumed = mbtowc(&wc, (const char *)buffer + char_iter, total_bytes - char_iter);
                if (consumed < 0) {
                    print_error("Error: unexpected encoding error.");
                }
                current_line_length += wcwidth(wc);
                char_iter += 2;
                global_words_count += prev_space ? 1 : 0;
                prev_space = false;
            } else if (byte >= 0xE0 && byte <= 0xEF) {
                if (total_bytes - char_iter < 3) {
                    break;
                }
                wchar_t wc;
                int consumed = mbtowc(&wc, (const char *)buffer + char_iter, total_bytes - char_iter);
                if (consumed < 0) {
                    print_error("Error: unexpected encoding error.");
                }
                global_chars_count++;
                current_line_length += wcwidth(wc);
                global_words_count += prev_space ? 1 : 0;
                prev_space = false;
                char_iter += 3;
            } else if (byte >= 0xF0 && byte <= 0xF7) {
                if (total_bytes - char_iter < 4) {
                    break;
                }
                wchar_t wc;
                int consumed = mbtowc(&wc, (const char *)buffer + char_iter, total_bytes - char_iter);
                if (consumed < 0) {
                    print_error("Error: unexpected encoding error.");
                }
                global_chars_count++;
                current_line_length += wcwidth(wc);
                global_words_count += prev_space ? 1 : 0;
                prev_space = false;
                char_iter += 4;
            } else {
                print_error("Error: unexpected encoding error.");
            }
        }

        size_t prev = total_bytes - char_iter;
        if (prev > 0) {
            memmove(buffer, buffer + char_iter, prev);
        }
        prev_unprocessed_bytes = prev;

        if (current_line_length > global_max_line_length) {
            global_max_line_length = current_line_length;
        }
    }

    global_total_bytes += global_bytes_count;
    global_total_chars += global_chars_count;
    global_total_words += global_words_count;
    global_total_lines += global_lines_count;
    if (global_max_line_length > global_total_max_line_length) {
        global_total_max_line_length = global_max_line_length;
    }
}
void print_statistics(int lines, int words, int chars, int bytes, int max_line_length, const char *filename) {
    char output_string[MAX_LINE_LENGTH];
    bool first_field = true;
    char buffer[128];

    output_string[0] = '\0';

    if (options_lines) {
        snprintf(buffer, sizeof(buffer), "%d", lines);
        strncat(output_string, buffer, MAX_LINE_LENGTH - strlen(output_string) - 1);
        first_field = false;
    }
    if (options_words) {
        snprintf(buffer, sizeof(buffer), first_field ? "%d" : " %d", words);
        strncat(output_string, buffer, MAX_LINE_LENGTH - strlen(output_string) - 1);
        first_field = false;
    }
    if (options_chars) {
        snprintf(buffer, sizeof(buffer), first_field ? "%d" : " %d", chars);
        strncat(output_string, buffer, MAX_LINE_LENGTH - strlen(output_string) - 1);
        first_field = false;
    }
    if (options_bytes) {
        snprintf(buffer, sizeof(buffer), first_field ? "%d" : " %d", bytes);
        strncat(output_string, buffer, MAX_LINE_LENGTH - strlen(output_string) - 1);
        first_field = false;
    }
    if (options_max_line_len) {
        snprintf(buffer, sizeof(buffer), first_field ? "%d" : " %d", max_line_length);
        strncat(output_string, buffer, MAX_LINE_LENGTH - strlen(output_string) - 1);
        first_field = false;
    }
    if (filename != NULL) {
        strncat(output_string, " ", MAX_LINE_LENGTH - strlen(output_string) - 1);
        strncat(output_string, filename, MAX_LINE_LENGTH - strlen(output_string) - 1);
    }
    printf("%s\n", output_string);
}
int main(int argc, char **argv) {
    parse_arguments(argc, argv);
    if (files_count == 0) {
        if (!read_from_file) {
            FILE *file_handle;
            file_handle = stdin;
            stat_file(file_handle);
            print_statistics(global_lines_count, global_words_count, global_chars_count, global_bytes_count, global_max_line_length, NULL);
        }
        return 0;
    }
    int i = 0;
    while (i < files_count) {
        char *filename;
        filename = files_list[i];
        FILE *file_handle;
        file_handle = fopen(filename, "r");
        if (file_handle == NULL) {
            PrintError("Error: Unable to open file %s.\n", filename);
            i = i + 1;
            continue;
        }
        global_file_name = filename;
        stat_file(file_handle);
        fclose(file_handle);
        if (strcmp(options_total, "only") != 0) {
            print_statistics(global_lines_count, global_words_count, global_chars_count, global_bytes_count, global_max_line_length, global_file_name);
        }
        i = i + 1;
    }
    if (strcmp(options_total, "only") == 0) {
        print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, NULL);
    } else if (strcmp(options_total, "auto") == 0 && files_count > 1) {
        print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, "total");
    } else if (strcmp(options_total, "always") == 0) {
        print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, "total");
    }
    return 0;
}