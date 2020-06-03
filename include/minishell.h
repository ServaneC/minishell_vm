/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:28:49 by schene            #+#    #+#             */
/*   Updated: 2020/06/03 13:16:22 by schene           ###   ########.fr       */
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

# define MAX_PATH 4096

pid_t g_child_pid;

typedef struct	s_data
{
	t_list		*env;
	char		**multi;
	char		*line;
	char		**cmd;
	int			status;
	t_list		*fd;
}				t_data;

int				is_builtin(char *cmd);
void			exec_builtin(t_data *data);
void			builtin_cd(t_data *data);
t_list			*create_env(char	**env);
void			print_env(t_data *data);
void			builtin_export(t_data *data);
void			builtin_unset(t_data *data);
void			builtin_exit(t_data *data);
void			builtin_echo(t_data *data);
char			*var_value(t_list *env, char *var);
char			**split_quotes(char *s);
char			**split_spaces(char *s, char const *charset);
char			*remove_quotes(char *cmd);
void			ft_free(char **tab);
void			free_lst(t_list *lst);
void			close_fd(t_data *data);
char			*rm_sgl_quote(char *str);
char			**convert_env_to_tab(t_list *env);
void			exec_line(t_data *data);
char			**tab_of_quotes(char *str);
char			*clean_ft_strjoin(char *s1, char *s2);
int				echo_variable(char *s, t_data *data, char **ret, int i);
void			fill_fd(t_data *data);

#endif
