/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:28:49 by schene            #+#    #+#             */
/*   Updated: 2020/05/27 16:43:24 by schene           ###   ########.fr       */
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
# include <errno.h>
# include <string.h>
# include <signal.h>

# define MAX_PATH 4096

typedef struct	s_data
{
	t_list		*env;
	char		**multi;
	char		*line;
	char		**cmd;
	int			status;
	int			fd;
}				t_data;

int				is_builtin(char *cmd);
void			exec_builtin(t_data *data);
void			builtin_cd(char *path, t_list *env);
void			builtin_pwd(void);
t_list			*create_env(char	**env);
void			print_env(t_list *env);
void			builtin_export(t_data *data);
void			builtin_unset(char	**cmd, t_list *env);
void			builtin_exit(t_data *data);
void			builtin_echo(t_data *data);
char			*variable_value(t_list *env, char *var);
char			**split_quotes(char *s);
char			**split_spaces(char *s, char const *charset);
char			*remove_quotes(char *cmd);
void			ft_free(char **tab);
char			*rm_sgl_quote(char *str);
char			**convert_env_to_tab(t_list *env);
void			exec_line(t_data *data);

#endif
