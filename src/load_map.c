/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:26:57 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/01 21:05:18 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>



int check_player_direction(t_data *data, char c, int row, int i)
{
    if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
        return (1);
    else
    {
        data->player->player_dir = c;
        data->player->player_count += 1 ;
        data->player->y = row;
        data->player->x = i;
    }
    return (0);
}


void check_content_map_and_save_player_dir(t_data *data, char *line, int row)
{
    int i;

    i = 0;
    if (line && line[i])
    {
        while (line[i])
        {
            if (line[i] && line[i] != '0' && line[i] != '1' && line[i] != ' ' && line[i] != '\n')
            {
                if (check_player_direction(data, line[i], row, i))
                    err(RED"error: invalid map: Bad character\n"RESET), exit(1); //freee
            }
            i++;
        }
    }
    if (data->map->width < i)
        data->map->width = i - 1;
}


void readmap(t_data *data, char *file)
{
    char    *line;
    int     i;

    i = 0;
    if ((line = (char *)malloc(sizeof(char))) == NULL)
        exit(1);
    while (1)
    {
        line = get_next_line(data->map->fd);
        if (line && !check_emptyorspace(line))
        {
            if (data->map->num_elem != 6)
                save_data_map(data, line);
            else
            {
                check_content_map_and_save_player_dir(data, line, i);
                save_map(data, line);
                i++;
            }
        }
        if (line == NULL)
            break ;
        free(line);
    }
    free(line);
    data->map->height = i;
}

void load_map(t_data *data, char *file)
{
    data->map->fd = open(file, O_RDONLY);
    if (data->map->fd < 0)
        exit(1);
    readmap(data, file);
    close(data->map->fd);
    if (data->map->num_elem != 6)
        err(RED"error: map: invalid elements count\n"RESET), exit(1); //free
    if (data->player->player_count != 1)
        err(RED"error: invalid map: Enter a player\n"RESET), exit(1); //freee 
    printf(YELLOW"\nplayer_direction:%c\n\n"RESET, data->player->player_dir);
    if (!map_closed(data->map->map, data->player->x, data->player->y) || !check_valid_map(data))
        printf(RED"error: Map is not closed\n"RESET), exit(1);
    ft_printarray(data->map->map); //PRINT data->map-> char **map
    printf(BLUE"\nPlayer position: [%d][%d]\n"RESET, data->player->y, data->player->x); //PRINTF
    printf(GREEN"\nMap height: %d\n"RESET, data->map->height); //PRINTF
    printf(GREEN"Map width: %d\n"RESET, data->map->width); //PRINTF
}