/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:15:35 by cmateos-          #+#    #+#             */
/*   Updated: 2024/09/26 18:15:36 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/cub3d.h"

void err(char *str)
{
    while(*str)
        write(2, str++, 1);
}

// clean_data()

// int exit(t_map *map, char *err)
// {
//     clean_data()
// }