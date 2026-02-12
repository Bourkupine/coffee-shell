#include <stdio.h>
#include <stdlib.h>

void startup_print() {
    char *startup_msg = 
        "☕\n";
    printf("%s\n", startup_msg);
}

void cofsh_loop() {
    char* line;
    char** args;
    size_t len = 0;
    int read;
    int status = 1;

    do {
        printf("> ");

        read = getline(&line, &len, stdin);
        if (read == -1) {
            return;
        }
    } while (status);
}

int main() {

    startup_print();    

    cofsh_loop();

    return 0;
}
