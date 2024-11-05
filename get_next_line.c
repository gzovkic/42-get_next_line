/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:10:21 by gzovkic           #+#    #+#             */
/*   Updated: 2024/11/05 17:24:19 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*make_str(int count, char *str, char *buffer, int *str_count,
			int *total_size);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
size_t	ft_strcpy(char *dst, const char *src);


char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	int			buffer_check;
	int			count;
	char		*str;
	static int	str_count;
	static int	total_size;

	total_size = 0;
	str_count = 0;
	while ((buffer_check = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		count = 0;
		while (count < buffer_check)
		{
			str = make_str(count, str, buffer, &str_count, &total_size);
			if(!str)
				return(NULL);
			if (buffer[count] == '\n')
				return (str);
			count++;
		}
	}
	if(str_count > 0)
		return(str);
	free(str);
	return (NULL);
}

char	*make_str(int count, char *str, char *buffer, int *str_count,
		int *total_size)
{
	char	*temp;

	if (*str_count + 1 >= *total_size) 
	{
    	*total_size += BUFFER_SIZE;
    	temp = ft_calloc(*total_size, sizeof(char));
		if (temp == NULL)
		{
			free(str);
			return (NULL);
		}
		if(str != NULL)
		{
			ft_strcpy(temp, str);
			free(str);
		}
		str = temp;
	}
	str[*str_count] = buffer[count];
	(*str_count)++;
	return (str);
}

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
size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	count;
	size_t	srclen;

	count = 0;
	srclen = 0;
	while (src[srclen] != '\0')
		srclen++;
	while (src[count] != '\0')
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = '\0';
	return (srclen);
}
