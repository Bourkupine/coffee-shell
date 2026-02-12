#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 64
#define TOK_DELIM " "

void startup_print() {
    char *startup_msg = 
        "☕\n";
    printf("%s\n", startup_msg);
}

char **parse_line(char *line) {
    char **tokens = malloc(BUF_SIZE * sizeof(char *));
    char *token;
    int pos = 0;

    if (!tokens) {
        fprintf(stderr, "failed to malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL) {
//        printf("%d | %s\n", pos, token);
        tokens[pos] = token;
        pos++;

        token = strtok(NULL, TOK_DELIM);
    }
    return tokens;
}

void cofsh_loop() {
    char *line = NULL;
    char **args;
    size_t len = 0;
    int status = 1;

    do {
        printf("> ");

        if (getline(&line, &len, stdin) == -1) {
            return;
        }
        args = parse_line(line);
        free(args);

    } while (status);
}

int main() {

    startup_print();    

    cofsh_loop();

    return 0;
}

