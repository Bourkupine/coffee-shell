#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "builtin.h"

struct builtin_entry builtins[] = {
    {"exit", cofsh_exit, "exit - exit shell"},
    {"quit", cofsh_exit, "quit - exit shell"},
    {"cd", cofsh_cd, "cd <dir> - change directory to <dir>"},
    {"help", cofsh_help, "help - print help"},
    {"brew", cofsh_brew, "brew <n> - set a timer for <n> minutes"}
};

int get_num_builtin() {
    return (sizeof(builtins) / sizeof(builtins[0]));
}

int cofsh_exit(int argc, char **args) {
    return 0; 
}

/* cd -> does nothing
 * cd <arg> will cd into that dir
 */
int cofsh_cd(int argc, char **args) {
    if (argc < 2) return 1;
    else {
        if (chdir(args[1]) != 0) {
            return 0;
        }
    }
    return 1;
}

int cofsh_help(int argc, char **args) {

    int num_builtins = get_num_builtin();
    printf("\n== Coffee-Shell Builtin Commands ==\n");
    for (int i = 0; i < num_builtins; i++) {
        printf("%s\n", builtins[i].help);
    }
    printf("\n");
    return 1;
}

int cofsh_brew(int argc, char **args) {
    int timer = 20; //default value

    if (argc > 1) {
        int ret = atoi(args[1]);
        if (ret) timer = ret;
    }

    char progress[11] = "..........";

    printf("preparing to brew...\n");

    for (int i = 0; i < timer; i++) {

        float ratio = (float)i / timer;
        int bars = (int)(ratio * 10);

        for (int j = 0; j < bars; j++) {
            progress[j] = '|';
        }

        printf("\r%s", progress);
        fflush(stdout);
        sleep(60);
    }
    printf("\r%s", "||||||||||");
    fflush(stdout);
    sleep(1);
    printf("\n\nCoffee is brewed!\n");
    return 1;
}
