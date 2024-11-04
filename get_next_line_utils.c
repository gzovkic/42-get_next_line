/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrijel <gabrijel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 08:30:31 by gabrijel          #+#    #+#             */
/*   Updated: 2024/11/04 12:19:53 by gabrijel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void *ft_calloc(size_t count, size_t size);

void *ft_calloc(size_t count, size_t size)
{
    size_t n;
    void *ptr;
    unsigned char *str;

    n = 0;
    ptr = (void *)malloc(count * size);
    if(!ptr)
        return(NULL);
    str = (unsigned char *)ptr;
    while(n < size * count)
    {
        str[n] = 0;
        n++;
    }
    return(ptr);
}