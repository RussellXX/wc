#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>

// 下文需要使用的宏
#define MAX_LINE_LENGTH 1024
#define MAX_BUF_SIZE    512


// 命令行参数解析模块定义的全局变量
int options_bytes = 0;      // 是否统计字节数
int options_chars = 0;      // 是否统计字符数
int options_words = 0;      // 是否统计单词数
int options_lines = 0;      // 是否统计行数
int options_max_line_len = 0;  // 是否统计最大行长度
char *options_total = "auto";    // 总计选项：auto, always, only, never
char **files_list = NULL;         // 待统计的文件名列表
int files_count = 0;              // 待统计文件的数量
bool read_from_file = false;


// 统计计算模块定义的全局变量
int global_bytes_count = 0;          // 统计字节数
int global_chars_count = 0;          // 统计字符数
int global_words_count = 0;          // 统计单词数
int global_lines_count = 0;          // 统计行数
int global_max_line_length = 0;      // 统计最大行长度
int current_line_length = 0;         // 当前未统计完的行的长度
int global_total_bytes = 0;          // 总计字节数
int global_total_chars = 0;          // 总计字符数
int global_total_words = 0;          // 总计单词数
int global_total_lines = 0;          // 总计行数
int global_total_max_line_length = 0; // 总计最大行长度
int global_read_from_file = 0;      // 是否从文件读取文件列表
char *global_file_name = NULL;      // 当前文件名

// 命令行参数解析模块定义的函数
void print_error(char *message, ...);
void read_files_list(char *file);
char *read_until_null_from_stdin();
char *read_until_null_from_file(FILE *file_handle);
int is_total_option(const char *option);
void parse_arguments(int argc, char *argv[]);

// 统计计数模块定义的函数
void clear_statistics();
bool is_whitespace(char c);
void stat_file(FILE *file_handle);


// 输出格式化模块定义的函数
void print_statistics(
    int lines,
    int words,
    int chars,
    int bytes,
    int max_line_length,
    char *filename
);

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
    size_t count = 0;
    int ch;
    while ((ch = fgetc(stdin)) != EOF && count < MAX_LINE_LENGTH - 1) {
        if ((char)ch == '\0') {
            break;
        }
        line[count++] = (char)ch;
    }
    line[count] = '\0';
    if (count == 0) {
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
    size_t count = 0;
    int ch;
    while ((ch = fgetc(file_handle)) != EOF && count < MAX_LINE_LENGTH - 1) {
        if ((char)ch == '\0') {
            break;
        }
        line[count++] = (char)ch;
    }
    line[count] = '\0';
    if (count == 0) {
        free(line);
        return NULL;
    }
    return line;
}

void read_files_list(char *file) {
    if (strcmp(file, "-") == 0) {
        for (;;) {
            char *file_name = read_until_null_from_stdin();
            if (file_name == NULL) {
                break;
            }
            if (strlen(file_name) > 0) {
                char **new_list = (char **)realloc(files_list, sizeof(char *) * (files_count + 1));
                if (new_list == NULL) {
                    free(file_name);
                    print_error("Error: memory allocation failed.");
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
            print_error("Error: Unable to open file %s.\n", file);
        }
        for (;;) {
            char *file_name = read_until_null_from_file(file_handle);
            if (file_name == NULL) {
                break;
            }
            if (strlen(file_name) > 0) {
                char **new_list = (char **)realloc(files_list, sizeof(char *) * (files_count + 1));
                if (new_list == NULL) {
                    free(file_name);
                    fclose(file_handle);
                    print_error("Error: memory allocation failed.");
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
            char **new_list = (char **)realloc(files_list, sizeof(char *) * (files_count + 1));
            if (new_list == NULL) {
                print_error("Error: memory allocation failed.");
            }
            files_list = new_list;
            files_list[files_count] = strdup(argv[i]);
            if (files_list[files_count] == NULL) {
                print_error("Error: memory allocation failed.");
            }
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
    for (;;) {
        size_t bytes_read = fread(buffer + prev_unprocessed_bytes, 1, MAX_BUF_SIZE - prev_unprocessed_bytes, file_handle);
        if (bytes_read < 0) print_error("Error: failed reading input.\n");
        if (bytes_read == 0) {
            if (ferror(file_handle)) {
                print_error("Error: read failed.");
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
                int ret = mbtowc(&wc, (const char *)(buffer + char_iter), 2);
                int w = (ret > 0) ? wcwidth(wc) : 0;
                if (w > 0) {
                    current_line_length += w;
                }
                char_iter += 2;
                global_words_count += prev_space ? 1 : 0;
                prev_space = false;
            } else if (byte >= 0xE0 && byte <= 0xEF) {
                if (total_bytes - char_iter < 3) {
                    break;
                }
                wchar_t wc;
                int ret = mbtowc(&wc, (const char *)(buffer + char_iter), 3);
                global_chars_count++;
                int w = (ret > 0) ? wcwidth(wc) : 0;
                if (w > 0) {
                    current_line_length += w;
                }
                global_words_count += prev_space ? 1 : 0;
                prev_space = false;
                char_iter += 3;
            } else if (byte >= 0xF0 && byte <= 0xF7) {
                if (total_bytes - char_iter < 4) {
                    break;
                }
                wchar_t wc;
                int ret = mbtowc(&wc, (const char *)(buffer + char_iter), 4);
                global_chars_count++;
                int w = (ret > 0) ? wcwidth(wc) : 0;
                if (w > 0) {
                    current_line_length += w;
                }
                global_words_count += prev_space ? 1 : 0;
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
    char output_string[1024];
    output_string[0] = '\0';
    bool first_field = true;
    char buffer[128];

    if (options_lines) {
        snprintf(buffer, sizeof(buffer), "%d", lines);
        strcat(output_string, buffer);
        first_field = false;
    }
    if (options_words) {
        if (first_field == true) {
            snprintf(buffer, sizeof(buffer), "%d", words);
            strcat(output_string, buffer);
            first_field = false;
        } else {
            snprintf(buffer, sizeof(buffer), " %d", words);
            strcat(output_string, buffer);
        }
    }
    if (options_chars) {
        if (first_field == true) {
            snprintf(buffer, sizeof(buffer), "%d", chars);
            strcat(output_string, buffer);
            first_field = false;
        } else {
            snprintf(buffer, sizeof(buffer), " %d", chars);
            strcat(output_string, buffer);
        }
    }
    if (options_bytes) {
        if (first_field == true) {
            snprintf(buffer, sizeof(buffer), "%d", bytes);
            strcat(output_string, buffer);
            first_field = false;
        } else {
            snprintf(buffer, sizeof(buffer), " %d", bytes);
            strcat(output_string, buffer);
        }
    }
    if (options_max_line_len) {
        if (first_field == true) {
            snprintf(buffer, sizeof(buffer), "%d", max_line_length);
            strcat(output_string, buffer);
            first_field = false;
        } else {
            snprintf(buffer, sizeof(buffer), " %d", max_line_length);
            strcat(output_string, buffer);
        }
    }
    if (filename != NULL) {
        snprintf(buffer, sizeof(buffer), " %s", filename);
        strcat(output_string, buffer);
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