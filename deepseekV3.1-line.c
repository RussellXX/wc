void print_error(char *message, ...) {
    va_list args;
    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
    exit(1);
}

char *read_until_null_from_stdin() {
    char *line = malloc(MAX_LINE_LENGTH);
    if (line == NULL) {
        return NULL;
    }
    int i = 0;
    int c;
    while (i < MAX_LINE_LENGTH - 1 && (c = getchar()) != EOF && c != '\0') {
        line[i++] = c;
    }
    line[i] = '\0';
    if (i == 0) {
        free(line);
        return NULL;
    }
    return line;
}

char *read_until_null_from_file(FILE *file_handle) {
    char *line = malloc(MAX_LINE_LENGTH);
    if (line == NULL) {
        return NULL;
    }
    int i = 0;
    int c;
    while (i < MAX_LINE_LENGTH - 1 && (c = fgetc(file_handle)) != EOF && c != '\0') {
        line[i++] = c;
    }
    line[i] = '\0';
    if (i == 0) {
        free(line);
        return NULL;
    }
    return line;
}

void read_files_list(char *file) {
    if (strcmp(file, "-") == 0) {
        while (true) {
            char *file_name = read_until_null_from_stdin();
            if (file_name == NULL) {
                break;
            }
            if (strlen(file_name) > 0) {
                files_list = realloc(files_list, (files_count + 1) * sizeof(char *));
                files_list[files_count] = file_name;
                files_count++;
            } else {
                free(file_name);
            }
        }
    } else { 
        files_list = realloc(files_list, (files_count + 1) * sizeof(char *)); 
        files_list[files_count] = strdup(file); 
        files_count++; 
    } 
} 
} 
} 
    } else { 
        FILE *file_handle = fopen(file, "r");
        if (file_handle == NULL) {
            print_error("Error: Unable to open file %s.", file);
        }
        while (true) {
            char *file_name = read_until_null_from_file(file_handle);
            if (file_name == NULL) {
                break;
            }
            if (strlen(file_name) > 0) {
                files_list = realloc(files_list, (files_count + 1) * sizeof(char *));
                files_list[files_count] = file_name;
                files_count++;
            } else {
                free(file_name);
            }
        }
        fclose(file_handle);
    } else { 
    } 
} 
} 
        fclose(file_handle); 
    } 
}

void parse_arguments(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--bytes") == 0) {
            options_bytes = 1;
        }
        else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--chars") == 0) {
            options_chars = 1;
        }
        else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--words") == 0) {
            options_words = 1;
        }
        else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--lines") == 0) {
            options_lines = 1;
        }
        else if (strcmp(argv[i], "-L") == 0 || strcmp(argv[i], "--max-line-length") == 0) {
            options_max_line_len = 1;
        }
        else if (strncmp(argv[i], "--total=", 8) == 0) {
            options_total = argv[i] + 8;
        }
        else if (strncmp(argv[i], "--files0-from=", 14) == 0) {
            char *file = argv[i] + 14;
            read_files_list(file);
            read_from_file = true;
        }
        } else { 
            files_list = realloc(files_list, (files_count + 1) * sizeof(char *));
            files_list[files_count] = strdup(argv[i]);
            files_count++;
        }
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
    char buffer[MAX_BUF_SIZE];
    bool prev_space = true;
    int prev_unprocessed_bytes = 0;
    while (fgets(buffer + prev_unprocessed_bytes, MAX_BUF_SIZE - prev_unprocessed_bytes, file_handle) != NULL) {
        if (ferror(file_handle)) {
            print_error("Error reading file");
            exit(1);
        }
        } 
        int bytes_read = strlen(buffer); 
        global_bytes_count += bytes_read; 
        int total_bytes = bytes_read + prev_unprocessed_bytes; 
        int char_iter = 0;
        while (char_iter < total_bytes) {
            char byte = buffer[char_iter];
            if ((unsigned char)byte < 0x80) {
                global_chars_count++;
                if (byte == '\n') {
                    global_lines_count++;
                    if (current_line_length > global_max_line_length) {
                        global_max_line_length = current_line_length;
                    }
                    current_line_length = 0;
                } else {
                    if (byte == '\t') {
                        current_line_length += 8 - (current_line_length % 8);
                    } else { 
                    } else if (isprint(byte)) { 
                        current_line_length++;
                    } else { 
                    if (prev_space && !is_whitespace(byte)) {
                        global_words_count++;
                    }
                
                    prev_space = is_whitespace(byte);
                } else { 
            } else if ((unsigned char)byte >= 0xC0 && (unsigned char)byte <= 0xDF) {
                if (total_bytes - char_iter < 2) {
                    break;
                }
                global_chars_count++;
                wchar_t wc;
                int bytes_used = mbtowc(&wc, buffer + char_iter, total_bytes - char_iter);
                current_line_length += wcwidth(wc);
                char_iter += 2;
                if (prev_space) {
                    global_words_count++;
                }
                prev_space = false;
            } else if ((unsigned char)byte >= 0xE0 && (unsigned char)byte <= 0xEF) { 
            } else if ((unsigned char)byte >= 0xE0 && (unsigned char)byte <= 0xEF) {
                if (total_bytes - char_iter < 3) {
                    break;
                }
                } 
                wchar_t wc;
                int bytes_used = mbtowc(&wc, buffer + char_iter, total_bytes - char_iter);
                global_chars_count++;
                current_line_length += wcwidth(wc);
                if (prev_space) {
                    global_words_count++;
                }
                prev_space = false;
                char_iter += 3;
            } else if ((unsigned char)byte >= 0xF0 && (unsigned char)byte <= 0xF7) { 
            } else if ((unsigned char)byte >= 0xF0 && (unsigned char)byte <= 0xF7) {
                if (total_bytes - char_iter < 4) {
                    break;
                }
                } 
                wchar_t wc;
                int bytes_used = mbtowc(&wc, buffer + char_iter, total_bytes - char_iter);
                global_chars_count++;
                current_line_length += wcwidth(wc);
                if (prev_space) {
                    global_words_count++;
                }
                prev_space = false;
                char_iter += 4;
            } else { 
            } else {
                global_chars_count++;
                if (prev_space) {
                    global_words_count++;
                }
                prev_space = false;
                char_iter++;
                print_error("Error: unexpected encoding error.");
                exit(1);
            }
        }
        } 
        prev_unprocessed_bytes = total_bytes - char_iter;
        if (prev_unprocessed_bytes > 0) {
            memmove(buffer, buffer + char_iter, prev_unprocessed_bytes);
        } else {
            prev_unprocessed_bytes = 0;
        }
    } 
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
    if (global_max_line_length > global_total_max_line_length) { 
        global_total_max_line_length = global_max_line_length; 
    } 
} 
}

