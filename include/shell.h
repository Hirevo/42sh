/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** shell
*/

#pragma once

#include "hmap.h"
#include "server.h"
#include "str.h"
#include "vec.h"
#include <option.h>
#include <result.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <termios.h>

DEF_OPTION(CharPtr, char *);
OPT_NULLABLE(CharPtr, char *);
DEF_RESULT(CharPtr, char *, char *);

DEF_OPTION(CharPtrPtr, char **);
OPT_NULLABLE(CharPtrPtr, char **);
DEF_RESULT(CharPtrPtr, char **, char *);

DEF_OPTION(SizeT, size_t);
DEF_RESULT(SizeT, size_t, char *);

DEF_OPTION(Int, int);
DEF_RESULT(Int, int, char *);

#define RC_FILE ".42shrc"
#define HIST_FILE ".42sh_history"
#define ALIAS_FILE ".42sh_alias"

extern char **environ;

typedef struct Command {
    vec_t *av;
    char link;
    char *r_name;
    char *r_type;
    char *l_name;
    char *l_type;
    int count;
    struct Command *prev;
    struct Command *next;
} Command;

typedef struct {
    char *alias;
    char *command;
} Alias;

typedef struct {
    int idx;
    char **list;
} Subst;

typedef struct {
    vec_t *arr;
    long cur;
    char *cur_line;
} History;

typedef struct {
    struct termios oterm;
    char *smkx;
    char *rmkx;
    char *clear;
    char *end;
    char *home;
    char *forw;
    char *backw;
    char *upw;
    char *downw;
    char *left;
    char *right;
    int cur;
} Window;

typedef struct {
    char *rc_file;
    char *alias_file;
    char *history_file;
    char *prompt;
} Config;

/*
** This is the main structure that binds the shell together.
** It serves as its internal state.
**
** NOTE: It is somewhat cluttered with fields we could remove.
**       The removal of those fields will be done with time, as parts of
**       shell gets revisited.
**
** av: argument list of the shell (for $0, $1, etc...).
** prompt: current selected prompt ID.
** line: raw command input from user.
** final: parsed command from line.
** is_done: flag to exit after the command execution ends (set by `exit`).
** exit_code: last exit code (used for prompts and `exit`).
** fds: list of current running process IDs, for execution pipelines.
** tty: is the stdin interactive (to enable/disable prompt and autocompletion).
** ioctl: is ioctl supported on the terminal.
** pgid: current process group leader.
** vars: internal variables of the shell (accessible via `set` and `unset`).
** aliases: command aliases (accessible via `alias` and `unalias`).
** builtins: list of builtins (listed via `builtins`).
** subst: used for alias processing, avoids alias loops (used by `alias`).
** hist: history management (for prompt arrow keys, globbing and `history`).
** commands: current command list to execute.
** cur: currently processed command (points into `Shell::commands`).
** w: interactive terminal data structure (for the interactive prompt)
** config: a future potential configuration struct.
*/
typedef struct {
    char **av;
    int prompt;
    char *line;
    vec_t *fragments;
    char is_done;
    unsigned int exit_code;
    char *last;
    int *fds;
    int tty;
    int ioctl;
    pid_t pgid;
    hmap_t *vars;
    hmap_t *aliases;
    hmap_t *builtins;
    Subst subst;
    History hist;
    Command *commands;
    Command *cur;
    Window w;
    Config config;
} Shell;

unsigned int count_args(char *);
int get_next_arg(char *, char **, int);
vec_t *bufferize(char *, int);
char *cat_path(char **, char *, int);
void exec_process(vec_t *);
unsigned int exec_command(char **, Shell *);
unsigned int exec_line(Shell *, unsigned int);
void parse_rc(Shell *);
int count_entries(char *);
int get_next_entry(char *, char **, int);
char **init_path(char *);
char **set_default_path(void);
int disp_env(void);
int move_dir(vec_t *);
unsigned int exec_action(Shell *, unsigned int);
unsigned int process_command(Shell *, int);
int is_char_alpha(char *);
int set_env(char *, char *);
int unset_env(vec_t *);
void free_shell(Shell *);
void free_shell2(Shell *);
void free_commands(Shell *);
int my_print_err(char *);
int my_print_ret(char *, int);
int is_path(char *);
int is_valid_path(char *);
void diagnose_status(unsigned int);
int check_wave(Shell *);
void add_hist(Shell *);
void my_print_command(Shell *);
char *detect_home(char *, char *);
char *get_current(char *, char *);
int indexof_builtin(char *);
OPTION(Int) exec_builtins(Shell *, vec_t *);
unsigned int get_unsigned_int(char *);
int is_line_empty(char *);
void init_shell(Shell *);
int my_strlen_spe(char *, char);
void init_aliases(Shell *);
void set_alias(Shell *, char *);
void free_alias(Shell *);
void free_hist(Shell *);
int disp_alias(Shell *, char *);
int disp_all_alias(Shell *);
int add_alias(Shell *, char *, char *);
void save_alias(Shell *);
void my_print_fd(char *, int);
int set_commands(Shell *);
int check_access(char **, Shell *);
int check_env_error(char *, char *);
int check_exit(Shell *, vec_t *);
int compare_stats(struct stat *);
void check_exec(Shell *, int, int *);
void exec_piped_command(char *, Command *, int[2], Shell *);
char *format_arg(char *);

