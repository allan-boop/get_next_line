/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahans <allan.hans68350@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:19:26 by ahans             #+#    #+#             */
/*   Updated: 2023/11/21 11:12:13 by ahans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup(const char *source)
{
	size_t	i;
	char	*new;

	i = 0;
	if (!source)
		return (NULL);
	new = (char *)malloc(sizeof(char) * ft_strlen(source) + 1);
	if (!new)
		return (NULL);
	while (*source)
		new[i++] = *source++;
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	all_size;

	if (!s1 || !s2)
	{
		if (s1)
			return (ft_strdup(s1));
		else if (s2)
			return (ft_strdup(""));
		return (NULL);
	}
	all_size = ft_strlen(s2) + ft_strlen(s1);
	str = (char *)malloc((all_size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;

	if (!s)
		return ;
	str = s;
	while (n--)
	{
		*str = 0;
		str++;
	}
	return ;
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	if (!s)
		return ((char *)0);
	i = 0;
	while (s[i])
		i++;
	if (start > i)
		len = 0;
	if (len > i - start)
		len = i - start;
	substr = (char *)malloc(sizeof(char) *(len + 1));
	if (!substr)
		return (substr);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
