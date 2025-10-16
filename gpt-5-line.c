void print_error(char *message, ...) {
    va_list args;
    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
    exit(1);
}

char * read_until_null_from_stdin() {
    char *line = malloc(MAX_LINE_LENGTH);
    if (line == NULL) {
        return NULL;
    }
    size_t i = 0;
    int ch;
    while (i < MAX_LINE_LENGTH) {
        ch = getchar();
        if (ch == EOF || ch == '\0') {
            break;
        }
        line[i++] = (char)ch;
    }
    line[i] = '\0';
    if (i == 0) {
        free(line);
        return NULL;
    }
    return line;
}

char * read_until_null_from_file(FILE *file_handle) {
    char *line = malloc(MAX_LINE_LENGTH);
    if (line == NULL) {
        return NULL;
    }
    size_t i = 0;
    int ch;
    while (i < MAX_LINE_LENGTH) {
        ch = fgetc(file_handle);
        if (ch == EOF || ch == '\0') {
            break;
        }
        line[i++] = (char)ch;
    }
    line[i] = '\0';
    if (i == 0) {
        return NULL; 
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
                files_list = realloc(files_list, sizeof(char*) * (files_count + 1));
                files_list[files_count] = file_name;
                files_count++; 
                files_count++;
}
    } else { 
            else {
                free(file_name);
            }
}
} 
    } else {
        FILE *file_handle = fopen(file, "rb");
        if (file_handle == NULL) {
            print_error("Error: Unable to open file %s.", file); 
        }
} 
            char *file_name = read_until_null_from_file(file_handle);
            if (file_name == NULL) {
                
            }
            } 
            if (strlen(file_name) > 0) {
                files_list = realloc(files_list, sizeof(char*) * (files_count + 1));
                files_list[files_count] = file_name;
                files_count++; 
                files_count++;

            } else {
                
            }
}
} 
        fclose(file_handle);
}
}

void parse_arguments(int argc, char **argv) { 
    for (int i = 1; i <= argc - 1; i++) { 
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--bytes") == 0) { 
} 
            options_bytes = 1; 
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--chars") == 0) { 
} 
} 
        } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--words") == 0) { 
        options_bytes = 1; 
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--chars") == 0) { 
            options_chars = 1; 
        } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--words") == 0) { 
            options_words = 1; 
} 
        } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--lines") == 0) { 
} 
void print_error(char *message, ...) { 
    va_list args; 
    va_start(args, message); 
    vfprintf(stderr, message, args); 
    va_end(args); 
    exit(1); 
} 

char * read_until_null_from_stdin() { 
    char *line = malloc(MAX_LINE_LENGTH); 
    if (line == NULL) { 
        return NULL; 
    } 
    size_t i = 0; 
    int ch; 
    while (i < MAX_LINE_LENGTH) { 
        ch = getchar(); 
        if (ch == EOF || ch == '\0') { 
            break; 
        } 
        line[i++] = (char)ch; 
    } 
    line[i] = '\0'; 
    if (i == 0) { 
        free(line); 
        return NULL; 
    } 
    return line; 
} 

char * read_until_null_from_file(FILE *file_handle) { 
    char *line = malloc(MAX_LINE_LENGTH); 
    if (line == NULL) { 
        return NULL; 
    } 
    size_t i = 0; 
    int ch; 
    while (i < MAX_LINE_LENGTH) { 
        ch = fgetc(file_handle); 
        if (ch == EOF || ch == '\0') { 
            break; 
        } 
        line[i++] = (char)ch; 
    } 
    line[i] = '\0'; 
    if (i == 0) { 
        return NULL; 
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
                files_list = realloc(files_list, sizeof(char*) * (files_count + 1)); 
                files_list[files_count] = file_name; 
                files_count++; 
                files_count++; 
} 
    } else { 
            else { 
                free(file_name); 
            } 
} 
} 
    } else { 
        FILE *file_handle = fopen(file, "rb"); 
        if (file_handle == NULL) { 
            print_error("Error: Unable to open file %s.", file); 
        } 
} 
            char *file_name = read_until_null_from_file(file_handle); 
            if (file_name == NULL) { 
            } 
            } 
            if (strlen(file_name) > 0) { 
                files_list = realloc(files_list, sizeof(char*) * (files_count + 1)); 
                files_list[files_count] = file_name; 
                files_count++; 
                files_count++; 
} 
            } else { 
            } 
} 
} 
        fclose(file_handle); 
} 
} 

