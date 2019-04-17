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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <termios.h>
#include <option.h>
#include <result.h>

DEF_OPTION(CharPtr, char *);
OPT_NULLABLE(CharPtr, char *);
DEF_RESULT(CharPtr, char *, char *);

DEF_OPTION(CharPtrPtr, char **);
OPT_NULLABLE(CharPtrPtr, char **);
DEF_RESULT(CharPtrPtr, char **, char *);

DEF_OPTION(SizeT, size_t);
DEF_RESULT(SizeT, size_t, char *);

#define RC_FILE ".42shrc"
#define HIST_FILE ".42sh_history"
#define ALIAS_FILE ".42sh_alias"

extern char **environ;

typedef struct {
    bool ok;
    int code;
} exec_status_t;

typedef struct command_s {
    vec_t *av;
    char link;
    char *r_name;
    char *r_type;
    char *l_name;
    char *l_type;
    int count;
    struct command_s *prev;
    struct command_s *next;
} command_t;

typedef struct {
    char *alias;
    char *command;
} alias_t;

typedef struct {
    int idx;
    char **list;
} subst_t;

typedef struct {
    vec_t *arr;
    long cur;
    char *cur_line;
} hist_ctrl_t;

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
} window_t;

typedef struct {
    char *rc_file;
    char *alias_file;
    char *history_file;
    char *prompt;
} config_t;

/*
** This is the main structure that binds the shell together
**
** av: av give in the main (for var $0, $1, ...)
** script: is launch from script
** current: the current working directory, for prompt
** line: raw command input from user
** final: parsed command from line
** hist: last parsed command executed
** hist_args: arg count from hist
** exit: last exit status, for exit builtin
** exit_str: last exit status converted to str, for prompt
** last: used for alias processing, avoids loops
** prev: last working directory, for cd builtin
**
*/
typedef struct {
    char **av;
    int script;
    int prompt;
    hmap_t *vars;
    char *line;
    char **final;
    char is_done;
    unsigned int exit_code;
    char *last;
    int *fds;
    int tty;
    int ioctl;
    pid_t pgid;
    hmap_t *alias;
    subst_t subst;
    hist_ctrl_t hist;
    command_t *commands;
    command_t *cur;
    window_t w;
    config_t config;
    int is_comp;
} shell_t;

unsigned int count_args(char *);
int get_next_arg(char *, char **, int);
char **bufferize(char *, int);
char *cat_path(char **, char *, int);
void exec_process(vec_t *);
unsigned int exec_command(char **, shell_t *);
unsigned int exec_line(shell_t *, unsigned int);
void parse_rc(shell_t *);
int count_entries(char *);
int get_next_entry(char *, char **, int);
char **init_path(char *);
char **set_default_path(void);
int disp_env(void);
int move_dir(vec_t *);
unsigned int exec_action(shell_t *, unsigned int);
unsigned int process_command(shell_t *, int);
int is_char_alpha(char *);
int set_env(char *, char *);
int unset_env(vec_t *);
void free_shell(shell_t *);
void free_shell2(shell_t *);
void free_commands(shell_t *);
int my_print_err(char *);
int my_print_ret(char *, int);
int is_path(char *);
int is_valid_path(char *);
void diagnose_status(unsigned int);
int check_wave(shell_t *);
void add_hist(shell_t *);
void my_print_command(shell_t *);
char *detect_home(char *, char *);
char *get_current(char *, char *);
int indexof_builtin(char *);
exec_status_t exec_builtins(shell_t *, vec_t *);
unsigned int get_unsigned_int(char *);
int is_line_empty(char *);
int init_shell(shell_t *);
int my_strlen_spe(char *, char);
void init_aliases(shell_t *);
void set_alias(shell_t *, char *);
void free_alias(shell_t *);
void free_hist(shell_t *);
int disp_alias(shell_t *, char *);
int disp_all_alias(shell_t *);
int add_alias(shell_t *, char *, char *);
void save_alias(shell_t *);
void my_print_fd(char *, int);
int set_commands(shell_t *);
int check_access(char **, shell_t *);
int check_env_error(char *, char *);
int check_exit(shell_t *, vec_t *);
int compare_stats(struct stat *);
void check_exec(shell_t *, int, int *);
void exec_piped_command(char *, command_t *, int[2], shell_t *);
char *format_arg(char *);

