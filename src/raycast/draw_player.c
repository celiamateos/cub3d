/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:02:46 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/22 21:05:45 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_player(void *param)
{
	t_player	*p;
	t_vec2		pos;
	int			color;

	p = (t_player *)param;
	pos.x = p->position.x * SIZE + SIZE;
	pos.y = p->position.y * SIZE + SIZE;
	color = get_rgba(255, 0, 0, 255);
	draw_cube(p->map->game->screen, pos, color);
}