void parse_arguments(int argc, char **argv) {
    for (int i = 1; i <= argc - 1; i++) {
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--bytes") == 0) {
} 
            options_bytes = 1;
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--chars") == 0) {
} 
} 
        } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--words") == 0) {
        options_bytes = 1; 
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--chars") == 0) { 
            options_chars = 1; 
        } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--words") == 0) { 
            options_words = 1; 
} 
        } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--lines") == 0) {
} 
        options_lines = 1;
        } else if (strcmp(argv[i], "-L") == 0 || strcmp(argv[i], "--max-line-length") == 0) {
            options_max_line_len = 1;
        } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--total") == 0) { 
            options_total = "only"; 
        } else if (strcmp(argv[i], "--from-file") == 0) { 
            read_from_file = true;
            if (i + 1 <= argc - 1) { 
                read_files_list(argv[i + 1]); 
                i++; 
            } 
            
            
        } else {
            files_list = realloc(files_list, sizeof(char*) * (files_count + 1));
            files_list[files_count] = argv[i];
            files_count++;
        }   
    }   
} 
        } else if (strcmp(argv[i], "-L") == 0 || strcmp(argv[i], "--max-line-length") == 0) { 
            options_max_line_len = 1; 
} 
        } else if (strncmp(argv[i], "--total=", 8) == 0) { 
} 
            options_total = argv[i] + 8; 
} 
        } else if (strncmp(argv[i], "--files0-from=", 14) == 0) { 
        } else if (strcmp(argv[i], "-L") == 0 || strcmp(argv[i], "--max-line-length") == 0) { 
            options_max_line_len = 1; 
} 
        } else if (strncmp(argv[i], "--total=", 8) == 0) { 
} 
            options_total = argv[i] + 8; 
} 
        } else if (strncmp(argv[i], "--files0-from=", 14) == 0) { 
            char *file = argv[i] + 14; 
            read_files_list(file); 
            read_from_file = true; 
} 
        } else { 
            files_list = realloc(files_list, sizeof(char*) * (files_count + 1)); 
            files_list[files_count] = argv[i]; 
            files_count++; 
} 
            files_count++; 
} 
    } 
    if (options_bytes == 0 && options_chars == 0 && options_words == 0 && options_lines == 0 && options_max_line_len == 0) {
        options_lines = true;
        options_words = true;
} 
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
bool is_whitespace(char c) { 
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r'); 
} 
void stat_file(FILE *file_handle) { 
    clear_statistics(); 
    setlocale(LC_CTYPE, ""); 
    char buffer[MAX_BUF_SIZE]; 
} 
} 
    size_t bytes_read; 
    while ((bytes_read = fread(buffer + prev_unprocessed_bytes, 1, MAX_BUF_SIZE - prev_unprocessed_bytes, file_handle)) > 0) { 
        if (ferror(file_handle)) { 
} 
} 
        fprintf(stderr, "Error reading file.\n"); 
        exit(1); 
    } 
} 
        global_bytes_count += bytes_read; 
} 
} 
        while (char_iter < total_bytes) { 
} 
} 
} 
} 
void print_error(char *message, ...) { 
    va_list args; 
    va_start(args, message); 
    vfprintf(stderr, message, args); 
    va_end(args); 
    exit(1); 
} 

char * read_until_null_from_stdin() { 
    char *line = malloc(MAX_LINE_LENGTH); 
    if (line == NULL) { 
        return NULL; 
    } 
    size_t i = 0; 
    int ch; 
    while (i < MAX_LINE_LENGTH) { 
        ch = getchar(); 
        if (ch == EOF || ch == '\0') { 
            break; 
        } 
        line[i++] = (char)ch; 
    } 
    line[i] = '\0'; 
    if (i == 0) { 
        free(line); 
        return NULL; 
    } 
    return line; 
} 

char * read_until_null_from_file(FILE *file_handle) { 
    char *line = malloc(MAX_LINE_LENGTH); 
    if (line == NULL) { 
        return NULL; 
    } 
    size_t i = 0; 
    int ch; 
    while (i < MAX_LINE_LENGTH) { 
        ch = fgetc(file_handle); 
        if (ch == EOF || ch == '\0') { 
            break; 
        } 
        line[i++] = (char)ch; 
    } 
    line[i] = '\0'; 
    if (i == 0) { 
        return NULL; 
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
                files_list = realloc(files_list, sizeof(char*) * (files_count + 1)); 
                files_list[files_count] = file_name; 
                files_count++; 
                files_count++; 
} 
    } else { 
            else { 
                free(file_name); 
            } 
} 
} 
    } else { 
        FILE *file_handle = fopen(file, "rb"); 
        if (file_handle == NULL) { 
            print_error("Error: Unable to open file %s.", file); 
        } 
} 
            char *file_name = read_until_null_from_file(file_handle); 
            if (file_name == NULL) { 
            } 
            } 
            if (strlen(file_name) > 0) { 
                files_list = realloc(files_list, sizeof(char*) * (files_count + 1)); 
                files_list[files_count] = file_name; 
                files_count++; 
                files_count++; 
} 
            } else { 
            } 
} 
} 
        fclose(file_handle); 
} 
} 