void putstr(const char *fmt, ...);
void eputstr(const char *fmt, ...);
void dputstr(const int fd, const char *fmt, ...);
char *path_join(const char *p1, const char *p2);
char *pretty_path(const char *path);

/*
** alias/alias.c
*/
char *construct_alias(char **);
char *get_alias_cmd(shell_t *, char *);

/*
** alias/edit.c
*/
int parse_alias(shell_t *);

/*
** alias/unalias.c
*/
int unalias(shell_t *, vec_t *);

/*
** alias/loop.c
*/
void free_subst(shell_t *);
int detect_loop(shell_t *, char *, int);

/*
** comment.c
*/

int clear_comment(shell_t *);

/*
** config.c
*/

int config_http(shell_t *, t_config *);

/*
** history.c
*/
void save_history(shell_t *);
int disp_hist(shell_t *, vec_t *);
void add_hist_elem(shell_t *, char *);
void init_history(shell_t *);
void skip_string(char *, int *);

/*
** history2.c
*/
int subst_history(shell_t *, int);

/*
** magic/magic.c
*/
int magic(shell_t *);

/*
** magic/construct.c
*/
char *construct_magic(char **);

/*
** sanitizers/sanitizers.c
*/
char *sanitize(char *, bool);
char *sanitize_double_quotes(char *, bool);

/*
** exec/exec2.c
*/
exec_status_t exec_redirected_builtins(shell_t *, int[2]);
void quick_exec(shell_t *, char *);

/*
** exec/close.c
*/
int close_pipes(int *);

/*
** dualcast.c
*/

int launch_dualcast(shell_t *, vec_t *);

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

int launch_config(shell_t *);

/*
** redirects.c
*/
int setup_right_redirect(command_t *, int *, int);
int setup_left_redirect(char *, int);
int check_redirects(command_t *, command_t *);
int prepare_redirect(command_t *, char **, char **, size_t);
int set_redirects(shell_t *);

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
int check_error(shell_t *);

/*
** exec/pipe.c
*/
exec_status_t exec_pipeline(shell_t *);
int father_action(command_t **, int *, int *, shell_t *, pid_t);
void exec_piped_child(int, command_t *, int[2], shell_t *);

/*
** exec/tmp.c
*/
void tmp_file(shell_t *);

/*
** exec/setup.c
*/
void init_redirect(command_t *, int *, int *, int *);
void setup_exec(command_t *, int *, int);
void skip_commands(command_t **, unsigned char);
void set_fground(shell_t *);

/*
** globbing/globbing.c
*/
int parse_vars(shell_t *);

/*
** globbing/.c
*/
void replace_home(shell_t *);

/*
** globbing/stars.c
*/
int parse_stars(shell_t *);

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
** builtins/set.c
*/
int set(shell_t *, vec_t *);

/*
** builtins_init.c
*/
int nb_built(const char **);

/*
** builtins/unset.c
*/
int unset(shell_t *, vec_t *);

/*
** char.c
*/
void insert_char(char **, char);
void insert_int(int **, int);

/*
** print.c
*/
int ret_error(shell_t *, char *);

/*
** prompt.c
*/
OPTION(CharPtr) get_hostname(void);
void print_prompt(shell_t *);
void get_prompt(shell_t *);

/*
** vars.c
*/
void init_vars(shell_t *);

/*
** init.c
*/

void set_raw(struct termios *);
void init(shell_t *);
void init_prompt(shell_t *);

/*
** misc.c
*/
char get_input(void);
void handle_error(char *);

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

void sauv_prompt(shell_t *);

/*
** prompt/mechanics/load_file.c
*/

void free_tab(char **);
char **load_file(int);

/*
** prompt/mechanics/actions.c
*/
void remove_char(shell_t *);
void add_char(shell_t *, char);
void move_cursor(shell_t *, char);
void clear_term(shell_t *);
void pos_cursor(shell_t *);

/*
** prompt/mechanics/cursor.c
*/
void buffer_seq(shell_t *, char **, int *, char);
void move_forw(shell_t *);
void move_backw(shell_t *);
void move_upw(shell_t *);
void move_downw(shell_t *);

/*
** prompt/mechanics/advanced.c
*/
void move_home(shell_t *);
void move_end(shell_t *);
void set_hist_line(shell_t *);
void suppress_line(shell_t *);

/*
** prompt/mechanics/fct.c
*/
void get_cur_fcts(void (*[6])(shell_t *));

/*
** prompt/mechanics/prompt.c
*/
void prompt_line(shell_t *);
