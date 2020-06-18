/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:28:49 by schene            #+#    #+#             */
/*   Updated: 2020/06/18 15:05:12 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>

# define MAX_PATH 4096
# define RD_END 0
# define WR_END 1

pid_t g_child_pid;

typedef struct	s_data
{
	t_list		*env;
	char		**multi;
	char		*line;
	char		**cmd;
	char		**pipe;
	int			status;
	int			output;
	int			input;
	char		*dir;
}				t_data;

int				is_builtin(char *cmd);
void			exec_builtin(t_data *data);
void			builtin_cd(t_data *data);
t_list			*create_env(char	**env);
void			print_env(t_data *data);
void			builtin_export(t_data *data);
void			builtin_unset(t_data *data);
void			builtin_exit(t_data *data, int end);
void			builtin_echo(t_data *data);
char			*var_value(t_list *env, char *var);
char			**split_spaces(char *s, char const *charset);
void			ft_free(char **tab);
void			free_lst(t_list *lst);
void			close_fd(t_data *data);
char			**convert_env_to_tab(t_list *env);
void			exec_line(t_data *data);
char			**tab_of_quotes(char *str);
char			*clean_ft_strjoin(char *s1, char *s2);
int				fill_fd(t_data *data);
int				find_input(t_data *data);
int				ft_error(char **name);
int				simple_r(char *line, int i, char r);
int				double_r(char *line, int i);
char			*return_free(char **str);
int				fd_handling(t_data *data, int start);
int				len_variable(void *str);
char			*removeplus(char *str);
char			get_c_input(char *c, char str_i);
int				parse_error(char *s);
int				is_meta(char *str, int i);
char			*contains_comment(char *str);
int				is_quotes(char *str, int i);
int				check_char_q(char *s, int i, char c);
int				try_path(char *path);
void			handle_pipe(t_data *data, int i);
void			print_export(t_data *data);
int				replace_ifexist(t_list *env, char *str);
char			*escape_str(char *str, t_data *data);
t_data			*init_data(char **main_env);
void			exec_shell(t_data *data, char *line);
void			print_exec_error(char *cmd);

#endif
