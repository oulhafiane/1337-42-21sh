/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 01:26:35 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/03/12 14:47:53 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "const.h"
# include "libft.h"
# include <dirent.h>
# include <term.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <string.h>
# define BUF_S 10000
# define COPY_MAX 1000

typedef struct			s_builtin
{
	char				*cmd;
	void				(*f)();
}						t_builtin;

typedef struct			s_env
{
	char				*name;
	char				*value;
}						t_env;

typedef struct			s_line
{
	char				*command;
	char				*old_command;
	char				copy[COPY_MAX];
	int					top;
	int					index;
	int					copy_mode;
	int					begin_copy;
	char				print_msg;
}						t_line;

typedef struct			s_command
{
	char				*argv;
	struct s_command	*next;
}						t_command;

typedef struct			s_command_s
{
	struct s_command	*head;
	struct s_command	*tail;
	int					node_count;
}						t_command_list;

/*
**	minishell.c
*/
void					exec_cmd(char **cmds, char **path, t_list **env);

/*
**	args.c
*/
int					fix_line(char **line, t_list *env);

/*
**	builtin.c
*/
void					free_builtin(t_list *lst);
void					init_builtin(t_list **lst);
int					check_builtin(t_list *elem, void *obj);
void					run_builtin(t_list **env, char **cmds, t_list *bltin);

/*
**	env.c
*/
char					**get_path(t_list *env);
void					add_env(t_list **lst, char *name, char *value, int end);
void					init_env(t_list **lst, char **env);
char					**env_to_tab(t_list *lst);
void					free_env(t_list *lst);

/*
**	errors.c
*/
void					print_error(char *error, char *cmd);

/*
**	free.c
*/
void					free_elem_env(t_list *elem);
void					free_exec_cmd(char *error, char *full_path,
		char **head_path);

/*
**	ft_env.c
*/
char					*get_env_value(char *name, t_list *lst);

/*
**	builtins commands.
*/
void					ft_cd(char **args, t_list **env);
void					ft_echo(char **args, t_list **env);
void					ft_env(char **args, t_list **env);
void					ft_setenv(char **args, t_list **env);
void					ft_unsetenv(char **args, t_list **env);
void					ft_pwd(char **args, t_list **env);

/*
**	read_line.c
*/
int						read_line(t_line *line);

/*
**	line.c
*/
t_line					*get_t_line(void);
void					free_line(void);
t_line					*init_line(void);

/*
**	edit_line.c
*/
void					delete_char(t_line *line);
void					add_char(t_line *line, char c);

/*
**	terms.c
*/
struct termios			*get_termios(void);
int						init_termios(struct termios term);
int						init_terms(void);

/*
**	cursor.c
*/
void					go_left(t_line *line, int col);
void					go_right(t_line *line, int col);
void					move_cursor(int direction, t_line *line);

/*
**	cursor2.c
*/
int						get_current_row(int height);
void					go_down_left(void);
void					go_home(t_line *line, int col);
void					go_end(t_line *line, int col);

/*
**	cursor3.c
*/
void					go_up(t_line *line, int col);
void					go_down(t_line *line, int col);
void					next_word(t_line *line, int col, int direction);

/*
**	copy.c
*/
void					paste_text(t_line *line);
void					end_copy_mode(t_line *line, int keystrock);
void					begin_reset_mode(t_line *line);
void					go_left_copy_mode(t_line *line, int col);

/*
**	handlers.c
*/
void					child_handler(int sig);
void					signals(void);
void					exit_shell(char *format, ...);

/*
**	quotes.c
*/
void					push_stack(char *flag_quote, char buf);
int						check_stack(char flag_quote);

/*
**	pipe.c
*/
void					handle_piping(char **command, t_list **env, t_list *built_in, int count);
int						is_piped(char **commands);

/*
** Path.c
*/
int						full_path(char **cmd, char **path_env);

/*
** redirection.c
*/

int						is_redirection(char *str, int *flag);
void					redirect_in(char *filename);
void					redirect_out(char *filename, int fd, int permission);
void					handle_redirection(char ***cmds);

/*
** quotes.c
*/

char					**init_quotes(t_line *linei, t_command_list *commands);


/*
** lists.c
*/

void					init_list(t_command_list *ptr);
void					push(t_command_list *ptr, char *command);
void					free_list(t_command_list *ptr);
void					print_list(t_command_list *ptr);
char					**list_to_chars(t_command_list *ptr);

//debug
#define TERM_TTY "/dev/ttys003"
void	debug_msg(char *msg, ...);

#endif