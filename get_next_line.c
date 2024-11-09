/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:54:14 by gzovkic           #+#    #+#             */
/*   Updated: 2024/11/09 15:04:00 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*make_str(char *buffer);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
size_t	ft_strcpy(char *dst, const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *c);
char	*leftover_check(char *buffer);

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			buffer_check;
	static char	*str;
	char		*str2;
	static char	*buffer_leftovers;

	str = NULL;
	str2 = NULL;
	if (buffer_leftovers)
	{
		str = make_str(buffer_leftovers);
		buffer_leftovers = leftover_check(buffer_leftovers);
		if(str)
			return (str);
	}
	while ((buffer_check = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[buffer_check] = '\0';
		if (str2 == NULL && str == NULL)
		{
			str = make_str(buffer);
			buffer_leftovers = leftover_check(buffer);
		}
		else
		{
			str2 = make_str(buffer);
			buffer_leftovers = leftover_check(buffer);
		}
		if (str != NULL && str2 != NULL && buffer_leftovers[0] == '\0')
			str = ft_strjoin(str, str2);
		else if (str2 != NULL && buffer_leftovers[0] != '\0')
			str = ft_strjoin(buffer_leftovers, str2);
		if (!str)
			return (NULL);
		
	}
	
	return (NULL);

}
char	*make_str(char *buffer)
{
	char			*str;
	unsigned int	count;
	unsigned int	count2;

	count = 0;
	count2 = 0;
	while (buffer[count] != '\n' && buffer[count] != '\0')
		count++;
	str = ft_calloc(count + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (count > 0)
	{
		str[count2] = buffer[count2];
		count--;
		count2++;
	}
	return (str);
}

char	*leftover_check(char *buffer)
{
	int		count;
	int		count2;
	char	*str;

	count = 0;
	count2 = 0;
	while (buffer[count] != '\n' && buffer[count] != '\0')
		count++;
	if(buffer[count] == '\0')
		return(NULL);
	str = ft_calloc(ft_strlen(buffer) - count + 1, sizeof(char));
	if (!str)
		return (NULL);
	count++;
	while (buffer[count] != '\0')
	{
		str[count2] = buffer[count];
		count++;
		count2++;
	}
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

int	main(void)
{
	char *new_line;
	int fd;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		printf("ERROR OPENING FILE");
	while (1)
	{
		new_line = get_next_line(fd);
		if (!new_line)
			break ;
		printf("%s", new_line);
	}
}