/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 12:47:15 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/07/28 17:22:55 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <dirent.h>

char			**g_my_env;

void			sh_echo_std(char *str, int ctr);
void			print_var(int n);
int				sh_echo(char **args);
int				cd_sub(char **args, char *n_p, char *old_pwd, char *free_ptr);
int				sh_cd(char **args);
int				sh_launch(char **args, int ctr);
int				sh_execute(char **args);
void			handle_args(char **args, int ctr);
void			sh_loop(void);
char			*get_env_var_value(char *var_name);
void			pp(char **paths, char **args, int ctr2, char *free_ptr);
char			**check_paths(char **args, int ctr);
char			**get_paths(char **args);
int				sh_env(void);
int				sh_unset(char **args);
void			add_env_var(char *args);
int				sh_setenv(char *args);
int				comp_var_env(char *args);

#endif
