/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:12:30 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/16 22:58:48 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	set_looking_angle(char dir, double *angle)
{
	if (dir == 'N')
		*angle = 90;
	else if (dir == 'E')
		*angle = 360;
	else if (dir == 'S')
		*angle = 270;
	else if (dir == 'W')
		*angle = 180;
}

void	set_spawn_position(double x, double y, t_vec2 *player_pos)
{
	player_pos->x = x;
	player_pos->y = y;
}