void parse_arguments(int argc, char **argv) { 
    for (int i = 1; i <= argc - 1; i++) { 
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--bytes") == 0) { 
} 
            options_bytes = 1; 
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--chars") == 0) { 
} 
} 
        } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--words") == 0) { 
        options_bytes = 1; 
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--chars") == 0) { 
            options_chars = 1; 
        } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--words") == 0) { 
            options_words = 1; 
} 
        } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--lines") == 0) { 
} 
        options_lines = 1; 
        } else if (strcmp(argv[i], "-L") == 0 || strcmp(argv[i], "--max-line-length") == 0) { 
            options_max_line_len = 1; 
        } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--total") == 0) { 
            options_total = "only"; 
        } else if (strcmp(argv[i], "--from-file") == 0) { 
            read_from_file = true; 
            if (i + 1 <= argc - 1) { 
                read_files_list(argv[i + 1]); 
                i++; 
            } 
        } else { 
            files_list = realloc(files_list, sizeof(char*) * (files_count + 1)); 
            files_list[files_count] = argv[i]; 
            files_count++; 
        }    
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

bool is_whitespace(char c) { 
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r'); 
} 

void stat_file(FILE *file_handle) { 
    clear_statistics(); 
    setlocale(LC_CTYPE, ""); 
    char buffer[MAX_BUF_SIZE]; 
} 
    if (current_line_length > global_max_line_length) { 
        global_max_line_length = current_line_length; 
} 
    current_line_length = 0; 
} 
    if (byte == '\t') { 
        } 
        } else { 
            char_iter = 0; 
            while ((bytes_read = fread(buffer + prev_unprocessed_bytes, 1, MAX_BUF_SIZE - prev_unprocessed_bytes, file_handle)) > 0) { 
                if (ferror(file_handle)) { 
                    fprintf(stderr, "Error reading file.\n"); 
                    exit(1); 
                } 
            } 
            global_bytes_count += bytes_read; 
        } 
        char_iter = 0; 
        while (char_iter < total_bytes) { 
            if (current_line_length > global_max_line_length) { 
                global_max_line_length = current_line_length; 
            } 
            current_line_length = 0; 
        } 
        if (byte == '\t') { 
            current_line_length += 8 - (current_line_length % 8); 
        } 
} 
    else if (isprint(byte)) { 
    else if (isprint(byte)) { 
        current_line_length++; 
} 
        if (prev_space && !is_whitespace(byte)) { 
            global_words_count++; 
void print_error(char *message, ...) { 
    va_list args; 
    va_start(args, message); 
    vfprintf(stderr, message, args); 
    va_end(args); 
    exit(1); 
} 

char * read_until_null_from_stdin() { 
    char *line = malloc(MAX_LINE_LENGTH); 
    if (line == NULL) { 
        return NULL; 
    } 
    size_t i = 0; 
    int ch; 
    while (i < MAX_LINE_LENGTH) { 
        ch = getchar(); 
        if (ch == EOF || ch == '\0') { 
            break; 
        } 
        line[i++] = (char)ch; 
    } 
    line[i] = '\0'; 
    if (i == 0) { 
        free(line); 
        return NULL; 
    } 
    return line; 
} 

char * read_until_null_from_file(FILE *file_handle) { 
    char *line = malloc(MAX_LINE_LENGTH); 
    if (line == NULL) { 
        return NULL; 
    } 
    size_t i = 0; 
    int ch; 
    while (i < MAX_LINE_LENGTH) { 
        ch = fgetc(file_handle); 
        if (ch == EOF || ch == '\0') { 
            break; 
        } 
        line[i++] = (char)ch; 
    } 
    line[i] = '\0'; 
    if (i == 0) { 
        return NULL; 
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
                files_list = realloc(files_list, sizeof(char*) * (files_count + 1)); 
                files_list[files_count] = file_name; 
                files_count++; 
                files_count++; 
} 
    } else { 
            else { 
                free(file_name); 
            } 
} 
} 
    } else { 
        FILE *file_handle = fopen(file, "rb"); 
        if (file_handle == NULL) { 
            print_error("Error: Unable to open file %s.", file); 
        } 
} 
            char *file_name = read_until_null_from_file(file_handle); 
            if (file_name == NULL) { 
            } 
            } 
            if (strlen(file_name) > 0) { 
                files_list = realloc(files_list, sizeof(char*) * (files_count + 1)); 
                files_list[files_count] = file_name; 
                files_count++; 
                files_count++; 
} 
            } else { 
            } 
} 
} 
        fclose(file_handle); 
} 
} 

