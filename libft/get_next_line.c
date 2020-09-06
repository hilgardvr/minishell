/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 09:27:55 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/07/08 13:35:44 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*realloc_line(char *line)
{
	char		*temp;

	temp = (char *)ft_memalloc(ft_strlen(line) + BUFF_SIZE + 1);
	if (temp == 0)
		return (0);
	ft_strcpy(temp, line);
	free(line);
	return (temp);
}

static char		get_c(const int fd)
{
	static int	ctr;
	static char	buf[BUFF_SIZE + 1];
	static char	*ptr;
	char		c;

	if (ctr == 0)
	{
		ctr = read(fd, buf, BUFF_SIZE);
		if (ctr <= 0)
			return (ctr);
		ptr = &buf[0];
	}
	c = *ptr;
	ctr--;
	ptr++;
	return (c);
}

int				get_next_line(const int fd, char **line)
{
	size_t		ctr;
	char		temp;

	if (!line || fd < 0 || !(*line = (char *)ft_memalloc(BUFF_SIZE + 1)))
		return (-1);
	ctr = 0;
	while (1)
	{
		temp = get_c(fd);
		if (temp == '\n' || temp == 0 || temp == -1)
			break ;
		(*line)[ctr] = temp;
		ctr++;
		if (ctr % BUFF_SIZE == 0)
		{
			*line = realloc_line(*line);
			if (*line == 0)
				return (-1);
		}
	}
	if (temp == 0 && ctr == 0)
		return (0);
	else if (temp == -1)
		return (-1);
	return (1);
}
