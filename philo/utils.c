/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 20:27:44 by oalananz          #+#    #+#             */
/*   Updated: 2025/06/07 20:28:57 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_bzero(void *s, size_t n)
{
        memset(s, '\0', n);
}

void    *ft_calloc(size_t nmemb, size_t size)
{
        size_t  *p;

        p = malloc (nmemb * size);
        if (p == NULL)
                return (NULL);
        ft_bzero(p, nmemb * size);
        return (p);
}

int     ft_atoi(const char *nptr)
{
        char    *num;
        int             res;
        int             sign;

        sign = 1;
        res = 0;
        num = (char *)nptr;
        while (*num == ' ' || (*num >= 9 && *num <= 13))
                num++;
        if (*num == '-' || *num == '+')
        {
                if (*num == '-')
                {
                        sign *= -1;
                        num++;
                }
                else
                        num++;
        }
        while (*num >= '0' && *num <= '9')
        {
                res = (res * 10) + (*num - '0');
                num++;
        }
        return (res * sign);
}

int     ft_isdigit(int c)
{
        if (c >= 48 && c <= 57)
                return (2048);
        else
                return (0);
}


int all_digits(char **av)
{
    int i;
    int j;

    i = 1;
    while(av[i])
    {
        j = 0;
        while(av[i][j])
        {
            if(ft_isdigit(av[i][j]) == 0)
                return (0);
            j++;      
        }
        i++;
    }
    return (1);
}