void parse_arguments(int argc, char **argv) { 
    for (int i = 1; i <= argc - 1; i++) { 
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--bytes") == 0) { 
} 
            options_bytes = 1; 
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--chars") == 0) { 
} 
} 
        } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--words") == 0) { 
        options_bytes = 1; 
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--chars") == 0) { 
            options_chars = 1; 
        } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--words") == 0) { 
            options_words = 1; 
} 
        } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--lines") == 0) { 
} 
        options_lines = 1; 
        } else if (strcmp(argv[i], "-L") == 0 || strcmp(argv[i], "--max-line-length") == 0) { 
            options_max_line_len = 1; 
        } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--total") == 0) { 
            options_total = "only"; 
        } else if (strcmp(argv[i], "--from-file") == 0) { 
            read_from_file = true; 
            if (i + 1 <= argc - 1) { 
                read_files_list(argv[i + 1]); 
                i++; 
            } 
        } else { 
            files_list = realloc(files_list, sizeof(char*) * (files_count + 1)); 
            files_list[files_count] = argv[i]; 
            files_count++; 
        }    
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

bool is_whitespace(char c) { 
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r'); 
} 

void stat_file(FILE *file_handle) {
    clear_statistics();
    setlocale(LC_CTYPE, "");
    char buffer[MAX_BUF_SIZE];while (1) { 
        int bytes_read = fread(buffer + prev_unprocessed_bytes, 1, MAX_BUF_SIZE - prev_unprocessed_bytes, file_handle); 
        if (bytes_read < 0) { 
            print_error("Error: Failed to read from file."); 
        } 
        if (bytes_read == 0) { 
            break; 
        } 
        global_bytes_count += bytes_read; 
        int total_bytes = bytes_read + prev_unprocessed_bytes; 
        int char_iter = 0; 
        while (char_iter < total_bytes) { 
            unsigned char byte = buffer[char_iter]; 
            if (byte < 0x80) { 
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
    }
    else if (isprint(byte)) {
        current_line_length++;
    }
        if (prev_space && !is_whitespace(byte)) {
            global_words_count++;
        }
        prev_space = is_whitespace(byte);
        prev_space = is_whitespace(byte); 
        char_iter ++; 
            } 
    else if (byte >= 0xC0 && byte <= 0xDF) { 
        if (total_bytes - char_iter < 2) { 
    else if (byte >= 0xC0 && byte <= 0xDF) {
        if (total_bytes - char_iter < 2) {
            break;
        }
        global_chars_count++;
        wchar_t wc;
        int mb_len = mbtowc(&wc, (const char *)buffer + char_iter, total_bytes - char_iter);
        current_line_length += wcwidth(wc);
        
        prev_space = is_whitespace(byte); 
        
    } else if (byte >= 0xC0 && byte <= 0xDF) { 
        if (total_bytes - char_iter < 2) { 
            break; 
        } 
        global_chars_count++; 
        wchar_t wc; 
        int mb_len = mbtowc(&wc, (const char *)buffer + char_iter, total_bytes - char_iter); 
        current_line_length += wcwidth(wc); 
        char_iter += 2; 
        global_words_count += prev_space; 
        prev_space = is_whitespace(byte); 
    } else if (byte >= 0xC0 && byte <= 0xDF) { 
        if (total_bytes - char_iter < 2) { 
            break; 
        } 
        global_chars_count++; 
        wchar_t wc; 
        int mb_len = mbtowc(&wc, (const char *)buffer + char_iter, total_bytes - char_iter); 
        current_line_length += wcwidth(wc); 
        char_iter += 2; 
        global_words_count += prev_space; 
        prev_space = false; 
        } 
        else if (byte >= 0xE0 && byte <= 0xEF) {
            if (total_bytes - char_iter < 3) {
                break;
            
            global_chars_count++;
            wchar_t wc;
            int mb_len = mbtowc(&wc, (const char *)buffer + char_iter, total_bytes - char_iter);
            current_line_length += wcwidth(wc);
            char_iter += 3;
            global_words_count += prev_space;
            prev_space = false;
        } else if (byte >= 0xF0 && byte <= 0xF4) { 
            if (total_bytes - char_iter < 4) {
                break;
            }
            global_chars_count++;
            wchar_t wc;
            int mb_len = mbtowc(&wc, (const char *)buffer + char_iter, total_bytes - char_iter);
            current_line_length += wcwidth(wc);
            char_iter += 4;
            global_words_count += prev_space;
            prev_space = false;
        } else {
            char_iter++; 
        }
    }

    prev_unprocessed_bytes = MAX_BUF_SIZE - char_iter; 
    if (prev_unprocessed_bytes > 0) {
        memmove(buffer, buffer + char_iter, prev_unprocessed_bytes);
    }
} 
            global_chars_count++; 
            wchar_t wc; 
            int mb_len = mbtowc(&wc, (const char *)buffer + char_iter, total_bytes - char_iter); 
            current_line_length += wcwidth(wc); 
            char_iter += 3; 
            global_words_count += prev_space; 
            prev_space = false; 
            global_chars_count++; 
            current_line_length += wcwidth(wc); 
            wchar_t wc; 
            int mb_len = mbtowc(&wc, (const char *)buffer + char_iter, total_bytes - char_iter); 
            global_chars_count++; 
            current_line_length += wcwidth(wc); 
            global_words_count += prev_space; 
            prev_space = false; 
            char_iter += 3; 
} 
        else if (byte >= 0xF0 && byte <= 0xF7) { 
        else if (byte >= 0xF0 && byte <= 0xF7) { 
            if (total_bytes - char_iter < 4) { 
        else if (byte >= 0xF0 && byte <= 0xF7) { 
            if (total_bytes - char_iter < 4) { 
                break; 
            } 
            current_line_length += wcwidth(wc); 
            wchar_t wc; 
            int mb_len = mbtowc(&wc, (const char *)buffer + char_iter, total_bytes - char_iter); 
            global_chars_count++; 
            wchar_t wc; 
            int mb_len = mbtowc(&wc, (const char *)buffer + char_iter, total_bytes - char_iter); 
            global_chars_count++; 
            current_line_length += wcwidth(wc); 
            global_words_count += prev_space; 
            char_iter += 4; 
            prev_space = false; 
            char_iter += 4; 
} 
            char_iter++; 
            print_error("Error: unexpected encoding error."); 
} 
            } else { 
                print_error("Error: unexpected encoding error."); 
            } 
        } 
        prev_unprocessed_bytes = total_bytes - char_iter; 
            memmove(buffer, buffer + char_iter, prev_unprocessed_bytes); 
        }     
    }     
} 
            memmove(buffer, buffer + char_iter, prev_unprocessed_bytes); 
        } else { 
            memmove(buffer, buffer + char_iter, prev_unprocessed_bytes); 
        } 
    } 
} 
    if (current_line_length > global_max_line_length) {
} 
        global_max_line_length = current_line_length;
}
}
    
    global_total_bytes += global_bytes_count;
    global_total_chars += global_chars_count;
    global_total_words += global_words_count;
    global_total_lines += global_lines_count;
        global_total_max_line_length = global_max_line_length; 
        global_total_max_line_length = global_max_line_length;
}
}