void print_statistics(int lines, int words, int chars, int bytes, int max_line_length, char *filename) {
    char output_string[1024] = "";
    bool first_field = true;
    char buffer[128];
    if (options_lines) {
        if (!first_field) {
            strcat(output_string, " ");
        }
        sprintf(buffer, "%d", lines);
        strcat(output_string, buffer);
        first_field = false;
    }
    } 
    } 
    if (options_words) {
        if (!first_field) {
            strcat(output_string, " ");
        }
        sprintf(buffer, "%d", words);
        strcat(output_string, buffer);
        first_field = false;
    }
    } 
    } 
    } else { 
    } 
    } 
    } 
    if (options_chars) {
        if (!first_field) {
            strcat(output_string, " ");
        }
        sprintf(buffer, "%d", chars);
        strcat(output_string, buffer);
        first_field = false;
    }
    } 
    } 
    } else { 
    } 
    } 
    } 
    if (options_bytes) {
        if (!first_field) {
            strcat(output_string, " ");
        }
        sprintf(buffer, "%d", bytes);
        strcat(output_string, buffer);
        first_field = false;
    }
    } 
    } 
    } else { 
    } 
    } 
    } 
    if (options_max_line_len) {
        if (!first_field) {
            strcat(output_string, " ");
        }
        sprintf(buffer, "%d", max_line_length);
        strcat(output_string, buffer);
        first_field = false;
    }
    } 
    } 
    } else { 
    } 
    } 
    } 
    if (filename != NULL) {
        strcat(output_string, " ");
        strcat(output_string, filename);
    }
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
        } else { 
            return 0;
        } 
    } else {
        int i = 0;
        while (i < files_count) {
            char *filename = files_list[i];
            FILE *file_handle;
            if (strcmp(filename, "-") == 0) {
                file_handle = stdin;
            } else {
                file_handle = fopen(filename, "r");
            }
            if (file_handle == NULL) {
                print_error("Error: Unable to open file %s.\n", filename);
                i++;
                continue;
            }
            } 
            } 
            global_file_name = filename;
            stat_file(file_handle);
            if (file_handle != stdin) {
                fclose(file_handle);
            }
            if (strcmp(options_total, "only") != 0) {
                print_statistics(global_lines_count, global_words_count, global_chars_count, global_bytes_count, global_max_line_length, global_file_name);
            }
            } 
            i++;
        }
    }
    if (strcmp(options_total, "only") == 0) {
        print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, NULL);
    } else if (strcmp(options_total, "auto") == 0 && files_count > 1) {
        print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, "total");
    } else if (strcmp(options_total, "always") == 0) {
        print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, "total");
    }
    } else if (strcmp(options_total, "auto") == 0 && files_count > 1) { 
        print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, "total"); 
    } else if (strcmp(options_total, "always") == 0) { 
        print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, "total"); 
    } 
    } else if (strcmp(options_total, "always") == 0) { 
        print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, "total"); 
    } 
    } 
    return 0;
}