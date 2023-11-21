/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahans <allan.hans68350@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:57:39 by ahans             #+#    #+#             */
/*   Updated: 2023/11/21 11:13:52 by ahans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *string, int searched_char)
{
	if (!string)
		return (NULL);
	while (*string != '\0')
	{
		if (*string == (char)searched_char)
			return ((char *)string);
		string++;
	}
	if ((char)searched_char == '\0')
		return ((char *)string);
	return (NULL);
}

static char	*ft_clean_stash_and_return(char **stash, int fd)
{
	int		end;
	char	*tmp;
	char	*next_line;

	end = 0;
	if (!stash[fd])
		return (NULL);
	while (stash[fd][end] && stash[fd][end] != '\n')
		end++;
	if (stash[fd][end] == '\n' && stash[fd][end])
		end++;
	next_line = ft_substr(stash[fd], 0, end);
	if (next_line == NULL)
		return (NULL);
	tmp = ft_substr(stash[fd], end, (ft_strlen(stash[fd]) - end));
	if (tmp == NULL)
		return (NULL);
	free(stash[fd]);
	stash[fd] = tmp;
	return (next_line);
}

int	case_negative_read(int readed, char **stash, int fd, char *buff)
{
	if (readed < 0)
	{
		if (stash[fd])
		{
			free(stash[fd]);
			stash[fd] = NULL;
		}
		free(buff);
		return (2);
	}
	return (1);
}

int	while_readed(int *readed, char *buff, int fd, char **stash)
{
	char	*tmp;
	int		error;

	while (*readed > 0)
	{
		ft_bzero(buff, BUFFER_SIZE + 1);
		*readed = read(fd, buff, BUFFER_SIZE);
		error = case_negative_read(*readed, stash, fd, buff);
		if (error == 2)
			return (error);
		if (!stash[fd])
			stash[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strdup(stash[fd]);
			if (!tmp)
				return (2);
			free(stash[fd]);
			stash[fd] = ft_strjoin(tmp, buff);
			free(tmp);
		}
		if (ft_strchr(stash[fd], '\n'))
			break ;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*buff;
	int			readed;
	int			error;

	if (fd < 0 || fd > 1024)
		return (NULL);
	readed = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	error = while_readed(&readed, buff, fd, stash);
	if (error == 2)
		return (NULL);
	if (stash[fd] && stash[fd][0] == '\0' && readed == 0)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		free(buff);
		return (NULL);
	}
	free(buff);
	return (ft_clean_stash_and_return(stash, fd));
}