void print_statistics(int lines, int words, int chars, int bytes, int max_line_length, char *filename) {
    char output_string[MAX_LINE_LENGTH];
    output_string[0] = '\0';
    bool first_field = true;

} 
    char buffer[128];
    if (options_lines) {
        snprintf(buffer, sizeof(buffer), "%d", lines);
        strcat(output_string, buffer);
        first_field = false;
}
} 
} 
        if (options_words) {
            if (first_field) {
                snprintf(buffer, sizeof(buffer), "%d", words);
                strcat(output_string, buffer);
                first_field = false;
            } else {
                snprintf(buffer, sizeof(buffer), " %d", words);
                strcat(output_string, buffer);
            }
        }
        first_field = false; 
} 
        } 
        } 
        } 
} 
} 
} 
        if (options_chars) {
            if (first_field) {
                snprintf(buffer, sizeof(buffer), "%d", chars);
                strcat(output_string, buffer);
                first_field = false;
            } else {
                snprintf(buffer, sizeof(buffer), " %d", chars);
                strcat(output_string, buffer);
            }
        }
}  
        first_field = false; 
} 
        snprintf(buffer, sizeof(buffer), " %d", chars); 
        strcat(output_string, buffer); 
        } 
} 
        if (options_bytes) {
            if (first_field) {
                snprintf(buffer, sizeof(buffer), "%d", bytes);
                strcat(output_string, buffer);
                first_field = false;
            } else {
                snprintf(buffer, sizeof(buffer), " %d", bytes);
                strcat(output_string, buffer);
            }
        }
        if (first_field) { 
        } 
        } 
} 
} 
} 
} 
        if (first_field) { 
            snprintf(buffer, sizeof(buffer), "%d", bytes); 
            strcat(output_string, buffer); 
            first_field = false; 
        } else { 
            snprintf(buffer, sizeof(buffer), " %d", bytes); 
            strcat(output_string, buffer); 
        } 

        if (options_max_line_len) {
            if (first_field) {
                snprintf(buffer, sizeof(buffer), "%d", max_line_length);
                strcat(output_string, buffer);
                first_field = false;
            } else {
                snprintf(buffer, sizeof(buffer), " %d", max_line_length);
                strcat(output_string, buffer);
            }
        }
        if (options_max_line_len) { 
            if (first_field) { 
                snprintf(buffer, sizeof(buffer), "%d", max_line_length); 
                strcat(output_string, buffer); 
                first_field = false; 
            } else { 
                snprintf(buffer, sizeof(buffer), " %d", max_line_length); 
                strcat(output_string, buffer); 
            } 
        } 
        first_field = false; 
} 
        snprintf(buffer, sizeof(buffer), " %d", max_line_length); 
        strcat(output_string, buffer); 
} 
} 
} 
    if (filename != NULL) {
        
        
    }
        printf("%s\n", output_string); 
} 
printf("%s\n", output_string);
}

