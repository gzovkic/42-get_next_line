/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:54:14 by gzovkic           #+#    #+#             */
/*   Updated: 2024/11/11 23:13:28 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd);
char	*make_str(char *buffer);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *c);
char	*leftover_check(char *buffer);
char	*ft_strchr(const char *s, int c);

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			buffer_check;
	static char	*str;
	char 		*str2;
	static char	*buffer_leftovers;
	int			newline_check;

	newline_check = 0;
	if(buffer_leftovers)
	{
		str = make_str(buffer_leftovers);
		buffer_leftovers = leftover_check(buffer_leftovers);
		if(ft_strchr(str, '\n') || ft_strchr(str, '\0'))
			return (str);
					if(ft_strchr(buffer_leftovers, '\0'))
			free(buffer_leftovers);
		str = ft_strjoin(str, buffer_leftovers);
	}
	while (newline_check == 0)
	{
		buffer_check = read(fd, buffer, BUFFER_SIZE);
		if(buffer_check < 0)
			return(NULL);
		if(buffer_check == 0)
		{
			if(str == NULL || str[0] == '\0')
			{
				free(str);
				return(NULL);
			}
			newline_check = 1;
		}
		buffer[buffer_check] = '\0';
		if (str == NULL)
			str = make_str(buffer);
		else
		{
			str2 = ft_strjoin(str, buffer);
			str = str2;
		}
		if(ft_strchr(str, '\n'))
			newline_check = 1;
	}	
	buffer_leftovers = leftover_check(buffer);
	buffer_leftovers[ft_strlen(buffer_leftovers)] = '\0';
	// if(ft_strlen(buffer_leftovers) < 0)
	// 	free(buffer_leftovers);
	// if (*buffer_leftovers == '\0')
	// 	free(buffer_leftovers);
	return (str);
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
	while (count > count2)
	{
		str[count2] = buffer[count2];
		count2++;
	}
	if(buffer[count2] == '\n')
		str[count2] = '\n';
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
		free(new_line);
	}
	// new_line = get_next_line(fd);
	// printf("%s", new_line);
	return(0);
	}