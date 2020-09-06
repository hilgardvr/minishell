/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 09:27:54 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/07/28 16:49:37 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char				*get_env_var_value(char *var_name)
{
	int				ctr;
	char			*var_value;
	int				var_len;

	ctr = 0;
	var_value = NULL;
	while (g_my_env[ctr])
	{
		var_len = 0;
		while (g_my_env[ctr][var_len] && g_my_env[ctr][var_len] != '=')
			var_len++;
		if (ft_strncmp(var_name, g_my_env[ctr], var_len) == 0)
		{
			var_value = ft_strsub(g_my_env[ctr], (var_len + 1),
					(ft_strlen(g_my_env[ctr]) - var_len - 1));
			return (var_value);
		}
		ctr++;
	}
	return (var_value);
}

void				pp(char **paths, char **args, int ctr2, char *free_ptr)
{
	while (paths[ctr2])
	{
		if (ctr2 == 0)
		{
			free_ptr = paths[ctr2];
			paths[ctr2] = ft_strsub(paths[ctr2],
				5, (ft_strlen(paths[ctr2]) - 5));
			free(free_ptr);
		}
		if (paths[ctr2][0] != '/')
		{
			free_ptr = paths[ctr2];
			paths[ctr2] = ft_strjoin("/", paths[ctr2]);
			free(free_ptr);
		}
		free_ptr = paths[ctr2];
		paths[ctr2] = ft_strjoin(paths[ctr2], "/");
		free(free_ptr);
		free_ptr = paths[ctr2];
		paths[ctr2] = ft_strjoin(paths[ctr2], args[0]);
		free(free_ptr);
		ctr2++;
	}
}

char				**check_paths(char **args, int ctr)
{
	char			**paths;
	int				ctr2;
	char			*free_ptr;

	ctr2 = 0;
	paths = ft_strsplit(g_my_env[ctr], ':');
	free_ptr = NULL;
	pp(paths, args, ctr2, free_ptr);
	return (paths);
}

char				**get_paths(char **args)
{
	int				ctr;
	char			**paths;

	paths = NULL;
	ctr = 0;
	while (g_my_env[ctr])
	{
		if ((ft_strncmp(g_my_env[ctr], "PATH=", 5)) == 0)
		{
			paths = check_paths(args, ctr);
		}
		ctr++;
	}
	return (paths);
}
