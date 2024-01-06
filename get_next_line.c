/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:04:40 by yboumlak          #+#    #+#             */
/*   Updated: 2024/01/06 15:41:00 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	append_line(void)
{
	
}

char	*get_next_line(int fd)
{
	char		*buffer;
	ssize_t		read_size;
	static char	*line;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_size = read(fd, buffer, BUFFER_SIZE);
	if (read_size <= 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[read_size] = '\0';
	line = append_line();
	return (line);
}

int	main(void)
{
	char	*buffer;
	int		fd;

	fd = open("get_next_line.txt", O_RDONLY);
	buffer = get_next_line(fd);
	printf("%s", buffer);
}
