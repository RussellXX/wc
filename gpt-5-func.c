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
    size_t i = 0;
    int c;
    while (i < MAX_LINE_LENGTH - 1) {
        c = fgetc(stdin);
        if (c == EOF || c == '\0') {
            break;
        }
        line[i++] = (char)c;
    }
    line[i] = '\0';
    if (i == 0) {
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
    size_t i = 0;
    int c;
    while (i < MAX_LINE_LENGTH - 1) {
        c = fgetc(file_handle);
        if (c == EOF || c == '\0') {
            break;
        }
        line[i++] = (char)c;
    }
    line[i] = '\0';
    if (i == 0) {
        free(line);
        return NULL;
    }
    return line;
}
void read_files_list(const char *file) {
    if (strcmp(file, "-") == 0) {
        while (1) {
            char *file_name = read_until_null_from_stdin();
            if (file_name == NULL) {
                break;
            }
            if (strlen(file_name) > 0) {
                char **new_list = (char **)realloc(files_list, (files_count + 1) * sizeof(char *));
                if (new_list == NULL) {
                    free(file_name);
                    print_error("Error: memory allocation failed for files_list.");
                }
                files_list = new_list;
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
                char **new_list = (char **)realloc(files_list, (files_count + 1) * sizeof(char *));
                if (new_list == NULL) {
                    free(file_name);
                    fclose(file_handle);
                    print_error("Error: memory allocation failed for files_list.");
                }
                files_list = new_list;
                files_list[files_count] = file_name;
                files_count++;
            } else {
                free(file_name);
            }
        }
        fclose(file_handle);
    }
}
void parse_arguments(int argc, char *argv[]) {
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
            const char *file = argv[i] + 14;
            read_files_list(file);
            read_from_file = true;
        } else {
            char **new_list = (char **)realloc(files_list, (files_count + 1) * sizeof(char *));
            if (new_list == NULL) {
                print_error("Error: memory allocation failed for files_list.");
            }
            files_list = new_list;
            files_list[files_count] = argv[i];
            files_count++;
        }
    }
    if (options_bytes == 0 && options_chars == 0 && options_words == 0 && options_lines == 0 && options_max_line_len == 0) {
        options_lines = 1;
        options_words = 1;
        options_bytes = 1;
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

    while (1) {
        size_t bytes_read = fread(buffer + prev_unprocessed_bytes, 1, MAX_BUF_SIZE - prev_unprocessed_bytes, file_handle);
        if (ferror(file_handle)) { 
            print_error("Error: failed reading input.");
        }
        if (bytes_read == 0 && prev_unprocessed_bytes == 0) {
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
                } else if (byte == '\t') {
                    current_line_length += 8 - (current_line_length % 8);
                } else if (isprint((int)byte)) {
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
                int consumed = mbtowc(&wc, (const char *)(buffer + char_iter), 2);
                if (consumed <= 0) {
                    print_error("Error: unexpected encoding error.");
                }
                int w = wcwidth(wc);
                if (w > 0) current_line_length += w;
                char_iter += 2;
                if (prev_space) {
                    global_words_count++;
                }
                prev_space = false;
            } else if (byte >= 0xE0 && byte <= 0xEF) {
                if (total_bytes - char_iter < 3) {
                    break;
                }
                wchar_t wc;
                int consumed = mbtowc(&wc, (const char *)(buffer + char_iter), 3);
                if (consumed <= 0) {
                    print_error("Error: unexpected encoding error.");
                }
                global_chars_count++;
                int w = wcwidth(wc);
                if (w > 0) current_line_length += w;
                if (prev_space) {
                    global_words_count++;
                }
                prev_space = false;
                char_iter += 3;
            } else if (byte >= 0xF0 && byte <= 0xF7) {
                if (total_bytes - char_iter < 4) {
                    break;
                }
                wchar_t wc;
                int consumed = mbtowc(&wc, (const char *)(buffer + char_iter), 4);
                if (consumed <= 0) {
                    print_error("Error: unexpected encoding error.");
                }
                global_chars_count++;
                int w = wcwidth(wc);
                if (w > 0) current_line_length += w;
                if (prev_space) {
                    global_words_count++;
                }
                prev_space = false;
                char_iter += 4;
            } else {
                print_error("Error: unexpected encoding error.");
            }
        }

        prev_unprocessed_bytes = total_bytes - char_iter;
        if (prev_unprocessed_bytes > 0) {
            memmove(buffer, buffer + char_iter, prev_unprocessed_bytes);
        }
        if (current_line_length > global_max_line_length) {
            global_max_line_length = current_line_length;
        }

        if (bytes_read == 0) {
            break;
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
        snprintf(buffer, sizeof(buffer), "%d", words);
        if (first_field) {
            strncat(output_string, buffer, MAX_LINE_LENGTH - strlen(output_string) - 1);
            first_field = false;
        } else {
            strncat(output_string, " ", MAX_LINE_LENGTH - strlen(output_string) - 1);
            strncat(output_string, buffer, MAX_LINE_LENGTH - strlen(output_string) - 1);
        }
    }
    if (options_chars) {
        snprintf(buffer, sizeof(buffer), "%d", chars);
        if (first_field) {
            strncat(output_string, buffer, MAX_LINE_LENGTH - strlen(output_string) - 1);
            first_field = false;
        } else {
            strncat(output_string, " ", MAX_LINE_LENGTH - strlen(output_string) - 1);
            strncat(output_string, buffer, MAX_LINE_LENGTH - strlen(output_string) - 1);
        }
    }
    if (options_bytes) {
        snprintf(buffer, sizeof(buffer), "%d", bytes);
        if (first_field) {
            strncat(output_string, buffer, MAX_LINE_LENGTH - strlen(output_string) - 1);
            first_field = false;
        } else {
            strncat(output_string, " ", MAX_LINE_LENGTH - strlen(output_string) - 1);
            strncat(output_string, buffer, MAX_LINE_LENGTH - strlen(output_string) - 1);
        }
    }
    if (options_max_line_len) {
        snprintf(buffer, sizeof(buffer), "%d", max_line_length);
        if (first_field) {
            strncat(output_string, buffer, MAX_LINE_LENGTH - strlen(output_string) - 1);
            first_field = false;
        } else {
            strncat(output_string, " ", MAX_LINE_LENGTH - strlen(output_string) - 1);
            strncat(output_string, buffer, MAX_LINE_LENGTH - strlen(output_string) - 1);
        }
    }
    if (filename != NULL) {
        strncat(output_string, " ", MAX_LINE_LENGTH - strlen(output_string) - 1);
        strncat(output_string, filename, MAX_LINE_LENGTH - strlen(output_string) - 1);
    }

    printf("%s\n", output_string);
}
int main(int argc, char *argv[]) {
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
            fprintf(stderr, "Error: Unable to open file %s.\n", filename);
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