int main(int argc, char **argv) { 
    parse_arguments(argc, argv); 
        print_error("Error: unexpected encoding error."); 
            } else { 
                print_error("Error: unexpected encoding error."); 
            } 
        } 
        prev_unprocessed_bytes = total_bytes - char_iter; 
            memmove(buffer, buffer + char_iter, prev_unprocessed_bytes); 
        }     
    }     
} 
            memmove(buffer, buffer + char_iter, prev_unprocessed_bytes); 
        } else { 
            memmove(buffer, buffer + char_iter, prev_unprocessed_bytes); 
        } 
    } 
} 
    if (current_line_length > global_max_line_length) { 
} 
    if (!read_from_file) { 

        FILE *file_handle; 
        file_handle = stdin; 
        } else { 
            set file_handle = stdin; 
            stat_file(file_handle); 
        } 
    } else { 
        for (int i = 0; i < files_count; i++) { 
            FILE *file_handle = fopen(files_list[i], "rb"); 
            if (file_handle == NULL) { 
                print_error("Error: Unable to open file %s.", files_list[i]); 
            }    
            stat_file(file_handle); 
            fclose(file_handle); 
            if (strcmp(options_total, "only") != 0) { 
                print_statistics(global_lines_count, global_words_count, global_chars_count, global_bytes_count, global_max_line_length, files_list[i]); 
            }    
            global_total_lines += global_lines_count; 
            global_total_words += global_words_count; 
            global_total_chars += global_chars_count; 
            global_total_bytes += global_bytes_count; 
            if (global_max_line_length > global_total_max_line_length) { 
                global_total_max_line_length = global_max_line_length; 
            }    
        } 
        if (strcmp(options_total, "none") != 0) { 
            print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, NULL); 
        } 
    } 

    return 0; 
} 
print_statistics(global_lines_count, global_words_count, global_chars_count, global_bytes_count, global_max_line_length, NULL); 
} 
    return 0; 
} 
int i = 0; 
while (i < files_count) { 
    char *filename; 
    char *filename;  
    filename = files_list[i]; 
} 
    file_handle = fopen(filename, "r"); 
    if (file_handle == NULL) { 
        PrintError("Error: Unable to open file %s.\n", filename); 
        continue; 
        i = i + 1; 
        continue; 
    FILE *file_handle; 
    FILE *file_handle; 
    stat_file(file_handle); 
void print_error(char *message, ...) { 
    va_list args; 
    va_start(args, message); 
    vfprintf(stderr, message, args); 
    va_end(args); 
    exit(1); 
} 

char * read_until_null_from_stdin() { 
    char *line = malloc(MAX_LINE_LENGTH); 
    if (line == NULL) { 
        return NULL; 
    } 
    size_t i = 0; 
    int ch; 
    while (i < MAX_LINE_LENGTH) { 
        ch = getchar(); 
        if (ch == EOF || ch == '\0') { 
            break; 
        } 
        line[i++] = (char)ch; 
    } 
    line[i] = '\0'; 
    if (i == 0) { 
        free(line); 
        return NULL; 
    } 
    return line; 
} 

char * read_until_null_from_file(FILE *file_handle) { 
    char *line = malloc(MAX_LINE_LENGTH); 
    if (line == NULL) { 
        return NULL; 
    } 
    size_t i = 0; 
    int ch; 
    while (i < MAX_LINE_LENGTH) { 
        ch = fgetc(file_handle); 
        if (ch == EOF || ch == '\0') { 
            break; 
        } 
        line[i++] = (char)ch; 
    } 
    line[i] = '\0'; 
    if (i == 0) { 
        return NULL; 
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
                files_list = realloc(files_list, sizeof(char*) * (files_count + 1)); 
                files_list[files_count] = file_name; 
                files_count++; 
                files_count++; 
} 
    } else { 
            else { 
                free(file_name); 
            } 
} 
} 
    } else { 
        FILE *file_handle = fopen(file, "rb"); 
        if (file_handle == NULL) { 
            print_error("Error: Unable to open file %s.", file); 
        } 
} 
            char *file_name = read_until_null_from_file(file_handle); 
            if (file_name == NULL) { 
            } 
            } 
            if (strlen(file_name) > 0) { 
                files_list = realloc(files_list, sizeof(char*) * (files_count + 1)); 
                files_list[files_count] = file_name; 
                files_count++; 
                files_count++; 
} 
            } else { 
            } 
} 
} 
        fclose(file_handle); 
} 
} 

