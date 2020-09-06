/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 07:52:04 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/07/28 17:09:24 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				sh_env(void)
{
	int			ctr;

	ctr = 0;
	while (g_my_env[ctr])
	{
		ft_printf("%s\n", g_my_env[ctr]);
		ctr++;
	}
	return (1);
}

int				sh_unset(char **args)
{
	int			comp_ret;

	comp_ret = comp_var_env(args[1]);
	if (comp_ret == 0)
		return (1);
	else
	{
		while (g_my_env[comp_ret])
		{
			free(g_my_env[comp_ret]);
			if (g_my_env[comp_ret + 1] != NULL)
				g_my_env[comp_ret] = ft_strdup(g_my_env[comp_ret + 1]);
			else
				g_my_env[comp_ret] = NULL;
			comp_ret++;
		}
	}
	return (1);
}

void			add_env_var(char *args)
{
	int			ctr;
	char		**new_env;

	ctr = 0;
	while (g_my_env[ctr])
		ctr++;
	new_env = (char **)ft_memalloc(sizeof(char **) * (ctr + 2));
	ctr = 0;
	while (g_my_env[ctr])
	{
		new_env[ctr] = ft_strdup(g_my_env[ctr]);
		ctr++;
	}
	new_env[ctr] = ft_strdup(args);
	new_env[ctr + 1] = NULL;
	free_2d(&g_my_env);
	g_my_env = new_env;
}

int				sh_setenv(char *args)
{
	int			ctr;
	char		*env_var;
	int			comp_ret;

	if (!args || !ft_strchr(args, '='))
	{
		ft_printf("Error format used: VARIABLE_NAME=variable_value\n");
		return (1);
	}
	ctr = 0;
	comp_ret = 0;
	while (args[ctr] != '=')
		ctr++;
	env_var = ft_strsub(args, 0, ctr);
	if ((comp_ret = comp_var_env(env_var)))
	{
		free(g_my_env[comp_ret]);
		g_my_env[comp_ret] = ft_strdup(args);
	}
	else
		add_env_var(args);
	free(env_var);
	return (1);
}

int				comp_var_env(char *args)
{
	int			ctr;
	int			a_ctr;
	char		*e_var;

	ctr = 0;
	a_ctr = 0;
	e_var = NULL;
	while (g_my_env[ctr])
	{
		while (g_my_env[ctr][a_ctr] && g_my_env[ctr][a_ctr] != '=')
			a_ctr++;
		e_var = ft_strsub(g_my_env[ctr], 0, a_ctr);
		if (ft_strcmp(e_var, args) == 0)
		{
			free(e_var);
			return (ctr);
		}
		free(e_var);
		ctr++;
		a_ctr = 0;
	}
	return (0);
}
