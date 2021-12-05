/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darian <darian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:47:40 by darian            #+#    #+#             */
/*   Updated: 2021/11/29 21:14:06 by darian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*check_error(int fd)
{
	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	return ("\0");
}

int	ft_strlen_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

char	*init_line(char *line)
{
	if (line == NULL)
		return (NULL);
	else
		return (line);
}

char	*read_fd(int fd, char *str, int *read_val)
{
	char		*tmp;
	char		*buff;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	*read_val = read(fd, buff, BUFFER_SIZE);
	if (*read_val == -1)
		return (NULL);
	buff[*read_val] = 0;
	tmp = str;
	str = ft_strjoin(tmp, buff);
	free(tmp);
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*ret;
	static t_fd	fds[5000];
	char		*tmp;
	int			read_val;

	read_val = 1;
	fds[fd].fd = fd;
	fds[fd].str = init_line(fds[fd].str);
	if (check_error(fds[fd].fd) == NULL)
		return (NULL);
	while (read_val > 0 && (ft_strchr(fds[fd].str, '\n') == NULL))
		fds[fd].str = read_fd(fds[fd].fd, fds[fd].str, &read_val);
	ret = ft_substr(fds[fd].str, 0, ft_strlen_newline(fds[fd].str) + 1);
	tmp = fds[fd].str;
	fds[fd].str = ft_substr(tmp, ft_strlen_newline(fds[fd].str)
			+ 1, ft_strlen(fds[fd].str)
			- ft_strlen_newline(fds[fd].str));
	free(tmp);
	if (ret[0] == 0)
	{
		free(ret);
		ret = NULL;
		return (NULL);
	}
	return (ret);
}
