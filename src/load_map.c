/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:26:57 by cmateos-          #+#    #+#             */
/*   Updated: 2024/09/28 15:26:58 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/cub3d.h"

void readmap(t_data *data, char *file)
{
    char    *line;
    // t_map	*map;

    // line = data->map->line;
    data->map->fd = open(file, O_RDONLY);
    if (data->map->fd < 0)
        exit(1);
    if ((line = (char *)malloc(sizeof(char))) == NULL)
        exit(1);
    while (1)
    {
        printf("reading map\n");
        line = get_next_line(data->map->fd);
        if (line == NULL)
            perror("error: cannot read map\n"), exit(1);
        printf("line:%s\n", line);
        if (line && check_emptyorspace(line) == 0)
        {
            printf("linea no vacía\n");
            
        }
        if (line == NULL)
            break ;
        free(line);
    }
    free(line);
    close(data->map->fd);
    //segmentation fault ?? 
}

void load_map(t_data *data, char *file)
{

    // if (!map)
    //     exit(1);
    readmap(data, file);

}