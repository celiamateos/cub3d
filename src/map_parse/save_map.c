/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:23:33 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/14 21:22:10 by settes           ###   ########.fr       */
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

// // 'Encodes' four individual bytes into an int.
// int get_rgba(int r, int g, int b, int a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

int colorToInt(int red, int green, int blue)
{
    // Nos aseguramos de que los valores estén en el rango válido 0-255
    if (red < 0)
        red = 0;
    if (red > 255)
        red = 255;
    if (green < 0)
        green = 0;
    if (green > 255)
        green = 255;
    if (blue < 0)
        blue = 0;
    if (blue > 255)
        blue = 255;

    // Combinamos los colores en un solo entero de 24 bits
    return ((red << 16) | (green << 8) | blue);
}

int load_data_color_map(char *str)
{
    int     *result;
    char    **tmp;
    int color;

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
    color = colorToInt(result[0], result[1], result[2]);
    ft_freearray(tmp);
    free(result);
    return (color);
}

void save_colors_map(t_map *map, char ***elements)
{
    char **element;
    int rgb;

    element = *elements;
    if (!ft_strncmp(element[0], "C", ft_strlen(element[0])))
    {
        if ((rgb = load_data_color_map(element[1])) < 0)
            err(RED"error: invalid ceiling color\n"RESET), ft_freearray(element), exit(1); //free..
        map->ceiling_color = rgb;
        printf(GREEN"ceiling_route:%d\n"RESET, map->ceiling_color);
    }
    else if (!ft_strncmp(element[0], "F", ft_strlen(element[0])))
    {
        if ((rgb = load_data_color_map(element[1])) < 0)
            err(RED"error: invalid floor color\n"RESET), ft_freearray(element), exit(1); //free..
        map->floor_color = rgb;
        printf(GREEN"floor_route:%d\n"RESET, map->floor_color);
    }
    else
        err(RED"error: map: invalid elements\n"RESET), ft_freearray(element), exit(1);
    map->num_elem += 1;
}

void charge_texture(t_game *game, mlx_texture_t **tex, mlx_image_t **img, char *dir)
{
    *tex = mlx_load_png(dir);
    if (!tex)
        err("MIERDA JAJA");
    *img = mlx_texture_to_image(game->mlx, *tex);
    if (!img)
        err("MIERDA 2");
}

void save_element_map(t_map *map, char ***elements)
{
    char **element;
    char    *dir;

    element = *elements;
    if (!ft_strncmp(element[0], "NO", ft_strlen("NO")))
    {
        if ((dir = ft_search_element(element)) == NULL)
            ft_freearray(element), exit(1); //free..
        printf(GREEN"north_route:%s\n"RESET, dir);
        charge_texture(map->game, &map->textures.no, &map->images.no, dir);
        free(dir);

    }
    else if (!ft_strncmp(element[0], "SO", ft_strlen("SO")))
    {
        if ((dir = ft_search_element(element)) == NULL)
            ft_freearray(element), exit(1); //free..
        charge_texture(map->game, &map->textures.so, &map->images.so, dir);
        printf(GREEN"south_route:%s\n"RESET, dir);
        free(dir);
    }
    else if (!ft_strncmp(element[0], "EA", ft_strlen("EA")))
    {
        if ((dir = ft_search_element(element)) == NULL)
            ft_freearray(element), exit(1); //free..
        charge_texture(map->game, &map->textures.ea, &map->images.ea, dir);
        printf(GREEN"east_route:%s\n"RESET, dir);
        free(dir);
    }
    else if (!ft_strncmp(element[0], "WE", ft_strlen("WE")))
    {
        if ((dir = ft_search_element(element)) == NULL)
            ft_freearray(element), exit(1); //free..
        charge_texture(map->game, &map->textures.we, &map->images.we, dir);
        printf(GREEN"west_route:%s\n"RESET, dir);
        free (dir);
    }
    else
        err(RED"error: map: invalid elements\n"RESET), ft_freearray(element), exit(1); //free..
    map->num_elem += 1;
}

int save_data_map(t_map *map, char *line)
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
    return (0);
}
