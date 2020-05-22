/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:28:49 by schene            #+#    #+#             */
/*   Updated: 2020/05/22 15:23:20 by schene           ###   ########.fr       */
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

int		is_builtin(char *cmd);
void	exec_builtin(char **cmd, t_list *env, int status, char *line);
void	builtin_cd(char *path, t_list *env);
void	builtin_pwd(void);
t_list	*create_env(char	**env);
void	print_env(t_list *env);
void	builtin_export(char **cmd, t_list *env);
void	builtin_unset(char	**cmd, t_list *env);
void	builtin_exit(void);
void	builtin_echo(t_list *env, char **cmd, int status, char *line);
char	*variable_value(t_list *env, char *var);
char	**split_quotes(char const *s);
char	**split_spaces(char *s, char *charset);

#endif 