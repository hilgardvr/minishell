/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 08:12:51 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/07/28 16:08:12 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				sh_launch(char **args, int ctr)
{
	pid_t		pid;
	char		**paths;

	pid = fork();
	paths = NULL;
	if (pid < 0)
		ft_printf("Error forking process");
	else if (pid == 0)
	{
		execve(args[0], args, g_my_env);
		paths = get_paths(args);
		if (paths)
			while (paths[ctr])
			{
				execve(paths[ctr], args, g_my_env);
				ctr++;
			}
		ft_printf("Error: Command not found\n");
		free_2d(&paths);
		return (0);
	}
	else if (pid > 0)
		wait(NULL);
	return (1);
}

int				sh_execute(char **args)
{
	int			ctr;

	ctr = 0;
	if (args[0] == NULL)
		return (1);
	if ((ft_strcmp(args[0], "exit") == 0) || (ft_strcmp(args[0], "q") == 0))
		return (0);
	if (ft_strcmp(args[0], "cd") == 0)
		return (sh_cd(args));
	if (ft_strcmp(args[0], "setenv") == 0 || ft_strcmp(args[0], "export") == 0)
		return (sh_setenv(args[1]));
	if (ft_strcmp(args[0], "unset") == 0 || ft_strcmp(args[0], "unsetenv") == 0)
		return (sh_unset(args));
	if (ft_strcmp(args[0], "env") == 0)
		return (sh_env());
	if (ft_strncmp(args[0], "echo", 4) == 0)
		return (sh_echo(args));
	return (sh_launch(args, ctr));
}

void			handle_args(char **args, int ctr)
{
	int			temp_ctr;
	char		*temp_str;

	while (args[ctr])
	{
		temp_str = args[ctr];
		args[ctr] = ft_strtrim(args[ctr]);
		free(temp_str);
		if (ft_strcmp(args[ctr], "\0") == 0)
		{
			temp_ctr = ctr;
			while (args[ctr])
			{
				free(args[ctr]);
				if (args[ctr + 1] != NULL)
					args[ctr] = ft_strdup(args[ctr + 1]);
				else
					args[ctr] = NULL;
				ctr++;
			}
			ctr = temp_ctr - 1;
		}
		ctr++;
	}
}

void			sh_loop(void)
{
	char		*line;
	char		**args;
	int			status;
	int			sub_ctr;

	status = 1;
	line = NULL;
	args = NULL;
	sub_ctr = 0;
	while (status)
	{
		ft_printf("mini$>");
		if (get_next_line(0, &line) < 0)
			ft_printf("Unable to read line from stdin\n");
		args = ft_strsplit_shell(line);
		handle_args(args, sub_ctr);
		status = sh_execute(args);
		free(line);
		free_2d(&args);
	}
}

int				main(void)
{
	extern char	**environ;
	int			ctr;

	ctr = 0;
	while (environ[ctr])
		ctr++;
	g_my_env = (char **)ft_memalloc(sizeof(char **) * (ctr + 1));
	ctr = 0;
	while (environ[ctr])
	{
		g_my_env[ctr] = ft_strdup(environ[ctr]);
		ctr++;
	}
	g_my_env[ctr] = NULL;
	sh_loop();
	free_2d(&g_my_env);
	return (0);
}
