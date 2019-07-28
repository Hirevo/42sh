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

#define RC_FILE ".42shrc"
#define HIST_FILE ".42sh_history"
#define ALIAS_FILE ".42sh_alias"

extern char **environ;

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

typedef enum {
    ERROR_UNMATCHED_QUOTE,
    ERROR_REDIRECT_MISSING_NAME,
    ERROR_AMBIGUOUS_INPUT,
    ERROR_AMBIGUOUS_OUTPUT,
    ERROR_NULL_COMMAND
} ErrorKind;

typedef enum {
    REPORT_SINGLE_INDEX,
    REPORT_SINGLE_SPAN,
    REPORT_DOUBLE_INDEX,
    REPORT_DOUBLE_SPAN
} ReportKind;

typedef struct {
    size_t idx1;
} ReportSingleIndex;

typedef struct {
    size_t start;
    size_t end;
} ReportSingleSpan;

typedef struct {
    ReportSingleIndex fst;
    ReportSingleIndex snd;
} ReportDoubleIndex;

typedef struct {
    ReportSingleSpan fst;
    ReportSingleSpan snd;
} ReportDoubleSpan;

typedef struct {
    ReportKind kind;
    union {
        ReportSingleIndex single_index;
        ReportSingleSpan single_span;
        ReportDoubleIndex double_index;
        ReportDoubleSpan double_span;
    };
} Report;

typedef struct {
    ErrorKind kind;
    Report report;
} Error;

typedef enum {
    REDIR_KIND_FILE = 0,
    REDIR_KIND_FD,
} RedirectKind;

typedef enum {
    REDIR_TYPE_SIMPLE_LEFT = 0,
    REDIR_TYPE_SIMPLE_RIGHT,
    REDIR_TYPE_DOUBLE_LEFT,
    REDIR_TYPE_DOUBLE_RIGHT,
} RedirectType;

typedef struct {
    RedirectKind kind;
    RedirectType type;
    size_t from_fd;
    union {
        char *to_name;
        size_t to_fd;
    };
} Redirect;

DEF_OPTION(Redirect, Redirect);
DEF_RESULT(Redirect, Redirect, char *);
DEF_OPTION(RedirectPtr, Redirect *);
DEF_RESULT(RedirectPtr, Redirect *, char *);

typedef struct Command {
    vec_t *av;
    vec_t *redirects;
    char link;
    struct Command *prev;
    struct Command *next;
} Command;

DEF_OPTION(CommandPtr, Command *);
DEF_RESULT(CommandPtr, Command *, char *);

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
    char *delete;
    char *backsp;
    hmap_t *actions;
    size_t cur;
} Window;

typedef struct {
    char *rc_file;
    char *alias_file;
    char *history_file;
    char *prompt;
} Config;

DEF_OPTION(Config, Config);
DEF_RESULT(Config, Config, char *);

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
** is_done: flag to exit after the command execution ends (set by `exit`).
** exit_code: last exit code (used for prompts and `exit`).
** tty: is the stdin interactive (to enable/disable prompt and autocompletion).
** ioctl: is ioctl supported on the terminal.
** vars: internal variables of the shell (accessible via `set` and `unset`).
** aliases: command aliases (accessible via `alias` and `unalias`).
** builtins: list of builtins (listed via `builtins`).
** hist: history management (for prompt arrow keys, globbing and `history`).
** w: interactive terminal data structure (for the interactive prompt)
** config: a future potential configuration struct.
*/
typedef struct {
    char **av;
    int prompt;
    char is_done;
    unsigned int exit_code;
    int tty;
    int ioctl;
    hmap_t *vars;
    hmap_t *aliases;
    hmap_t *builtins;
    History hist;
    Window w;
    Config config;
} Shell;

typedef void (*PromptAction)(Shell *, char **line);

DEF_OPTION(PromptAction, PromptAction);
OPT_NULLABLE(PromptAction, PromptAction);
DEF_RESULT(PromptAction, PromptAction, char *);

size_t estimate_fragment_count(char *);
int get_next_arg(char *, char **, int);
vec_t *split_fragments(char *, int);
void exec_process(vec_t *);
OPTION(Int) exec_command(char **, Shell *);
int exec_line(Shell *, char *, bool);
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
void free_commands(Command *);
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
void init_aliases(Shell *);
void set_alias(Shell *, char *);
void free_alias(Shell *);
void free_hist(Shell *);
int disp_alias(Shell *, char *);
int disp_all_alias(Shell *);
int add_alias(Shell *, char *, char *);
void save_alias(Shell *);
void my_print_fd(char *, int);
OPTION(CommandPtr) parse_commands(vec_t *);
int check_access(char **, Shell *);
int check_env_error(char *, char *);
int check_exit(Shell *, vec_t *);
int compare_stats(struct stat *);
void check_exec(Shell *, int, int *);
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
OPTION(CharPtr) clear_comment(char *line);

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
void skip_string(char *, size_t *);

OPTION(CharPtr) substitute_aliases(Shell *, char *);
OPTION(CharPtr) substitute_commands(Shell *, char *);
OPTION(CharPtr) substitute_globs(Shell *, char *);
OPTION(CharPtr) substitute_history(Shell *, char *, bool);
OPTION(CharPtr) substitute_vars(Shell *, char *);

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
void quick_exec(Shell *, char *);

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
bool assign_redirects(Command *commands);

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
bool check_errors(Command *commands);

/*
** parse/redirects.c
*/
OPTION(Redirect) parse_redirect(const char *line);
OPTION(SizeT) span_redirect(const char *line);

/*
** exec/pipe.c
*/
OPTION(Int) exec_pipeline(Shell *, Command *);

/*
** exec/setup.c
*/
void init_redirect(Command *, int *, int *, int *);
void skip_commands(Command **, unsigned char);

/*
** exec/redirects.c
*/
bool redirect_simple_left(Redirect *redirect);
bool redirect_simple_right(Redirect *redirect);
bool redirect_double_left(Redirect *redirect);
bool redirect_double_right(Redirect *redirect);

/*
** globbing/.c
*/
void replace_home(Shell *);

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

void action_autocomplete(Shell *, char **);
void action_clear_term(Shell *, char **);
void action_cursor_backspace(Shell *, char **);
void action_cursor_delete(Shell *, char **);
void action_cursor_down(Shell *, char **);
void action_cursor_end(Shell *, char **);
void action_cursor_home(Shell *, char **);
void action_cursor_left(Shell *, char **);
void action_cursor_right(Shell *, char **);
void action_cursor_up(Shell *, char **);
void action_open_editor(Shell *, char **);

/*
** prompt/mechanics/editor.c
*/
void prompt_open_editor(Shell *, char **line);

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
void add_char(Shell *, char **, char);
void parse_escape_sequence(Shell *, char **, char);
void clear_term(Shell *, char *);
void pos_cursor(Shell *, char *);

/*
** prompt/mechanics/cursor.c
*/
RESULT(PromptAction) buffer_seq(Shell *, char);

/*
** prompt/mechanics/advanced.c
*/
void set_hist_line(Shell *, char **);
void suppress_line(Shell *, char *);

/*
** prompt/mechanics/prompt.c
*/
OPTION(CharPtr) prompt_line(Shell *);
void wait_input(void);

OPTION(Config) parse_config(char *filename);
