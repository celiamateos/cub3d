/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:23:33 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/13 20:10:36 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char *ft_search_element(char **element)
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
    int     *result;
    char    **tmp;

    result = 0;
    tmp = ft_split(str, ',');
    if (!tmp || (ft_arraylen(tmp) != 3))
        err(RED"error: element map: ceiling or floor\n"RESET), exit(1); //free y tal
    result = ft_calloc(3, sizeof(int));
    if (!result)
        err(RED"error: element map: malloc\n"RESET), exit(1); //free y tal    
    result[0] = ft_atoi(tmp[0]);
    result[1] = ft_atoi(tmp[1]);
    result[2] = ft_atoi(tmp[2]);

    if (result[0] < 0 || result[0] > 255 || result[1] < 0 || result[1] > 255 || result[2] < 0 || result[2] > 255)
        err(RED"error: element map: bad rgb params\n"RESET), exit(1); //free y tal
    ft_freearray(tmp);
    return (result);
}

void save_colors_map(t_map *map, char ***elements)
{
    char **element;

    element = *elements;
    if (!ft_strncmp(element[0], "C", ft_strlen(element[0])))
    {
        if ((map->ceiling_route = load_data_color_map(element[1])) && !map->ceiling_route)
            err(RED"error: invalid map\n"RESET), ft_freearray(element), exit(1); //free..
        printf(GREEN"ceiling_route:"RESET);
        ft_printintarray(map->ceiling_route, 3);
    }
    else if (!ft_strncmp(element[0], "F", ft_strlen(element[0])))
    {
        if ((map->floor_route = load_data_color_map(element[1])) && !map->floor_route)
            err(RED"error: invalid map\n"RESET), ft_freearray(element), exit(1); //free..
        printf(GREEN"floor_route:"RESET);
        ft_printintarray(map->floor_route, 3);
    }
    else
        err(RED"error: map: invalid elements\n"RESET), ft_freearray(element), exit(1);
    map->num_elem += 1;
}

void save_element_map(t_map *map, char ***elements)
{
    char **element;

    element = *elements;
    if (!map->north_route && !ft_strncmp(element[0], "NO", ft_strlen("NO")))
    {
        if ((map->north_route = ft_search_element(element)) == NULL)
            ft_freearray(element), exit(1); //free..
        printf(GREEN"north_route:%s\n"RESET, map->north_route);
    }
    else if (!map->south_route && !ft_strncmp(element[0], "SO", ft_strlen("SO")))
    {
        if ((map->south_route = ft_search_element(element)) == NULL)
            ft_freearray(element), exit(1); //free..
        printf(GREEN"south_route:%s\n"RESET, map->south_route);
    }
    else if (!map->east_route && !ft_strncmp(element[0], "EA", ft_strlen("EA")))
    {
        if ((map->east_route = ft_search_element(element)) == NULL)
            ft_freearray(element), exit(1); //free..
        printf(GREEN"east_route:%s\n"RESET, map->east_route);
    }
    else if (!map->west_route && !ft_strncmp(element[0], "WE", ft_strlen("WE")))
    {
        if ((map->west_route = ft_search_element(element)) == NULL)
            ft_freearray(element), exit(1); //free..
        printf(GREEN"west_route:%s\n"RESET, map->west_route);
    }
    else
        err(RED"error: map: invalid elements\n"RESET), ft_freearray(element), exit(1); //free..
    map->num_elem += 1;
}

void save_data_map(t_map *map, char *line)
{
    char    **element;

    element = ft_split(line, ' ');
    if (!element)
        exit(1); //Free data
    printf(BLUE"map->num_elem:%d\n"RESET, map->num_elem);
    if (map->num_elem < 4)
        save_element_map(map, &element);
    else if (map->num_elem < 6)
        save_colors_map(map, &element);
    ft_freearray(element);
}
