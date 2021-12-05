/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darian <darian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:22:47 by darian            #+#    #+#             */
/*   Updated: 2021/11/29 21:08:29 by darian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*str = NULL;
	char		*tmp;
	int			read_val;

	read_val = 1;
	str = init_line(str);
	if (check_error(fd) == NULL)
		return (NULL);
	while (read_val > 0 && (ft_strchr(str, '\n') == NULL))
		str = read_fd(fd, str, &read_val);
	ret = ft_substr(str, 0, ft_strlen_newline(str) + 1);
	tmp = str;
	str = ft_substr(tmp, ft_strlen_newline(str) + 1, ft_strlen(str)
			- ft_strlen_newline(str));
	free(tmp);
	if (ret[0] == 0)
	{
		free(ret);
		ret = NULL;
		return (NULL);
	}
	return (ret);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	// (void)argv;
// 	int fd = open(argv[1], 100);
// 	// int fd = 1000;
// 	char *lol;
// 	for (int i = 0; i < 9; i++)
// 	{
// 		lol = get_next_line(fd);
// 		if (lol != NULL)
// 			printf("%s", lol);
// 		free(lol);
// 	}
// 	return (0);
// }