#ifndef BUILTIN_H
#define BUILTIN_H

typedef int (*builtin_cmd)(int argc, char **args);

int get_num_builtin();

int cofsh_exit(int argc, char **args);
int cofsh_cd(int argc, char **args);
int cofsh_help(int argc, char **args);
int cofsh_brew(int argc, char **args);

struct builtin_entry {
    char *cmd;
    builtin_cmd func;
    char *help;
};

extern struct builtin_entry builtins[];

#endif /* BUILTIN_H */
