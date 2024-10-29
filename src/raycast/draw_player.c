/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:02:46 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/29 23:36:17 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
	rayY = ((pY / 64) * 64) + (Y.line - pY);
	rayX = (pY - rayY) / -tan(looking angle) + pX;
*/
void	draw_my_first_ray(t_player *player)
{
	t_vec2	ray;
	t_vec2	pos;
	int		color;

	ray.y = ((player->position.y / SIZE) * SIZE) + (/* grid.line.y */ - player->position.y);
	ray.x = (player->position.y - ray.y) / -tan(player->looking_angle) + player->position.x;
	pos.x = ray.x * SIZE + SIZE;
	pos.y = ray.y * SIZE + SIZE;
}

/**
 * @brief minimap (?)
 * 
 * @param param 
 */
void	draw_player(void *param)
{
	t_player	*p;
	t_vec2		pos;
	int			color;
	int x;
	int y;
	int size_y;
	int size_x;

	p = (t_player *)param;
	size_x = MINIMAP_SIZE / 2;
	size_y = MINIMAP_SIZE / 2;
	pos.x = (p->position.x * MINIMAP_SIZE) + size_x + (size_x / 2);
	pos.y = (p->position.y * MINIMAP_SIZE) + size_y + (size_y / 2);
	color = get_rgba(255, 0, 0, 255);
	// p = (t_player *)param;
	// size_x = MINIMAP_SIZE;
	// size_y = MINIMAP_SIZE;
	// pos.x = (p->position.x * MINIMAP_SIZE) + (size_x / 2);
	// pos.y = (p->position.y * MINIMAP_SIZE) + (size_y / 2);
	// color = get_rgba(255, 0, 0, 255);
	
	

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
