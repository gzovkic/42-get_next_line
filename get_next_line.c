/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrijel <gabrijel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 08:25:21 by gabrijel          #+#    #+#             */
/*   Updated: 2024/11/04 18:04:25 by gabrijel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *make_str(int count, char *str, char *buffer);

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    int buffer_check;
    int count;
    char *str;

    str = NULL;
    count = 0;
    while((buffer_check = read(fd,buffer,BUFFER_SIZE)) > 0)
    {
        count = 0;
        while(count < buffer_check)
        {
            str = make_str(count, str, buffer);
            if(buffer[count] == '\n')
            return(str);
            count++;
        }
    }
    if(str )
    
}

char *make_str(int count, char *str, char *buffer, int *total_size, int *str_count)
{
    int str_count;
    int total_size;
    char *temp;
    
    total_size = 0;
    str_count = 0;
    if(str_count + 1 >= total_size)
    {
        total_size += BUFFER_SIZE;
        temp = ft_calloc(str_count + 1, sizeof(char));
        if(!temp)
        {
            free(str);
            return(NULL);
        }
        str[str_count] = buffer[count];
        str_count++;
    }
    return(str);    
}
        