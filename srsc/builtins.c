/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 09:06:02 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/07/28 17:06:57 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			sh_echo_std(char *str, int ctr)
{
	if (ctr != 1)
		ft_printf(" %s", str);
	else
		ft_printf("%s", str);
}

void			print_var(int n)
{
	int			ctr;

	ctr = 0;
	while ((g_my_env[n][ctr] != '=') && (g_my_env[n][ctr]))
		ctr++;
	if (g_my_env[n][ctr])
		ctr++;
	while (g_my_env[n][ctr])
	{
		ft_printf("%c", g_my_env[n][ctr]);
		ctr++;
	}
}

int				sh_echo(char **args)
{
	int			ctr;
	int			comp_ret;
	char		*temp;

	ctr = 1;
	comp_ret = 0;
	while (args[ctr])
	{
		if (args[ctr][0] != '$')
			sh_echo_std(args[ctr], ctr);
		else
		{
			temp = args[ctr];
			args[ctr] = ft_strsub(args[ctr], 1, (ft_strlen(args[ctr]) - 1));
			free(temp);
			if ((comp_ret = comp_var_env(args[ctr])) != 0)
				print_var(comp_ret);
		}
		ctr++;
	}
	ft_putchar('\n');
	return (1);
}

int				cd_sub(char **args, char *n_p, char *old_pwd, char *free_ptr)
{
	char		buf[1024];

	if (chdir(n_p) != 0)
		ft_printf("Unable to change to directory %s\n", args[1]);
	else
	{
		sh_setenv(old_pwd);
		free_ptr = ft_strjoin("PWD=", getcwd(buf, sizeof(buf)));
		sh_setenv(free_ptr);
		free(free_ptr);
	}
	free(n_p);
	free(old_pwd);
	return (1);
}

int				sh_cd(char **args)
{
	char		*new_path;
	char		*old_pwd;
	char		*free_ptr;
	char		*free_ptr2;

	new_path = NULL;
	free_ptr = get_env_var_value("PWD");
	old_pwd = ft_strjoin("OLDPWD=", free_ptr);
	free(free_ptr);
	if (args[1] == NULL || (ft_strcmp(args[1], "~") == 0))
		new_path = get_env_var_value("HOME");
	else if (args[1] && args[1][0] == '~')
	{
		free_ptr = get_env_var_value("HOME");
		free_ptr2 = ft_strsub(args[1], 1, (ft_strlen(args[1]) - 1));
		new_path = ft_strjoin(free_ptr, free_ptr2);
		free(free_ptr);
		free(free_ptr2);
	}
	else if (ft_strcmp(args[1], "-") == 0)
		new_path = get_env_var_value("OLDPWD");
	else
		new_path = ft_strdup(args[1]);
	return (cd_sub(args, new_path, old_pwd, free_ptr));
}
