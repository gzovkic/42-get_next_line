/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:10:36 by gzovkic           #+#    #+#             */
/*   Updated: 2024/11/13 19:06:09 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *c);
char	*ft_strchr(const char *s, int c);

void	*ft_calloc(size_t count, size_t size)
{
	size_t	num;
	void	*ptr;

	num = 0;
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	while (num < count * size)
	{
		ft_bzero(&ptr[num], size);
		num = num + size;
	}
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			count;
	unsigned char	*loc;

	loc = (unsigned char *)s;
	count = 0;
	while (count < n)
	{
		loc[count] = 0;
		count++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		count;
	int		count2;
	int		sumstr;
	char	*newstr;

	count = 0;
	count2 = 0;
	sumstr = ft_strlen(s1) + ft_strlen(s2);
	newstr = ft_calloc(sumstr + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	while (count + count2 < sumstr)
	{
		if (count < ft_strlen(s1))
		{
			newstr[count] = s1[count];
			count++;
		}
		else if (count2 < ft_strlen(s2))
		{
			newstr[count + count2] = s2[count2];
			count2++;
		}
	}
	return (newstr);
}

int	ft_strlen(const char *c)
{
	int	count;

	count = 0;
	while (c[count] != '\0')
		count++;
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	int				count;
	unsigned char	c2;

	c2 = (unsigned char)c;
	count = 0;
	while (s[count] != '\0')
	{
		if (s[count] == c2)
			return ((char *)&s[count]);
		count++;
	}
	if (c2 == '\0')
		return ((char *)&s[count]);
	return (NULL);
}
