/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:37:38 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/23 14:37:40 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

mlx_image_t* create_colored_image(mlx_t* mlx, int width, int height, uint32_t color)
{
    mlx_image_t* img;
    int x;
    int y;

    x = -1;
    y = -1;
    img = mlx_new_image(mlx, width, height);
    if (!img)
    {
        err(RED"Error\n Cannot create colored image\n"RESET);
        return (NULL);
    }
    while (++y < height)
    {
        while (++x < width)
            mlx_put_pixel(img, x, y, color);
        x = -1;
    }
    return (img);
}

uint32_t int_to_rgba(int rgb_color)
{
    return (0xFF << 24) | (rgb_color & 0x00FFFFFF);
}

void draw_background(void *param)
{
    t_map *map;
    int height;
    int width;
    uint32_t color;

    height = HEIGHT_WIN;
    width = WIDTH_WIN;
	map = (t_map *)param;
    color = int_to_rgba(map->ceiling_color);
    map->images.c = create_colored_image(map->game->mlx, width, (height / 2), color);
    if (!map->images.c)
    {
        mlx_terminate(map->game->mlx);
    }
    color = int_to_rgba(map->floor_color);
    map->images.f = create_colored_image(map->game->mlx, width, (height / 2), color);
    if (!map->images.f)
    {
        mlx_terminate(map->game->mlx);
        //EXIT??
    }
}