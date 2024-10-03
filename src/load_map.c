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

char *ft_search_element(char **element, char *elem)
{
    char    *dir;
    int     fd;

    dir = ft_substr(element[1], 0, (ft_strlen(element[1]) - 1));
    if (!dir)
        return (err(RED"error: malloc\n"RESET)), NULL; //free
    fd = open(dir, O_RDONLY);
    if (fd < 0)
        return err(RED "error: map: fd: invalid element route\n" RESET), NULL;
    return (dir);
}

int *load_data_color_map(char *str)
{
    int *result;

    char **tmp = ft_split(str, ',');
    if (!tmp || (ft_arraylen(tmp) != 3))
        err(RED"error: element map: ceiling or floor\n"RESET), exit(1); //free y tal
    result[0] = ft_atoi(tmp[0]);
    result[1] = ft_atoi(tmp[1]);
    result[2] = ft_atoi(tmp[2]);

    if (result[0] < 0 || result[0] > 255 || result[1] < 0 || result[1] > 255 || result[2] < 0 || result[2] > 255)
        err(RED"error: element map: bad rgb params\n"RESET), exit(1); //free y tal
    ft_freearray(tmp);
    return (result);
}

void save_colors_map(t_data *data, char ***elements)
{
    char **element = *elements;
    if (!data->map->ceiling_route && !ft_strncmp(element[0], "C", ft_strlen(element[0])))
    {
        if ((data->map->ceiling_route = load_data_color_map(element[1])) && !data->map->ceiling_route)
            err(RED"error: invalid map\n"RESET), ft_freearray(element), exit(1); //free..
        printf(GREEN"ceiling_route:%ls\n"RESET, data->map->ceiling_route);
    }
    else if (!data->map->floor_route && !ft_strncmp(element[0], "F", ft_strlen(element[0])))
    {
        if ((data->map->floor_route = load_data_color_map(element[1])) && !data->map->floor_route)
            err(RED"error: invalid map\n"RESET), ft_freearray(element), exit(1); //free..
        printf(GREEN"floor_route:%ls\n"RESET, data->map->floor_route);
    }
    else
        err(RED"error: map: invalid elements\n"RESET), ft_freearray(element), exit(1);
    data->map->num_elem += 1;
}

void save_element_map(t_data *data, char ***elements)
{
    char **element = *elements;

    if (!data->map->north_route && !ft_strncmp(element[0], "NO", ft_strlen(element[0])))
    {
        if ((data->map->north_route = ft_search_element(element, "NO")) && !data->map->north_route)
            err(RED"error: invalid map\n"RESET), ft_freearray(element), exit(1); //free..
        printf(GREEN"north_route:%s\n"RESET, data->map->north_route);
    }
    else if (!data->map->south_route && !ft_strncmp(element[0], "SO", ft_strlen(element[0])))
    {
        if ((data->map->south_route = ft_search_element(element, "SO")) && !data->map->south_route)
            err(RED"error: invalid map\n"RESET), ft_freearray(element), exit(1); //free..
        printf(GREEN"south_route:%s\n"RESET, data->map->south_route);
    }
    else if (!data->map->east_route && !ft_strncmp(element[0], "EA", ft_strlen(element[0])))
    {
        if ((data->map->east_route = ft_search_element(element, "EA")) && !data->map->east_route)
            err(RED"error: invalid map\n"RESET), ft_freearray(element), exit(1); //free..
        printf(GREEN"east_route:%s\n"RESET, data->map->east_route);
    }
    else if (!data->map->west_route && !ft_strncmp(element[0], "WE", ft_strlen(element[0])))
    {
        if ((data->map->west_route = ft_search_element(element, "WE")) && !data->map->west_route)
            err(RED"error: invalid map\n"RESET), ft_freearray(element), exit(1); //free..
        printf(GREEN"west_route:%s\n"RESET, data->map->west_route);
    }
    else
        err(RED"error: map: invalid elements\n"RESET), ft_freearray(element), exit(1); //free..
    data->map->num_elem += 1;
}

void save_data_map(t_data *data, char *line)
{
    char **element = ft_split(line, ' ');
    if (!element)
        exit(1); //Free data
    printf(BLUE"data->map->num_elem:%d\n"RESET, data->map->num_elem);
    if (data->map->num_elem < 4)
        save_element_map(data, &element);
    else if (data->map->num_elem < 6)
        save_colors_map(data, &element);
    ft_freearray(element);
}

int check_player_direction(t_data *data, char c)
{
    if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
        return (1);
    else
    {
        data->player->player_dir = c;
        data->player->player_count += 1 ;
    }
    return (0);
}

int check_content_map_and_save_player_dir(t_data *data, char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] && line[i] != '0' && line[i] != '1' && line[i] != ' ' && line[i] != '\n')
        {
            if (check_player_direction(data, line[i]))
                err(RED"error: invalid map: Bad character\n"RESET), exit(1); //freee
        }
        //aqui puedo ir modificando line y convirtiendo los espacios en algo ???
        i++;
    }
}

void readmap(t_data *data, char *file)
{
    char    *line;
    int     i;

    i = 0;
    data->map->fd = open(file, O_RDONLY);
    if (data->map->fd < 0)
        exit(1);
    if ((line = (char *)malloc(sizeof(char))) == NULL)
        exit(1);
    while (1)
    {
        line = get_next_line(data->map->fd);
        if (line && !check_emptyorspace(line))
        {
            // printf("line:%s", line);
            if (data->map->num_elem != 6)
                save_data_map(data, line);
            else
            {
                check_content_map_and_save_player_dir(data, line);
                printf("line:%s", line);
                // data->map->map[i] = ft_strdup(line); //Segfault aqui
                // i++;
            }
        }
        if (line == NULL)
            break ;
        free(line);
    }
    free(line);
    close(data->map->fd);
    // data->map->map[i] = NULL;
}

void load_map(t_data *data, char *file)
{
    readmap(data, file);
    if (data->map->num_elem != 6)
        err(RED"error: map: invalid elements count\n"RESET), exit(1); //free
    if (data->player->player_count != 1)
        err(RED"error: invalid map: Enter a player\n"RESET), exit(1); //freee 
    printf(YELLOW"\nplayer_direction:%c\n"RESET, data->player->player_dir);
    // ft_printarray(data->map->map);
}