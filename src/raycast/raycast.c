/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:53:24 by iostancu          #+#    #+#             */
/*   Updated: 2024/11/26 16:20:22 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	rotate_vision(t_player *p, int key);
void	player_controller(mlx_t *mlx, t_player *p);
void detect_vertical_lines(t_player *player, int **grid, int gridWidth, int gridHeight, int screenHeight);
int do_vc_raycast2(t_vec2 pos, double angle, t_map *map, t_player *p);
/**
 * @brief Player control and ray casting. For every ray, distance where the ray
 * hit is saved and used to draw a wall line, after obteining its height.
 * 
 * wall_height = (size * height) / ray_lenght
 * RAY_ANGLE -> where the first ray starts (looking_angle - (FOV/2))
 * 
 * @param param 
 */
void do_raycast(void* param)
{
	t_player	*p;
	double		ray_angle;
	float		dist;
	int			i;
	int			j;
	int			wall_start;
	int			wall_end;
	int			wall_line_height;
	uint32_t	color;
	// char		*str;
	// char		*str2;

	p = (t_player *)param;
	i = -1;
	player_controller(p->map->game->mlx, p);
	draw_background(p->map->game->screen);
	draw_2d_map(p->map);
	color = get_rgba(1, 1, 1, 255);
	ray_angle = p->looking_angle - (p->fov / 2);	// first ray angle
	detect_vertical_lines(p, p->map->grid, p->map->width, p->map->height, p->height_win);
	draw_player(p);
	while (++i < p->width_win)
	{
 		trace_ray(p->position, ray_angle, p->map, p);	// trace ray, save distance
		ray_angle += p->ray_angle;	// next angle
	}
// 	// str2 = ft_itoa(abs(p->looking_angle));
// 	// str = ft_strjoin("Looking angle: ", str2);
// 	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, p->height_win - 210});
// 	// mlx_put_string(p->map->game->mlx, str, WIDTH_WIN - 300, p->height_win - 200);
// 	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, p->height_win - 210});	
// 	// free(str);
// 	// free(str2);
// 	draw_player(p);
}
