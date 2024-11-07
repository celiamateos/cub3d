/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:02:46 by iostancu          #+#    #+#             */
/*   Updated: 2024/11/06 19:51:03 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/**
 * @brief for minimap
 * 
 * @param param 
 */
void	draw_player(void *param)
{
	t_player	*p;
	t_vec2		pos;
	int			color;
	int			x;
	int			y;
	int			size_y;
	int			size_x;

	p = (t_player *)param;
	if (!p || !p->map || !p->map->game || !p->map->game->screen)
	{
		perror("Error: NULL\n");
		return ;
	}
	size_x = MINIMAP_SIZE / 2;
	size_y = MINIMAP_SIZE / 2;
	pos.x = (p->position.x * MINIMAP_SIZE) + size_x + (size_x / 2);
	pos.y = (p->position.y * MINIMAP_SIZE) + size_y + (size_y / 2);
	color = get_rgba(255, 0, 0, 255);
	y = 0;
	while (y < size_x)
	{
		x = 0;
		while (x < size_y)
		{
			mlx_put_pixel(p->map->game->screen, pos.x + x, pos.y + y, color);
			x++;
		}
		y++;
	}
}
