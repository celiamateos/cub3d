/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:01:29 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/03 12:01:30 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

int ft_arraylen(char **array)
{
    int i;

    i = 0;
    while (array[i])
        i++;
    return i;
}

void ft_printarray(char **arr)
{
    int i;

    i = 0;
    if (!arr || !arr[i])
        return err(RED"no existe el array mapa\n"RESET);
    while(arr[i])
        printf(PURPLE"%s\n"RESET, arr[i++]);
}