void writechar(const char chr);
void ewritechar(const char chr);
void dwritechar(const int fd, const char chr);
void writestr(const char *str);
void ewritestr(const char *str);
void dwritestr(const int fd, const char *str);
char *fmtstr(const char *fmt, ...);
void putstr(const char *fmt, ...);
void eputstr(const char *fmt, ...);
void dputstr(const int fd, const char *fmt, ...);
char *path_join(const char *p1, const char *p2);
char *pretty_path(const char *path);

/*
** alias/alias.c
*/
char *construct_alias(char **);
char *get_alias_cmd(Shell *, char *);

/*
** alias/edit.c
*/
int parse_alias(Shell *);

/*
** alias/unalias.c
*/
int unalias(Shell *, vec_t *);

/*
** alias/loop.c
*/
void free_subst(Shell *);
int detect_loop(Shell *, char *, int);

/*
** comment.c
*/
int clear_comment(Shell *);

/*
** config.c
*/
int config_http(Shell *, t_config *);

/*
** history.c
*/
void save_history(Shell *);
int disp_hist(Shell *, vec_t *);
void add_hist_elem(Shell *, char *);
void init_history(Shell *);
void skip_string(char *, int *);

/*
** history2.c
*/
int subst_history(Shell *, int);

/*
** magic/magic.c
*/
int magic(Shell *);

/*
** magic/construct.c
*/
char *construct_magic(char **);

/*
** sanitizers/sanitizers.c
*/
char *sanitize(char *, bool);
char *sanitize_single_arg(char *, bool);
char *sanitize_double_quotes(char *, bool);

/*
** exec/exec2.c
*/
OPTION(Int) exec_redirected_builtins(Shell *, int[2]);
void quick_exec(Shell *, char *);

/*
** exec/close.c
*/
int close_pipes(int *);

/*
** dualcast.c
*/
int launch_dualcast(Shell *, vec_t *);

/*
** dualcast/wait_connection.c
*/
t_socket wait_connection(t_socket, fd_set *, char *);

/*
** dualcast/init_dualcast.c
*/
int init_dualcast(t_socket *);

/*
** dualcast/get_password.c
*/
char *get_password(void);

/*
** launch_config.c
*/
int launch_config(Shell *);

/*
** redirects.c
*/
int setup_right_redirect(Command *, int *, int);
int setup_left_redirect(char *, int);
int check_redirects(Command *, Command *);
int prepare_redirect(Command *, char **, char **, size_t);
int set_redirects(Shell *);

/*
** buffer.c
*/
int buffer_input(char *, int[2]);

/*
** parse/line.c
*/
char *my_epurstr(char *);
char *my_epurcommand(char *);

/*
** parse/error.c
*/
int check_error(Shell *);

/*
** exec/pipe.c
*/
OPTION(Int) exec_pipeline(Shell *);
int father_action(Command **, int *, int *, Shell *, pid_t);
void exec_piped_child(int, Command *, int[2], Shell *);

/*
** exec/tmp.c
*/
void tmp_file(Shell *);

/*
** exec/setup.c
*/
void init_redirect(Command *, int *, int *, int *);
void setup_exec(Command *, int *, int);
void skip_commands(Command **, unsigned char);
void set_fground(Shell *);

/*
** globbing/globbing.c
*/
int parse_vars(Shell *);

/*
** globbing/.c
*/
void replace_home(Shell *);

/*
** globbing/stars.c
*/
int parse_stars(Shell *);

/*
** echo.c
*/
char get_escaped_char(char);
int echo_term(vec_t *);

/*
** is.c
*/
int is_redirect(char *);
int is_right_redirect(char *);
int is_left_redirect(char *);
int is_dir(char *);
int is_builtin(char *);
int is_to_fork(char);

/*
** is2.c
*/
int is_separator(char);
int is_space(char);
int is_delimiter(char);
int is_alphanum(char);
int is_num(char *);

/*
** char.c
*/
void insert_char(char **, char);
void insert_int(int **, int);

/*
** print.c
*/
int ret_error(Shell *, char *);

/*
** prompt.c
*/
OPTION(CharPtr) get_hostname(void);
void print_prompt(Shell *);
void get_prompt(Shell *);

/*
** vars.c
*/
void init_vars(Shell *);

/*
** init.c
*/
void set_raw(struct termios *);
void init(Shell *);
void init_prompt(Shell *);

/*
** misc.c
*/
char get_input(void);
void handle_error(char *);
char *read_all(int);

/*
** prompt/get_cur_branch.c
*/
char *show_cur_branch(void);

/*
** prompt/mechanics/char.c
*/
void insert_char_cur(char **, char, int);
void delete_char(char **, int);

/*
** prompt/mechanics/sauv.c
*/
void sauv_prompt(Shell *);

/*
** prompt/mechanics/load_file.c
*/
void free_tab(char **);
char **load_file(int);

/*
** prompt/mechanics/actions.c
*/
void remove_char(Shell *);
void add_char(Shell *, char);
void move_cursor(Shell *, char);
void clear_term(Shell *);
void pos_cursor(Shell *);

/*
** prompt/mechanics/cursor.c
*/
void buffer_seq(Shell *, char **, int *, char);
void move_forw(Shell *);
void move_backw(Shell *);
void move_upw(Shell *);
void move_downw(Shell *);

/*
** prompt/mechanics/advanced.c
*/
void move_home(Shell *);
void move_end(Shell *);
void set_hist_line(Shell *);
void suppress_line(Shell *);

/*
** prompt/mechanics/fct.c
*/
void get_cur_fcts(void (*[6])(Shell *));

/*
** prompt/mechanics/prompt.c
*/
void prompt_line(Shell *);
