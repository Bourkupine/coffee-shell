#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF_SIZE 64
#define TOK_DELIM " \n"


typedef int (*builtin_cmd)(int argc, char **args);

int cofsh_exit(int argc, char **args);
int cofsh_cd(int argc, char **args);

struct builtin_entry {
    char *cmd;
    builtin_cmd func;
};

struct builtin_entry builtins[] = {
    {"exit", cofsh_exit},
    {"quit", cofsh_exit},
    {"cd", cofsh_cd},
};
 
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

void startup_print() {
    char *startup_msg = 
        "☕\n";
    printf("%s\n", startup_msg);
}

int parse_line(char *line, char ***args) {
    *args = malloc(BUF_SIZE * sizeof(char *));
    char *token;
    int pos = 0;

    if (!(*args)) {
        fprintf(stderr, "failed to malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL) {
//        printf("%d | %s\n", pos, token);
        (*args)[pos] = token;
        pos++;

        token = strtok(NULL, TOK_DELIM);
    }
    return pos;
}

int exec_args(int argc, char **args) {

    //first check for builtins
    int num_builtins = sizeof(builtins) / sizeof(builtins[0]);
    for (int i = 0; i < num_builtins; i++) {
        if (strcmp(args[0], builtins[i].cmd) == 0) {
            return builtins[i].func(argc, args);
        }
    }    

    //otherwise execute
    pid_t pid, wpid;
    int status;

    pid = fork();

    switch(pid) {
    case -1:
        perror("cofsh");
    case 0:
        if (execvp(args[0], args) == -1)
            perror("cofsh");
    default:
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

#define PATH_MAX 32

void cofsh_loop() {
    char *line = NULL;
    char **args = NULL;
    int *arg_count = NULL;
    size_t len = 0;
    int status = 1;
    char dir[PATH_MAX];

    do {
        if (getcwd(dir, sizeof(dir)) != NULL) {
            printf("%s\n", dir);
        }

        printf("> ");

        if (getline(&line, &len, stdin) == -1) {
            return;
        }
        int ret = parse_line(line, &args);
        if (ret < 1) {
            free(args);
            continue;
        }
        status = exec_args(ret, args);
        free(args);

    } while (status);
}

int main() {

    startup_print();    

    cofsh_loop();

    return 0;
}

