/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:53:24 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/31 00:02:40 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/**
 * @brief wall_height = (size * height) / ray_lenght
 * 
 * @param param 
 */
void do_raycast(void* param)
{
	t_player	*p;
	double		angle_dist;
    double        ray_angle;
	double		dist;
	int			i;
	int			j;
	int		w_start;
	int		w_end;
	int		w_line_height;
	uint32_t	color;
	// char		*str;
	// char		*str2;

	p = (t_player *)param;
	i = -1;
	draw_background(p->map->game->screen);
	draw_2d_map(p->map);
	printf("ray_angle: %f\n", p->ray_angle);
	// check --> wall_height = (size * height) / ray_lenght
	int k = 0;
	color = get_rgba(1, 1, 1, 255);
    ray_angle = p->ray_angle;
	while (++i < WIDTH_WIN)
	{
		dist = trace_ray(p->position, p->looking_angle, ray_angle, p->map);
		if (dist > 0)
		{
			w_line_height = (int)(HEIGHT_WIN / dist);
			w_start = HALF_HEIGHT - (w_line_height / 2);
			if (w_start < 0) w_start = 0;
			w_end = HALF_HEIGHT + (w_line_height / 2);
			if (w_end >= HEIGHT_WIN) w_end = HEIGHT_WIN - 1;
			//color = get_distance_color(dist);
			j = w_start;
			while (j < w_end)
			{
				mlx_put_pixel(p->map->game->screen, i, j, color);
				j++;
			}
		}
		//trace_ray(p->position, p->looking_angle, ray_angle, p->map);
		ray_angle += p->raycast_angle;
	}
	
	// str2 = ft_itoa(abs(p->looking_angle));
	// str = ft_strjoin("Looking angle: ", str2);
	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, HEIGHT_WIN - 210});
	// mlx_put_string(p->map->game->mlx, str, WIDTH_WIN - 300, HEIGHT_WIN - 200);
	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, HEIGHT_WIN - 210});	
	// free(str);
	// free(str2);
	//trace_ray(p->position, p->looking_angle, p->raycast, p->map);
	
	draw_player(p);
}

