/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgba_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:53:28 by iostancu          #+#    #+#             */
/*   Updated: 2024/12/02 01:02:54 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t get_pixel(mlx_texture_t *texture, int x, int y)
{
	int		px_index;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
	uint32_t	color;

    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return 0;	// black
    px_index = (y * (texture->width ) + x) * texture->bytes_per_pixel; // 4 bytes x píxel (RGBA)
    r = texture->pixels[px_index];
    g = texture->pixels[px_index + 1];
    b = texture->pixels[px_index + 2];
    a = texture->pixels[px_index + 3];
    color = (r << 24) | (g << 16) | (b << 8) | a;
    return (color);
}