void parse_arguments(int argc, char **argv) { 
    for (int i = 1; i <= argc - 1; i++) { 
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--bytes") == 0) { 
} 
            options_bytes = 1; 
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--chars") == 0) { 
} 
} 
        } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--words") == 0) { 
        options_bytes = 1; 
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--chars") == 0) { 
            options_chars = 1; 
        } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--words") == 0) { 
            options_words = 1; 
} 
        } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--lines") == 0) { 
} 
        options_lines = 1; 
        } else if (strcmp(argv[i], "-L") == 0 || strcmp(argv[i], "--max-line-length") == 0) { 
            options_max_line_len = 1; 
        } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--total") == 0) { 
            options_total = "only"; 
        } else if (strcmp(argv[i], "--from-file") == 0) { 
            read_from_file = true; 
            if (i + 1 <= argc - 1) { 
                read_files_list(argv[i + 1]); 
                i++; 
            } 
        } else { 
            files_list = realloc(files_list, sizeof(char*) * (files_count + 1)); 
            files_list[files_count] = argv[i]; 
            files_count++; 
        }    
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

bool is_whitespace(char c) { 
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r'); 
} 

void stat_file(FILE *file_handle) { 
    clear_statistics(); 
    setlocale(LC_CTYPE, ""); 
    char buffer[MAX_BUF_SIZE]; 
    if (current_line_length > global_max_line_length) { 
        global_max_line_length = current_line_length; 
    } 
    current_line_length = 0; 
    if (byte == '\t') { 
        current_line_length += 8 - (current_line_length % 8); 
    } 
    else if (isprint(byte)) { 
        current_line_length++; 
    } 
        if (prev_space && !is_whitespace(byte))  
            global_words_count++; 
        } 
    prev_space = is_whitespace(byte); 
    prev_space = is_whitespace(byte); 
    } else if (byte >= 0xC0 && byte <= 0xDF) { 
        if (total_bytes - char_iter < 2) { 
            break; 
        } 
        global_chars_count++; 
        wchar_t wc; 
        int mb_len = mbtowc(&wc, (const char *)buffer + char_iter, total_bytes - char_iter); 
        current_line_length += wcwidth(wc); 
        char_iter += 2; 
        global_words_count += prev_space; 
        prev_space = false; 
        } else if (byte >= 0xE0 && byte <= 0xEF) { 
            if (total_bytes - char_iter < 3) { 
                break; 
            } 
            global_chars_count++; 
            wchar_t wc; 
            int mb_len = mbtowc(&wc, (const char *)buffer + char_iter, total_bytes - char_iter); 
            current_line_length += wcwidth(wc); 
            char_iter += 3; 
            global_words_count += prev_space; 
            prev_space = false; 
        } else if (byte >= 0xF0 && byte <= 0xF4) { 
            if (total_bytes - char_iter < 4) { 
                break; 
            } 
            global_chars_count++; 
            wchar_t wc; 
            int mb_len = mbtowc(&wc, (const char *)buffer + char_iter, total_bytes - char_iter); 
            current_line_length += wcwidth(wc); 
            char_iter += 4; 
            global_words_count += prev_space; 
            prev_space = false; 
        } else { 
            char_iter++; 
        } 
    } 

    prev_unprocessed_bytes = MAX_BUF_SIZE - char_iter; 
    if (prev_unprocessed_bytes > 0) { 
        memmove(buffer, buffer + char_iter, prev_unprocessed_bytes); 
    } 
} 

