/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:04:40 by yboumlak          #+#    #+#             */
/*   Updated: 2024/01/11 18:37:37 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*process_line(char **stash)
{
	int		i;
	char	*line;
	char	*deref;

	i = 0;
	deref = *stash;
	if (stash && deref)
	{
		while (deref[i])
		{
			if (ft_strchr("\n", deref[i]))
				return (ft_substr(deref, 0, i + 1));
			i++;
		}
		if (deref[i] == '\0')
		{
			line = ft_substr(deref, 0, i);
			free(deref);
			*stash = NULL;
			return (line);
		}
	}
	return (NULL);
}

char	*update_stash(char *stash)
{
	int		i;
	char	*ret;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i])
	{
		if (stash[i] == '\n')
		{
			ret = ft_substr(stash, i + 1, ft_strlen(stash) - i);
			free(stash);
			stash = NULL;
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	*read_file(int fd, char *stash)
{
	int		read_bytes;
	char	buffer[BUFFER_SIZE + 1];

	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_file(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = process_line(&stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = update_stash(stash[fd]);
	return (line);
}

// int main(void)
// {
// 	int fd1 = open("file1.txt", O_RDONLY);
// 	int fd2 = open("file2.txt", O_RDONLY);
// 	char *line;

// 	if (fd1 == -1 || fd2 == -1)
// 	{
// 		perror("Error opening file");
// 		return 1;
// 	}

// 	while ((line = get_next_line(fd1)) != NULL)
// 	{
// 		printf("File1: %s", line);
// 		free(line);
// 	}

// 	while ((line = get_next_line(fd2)) != NULL)
// 	{
// 		printf("File2: %s", line);
// 		free(line);
// 	}

// 	close(fd1);
// 	close(fd2);

// 	return 0;
// }