void print_statistics(int lines, int words, int chars, int bytes, int max_line_length, char *filename) { 
    char output_string[MAX_LINE_LENGTH]; 
    output_string[0] = '\0'; 
    bool first_field = true; 
    char buffer[128]; 
    if (options_lines) { 
        snprintf(buffer, sizeof(buffer), "%d", lines); 
        strcat(output_string, buffer); 
        first_field = false; 
    } 
        if (options_words) { 
            if (first_field) { 
                snprintf(buffer, sizeof(buffer), "%d", words); 
                strcat(output_string, buffer); 
                first_field = false; 
            } else { 
                snprintf(buffer, sizeof(buffer), " %d", words); 
                strcat(output_string, buffer); 
            } 
        } 
        first_field = false; 
        }  
        }  
        }  
    if (options_chars) { 
        if (first_field) { 
            snprintf(buffer, sizeof(buffer), "%d", chars); 
            strcat(output_string, buffer); 
            first_field = false; 
        } else { 
            snprintf(buffer, sizeof(buffer), " %d", chars); 
            strcat(output_string, buffer); 
        } 
} 
        first_field = false; 
        snprintf(buffer, sizeof(buffer), " %d", chars); 
        strcat(output_string, buffer); 
        } 
} 
    if (options_bytes) { 
        if (first_field) { 
            snprintf(buffer, sizeof(buffer), "%d", bytes); 
            strcat(output_string, buffer); 
            first_field = false; 
        } else { 
            snprintf(buffer, sizeof(buffer), " %d", bytes); 
            strcat(output_string, buffer); 
        } 
} 
        if (first_field) { 
        }  
        }  
} 
        }  
} 
        if (first_field) { 
            snprintf(buffer, sizeof(buffer), "%d", bytes); 
            strcat(output_string, buffer); 
            first_field = false; 
        } else { 
            snprintf(buffer, sizeof(buffer), " %d", bytes); 
            strcat(output_string, buffer); 
        } 
    if (options_max_line_len) { 
        if (first_field) { 
            snprintf(buffer, sizeof(buffer), "%d", max_line_length); 
            strcat(output_string, buffer); 
            first_field = false; 
        } else { 
            snprintf(buffer, sizeof(buffer), " %d", max_line_length); 
            strcat(output_string, buffer); 
        } 
} 
        if (options_max_line_len) { 
            if (first_field) { 
                snprintf(buffer, sizeof(buffer), "%d", max_line_length); 
                strcat(output_string, buffer); 
                first_field = false; 
            } else { 
                snprintf(buffer, sizeof(buffer), " %d", max_line_length); 
                strcat(output_string, buffer); 
            } 
        } 
        first_field = false; 
        snprintf(buffer, sizeof(buffer), " %d", max_line_length); 
        strcat(output_string, buffer); 
        } 
} 
    if (filename != NULL) { 
    } 
        printf("%s\n", output_string); 
} 

int main(int argc, char **argv) {
    parse_arguments(argc, argv);
    
    if (!read_from_file) { 
        FILE *file_handle;
        file_handle = stdin;
        } else { 
            set file_handle = stdin; 
            stat_file(file_handle);
            
        }
        
    } else {
        for (int i = 0; i < files_count; i++) {
            FILE *file_handle = fopen(files_list[i], "rb");
            if (file_handle == NULL) {
                print_error("Error: Unable to open file %s.", files_list[i]);
            }
            stat_file(file_handle);
            fclose(file_handle);
            if (strcmp(options_total, "only") != 0) {
                print_statistics(global_lines_count, global_words_count, global_chars_count, global_bytes_count, global_max_line_length, files_list[i]);
            }
            global_total_lines += global_lines_count; 
            global_total_words += global_words_count; 
            global_total_chars += global_chars_count; 
            global_total_bytes += global_bytes_count; 
            if (global_max_line_length > global_total_max_line_length) { 
                global_total_max_line_length = global_max_line_length; 
            }    
        }
        if (strcmp(options_total, "none") != 0) { 
            print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, NULL); 
        } 
    } 

    return 0; 
} 
print_statistics(global_lines_count, global_words_count, global_chars_count, global_bytes_count, global_max_line_length, NULL); 
} 
    return 0; 
} 
int i = 0; 
while (i < files_count) { 
    char *filename;  
    filename = files_list[i]; 
    file_handle = fopen(filename, "r"); 
    if (file_handle == NULL) { 
        PrintError("Error: Unable to open file %s.\n", filename); 
        continue; 
        i = i + 1; 
        continue; 
    } 
    
    FILE *file_handle; 
    FILE *file_handle; 
    stat_file(file_handle); 
    fclose(file_handle); 
if (strcmp(options_total, "only") != 0) { 
} 
    print_statistics(global_lines_count, global_words_count, global_chars_count, global_bytes_count, global_max_line_length, global_file_name); 
} 
    if (strcmp(options_total, "only") != 0) { 
        print_statistics(global_lines_count, global_words_count, global_chars_count, global_bytes_count, global_max_line_length, global_file_name); 
    } 
    i = i + 1; 
}
if (strcmp(options_total, "only") == 0) {
    print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, NULL);
}
    print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, NULL); 
} 
    if (strcmp(options_total, "auto") == 0 && files_count > 1) {
        print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, "total");
    }
} 
    print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, "total"); 
} 
    print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, "total"); 
    } else if (strcmp(options_total, "always") == 0) { 
        print_statistics(global_total_lines, global_total_words, global_total_chars, global_total_bytes, global_total_max_line_length, "total"); 
    } 
    return 0;
}