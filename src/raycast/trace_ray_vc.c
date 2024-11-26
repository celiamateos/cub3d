/* ************************************************************************** */
/*      */
/*:::      ::::::::   */
/*   trace_ray_vc.c  :+:      :+:    :+:   */
/*   +:+ +:+  +:+     */
/*   By: settes <settes@student.42.fr>+#+  +:++#+ */
/*      +#+#+#+#+#+   +#+    */
/*   Created: 2024/11/06 19:56:54 by iostancu   #+#    #+#      */
/*   Updated: 2024/11/10 22:30:31 by settes    ###   ########.fr*/
/*      */
/* ************************************************************************** */

#include <cub3d.h>

t_vec2 get_ray_direction(double angle);
void draw_v_line(mlx_image_t *screen, int x, int start, int end, float dist, int color) ;
// Función para detectar líneas verticales y calcular distancias y alturas
/**
 * @brief 
 * 
 * @param player 
 * @param m 
 * @param mWidth 
 * @param mHeight 
 * @param screenHeight 
 */
void detect_vertical_lines(t_player *player, int **m, int mWidth, int mHeight, int screenHeight) 
{
	t_vec2	ray_dir;
	double	wall_dist;
	t_vec2	delta_dist;
	t_vec2	nxt_line;	// distance to next grid line
	int		map_x;
	int		map_y;
	double	ray_angle;
	int		i;
	int		start;
	int		end;
	int		wall_line_height;
	int		step_x;
	int		step_y;
	int		is_wall;
	double		dist_to_projection;
	double		camera;
	t_vec2		wall;
	t_vec2		ray;

	i = -1;
	ray_angle = player->looking_angle - (player->fov / 2);
	dist_to_projection = (player->width_win / 2) / tan(player->fov / 2 * (M_PI / 180));
	while (++i < player->width_win) 
	{
		camera = 2 * i / (double)player->width_win - 1;
		// ray_dir.x = cos(player->looking_angle +  tan(camera));
		// ray_dir.y = sin(player->looking_angle + tan(camera));
		ray_dir.x = player->rotation.x + player->plane.x * camera;
		ray_dir.y = player->rotation.y + player->plane.y * camera;
		//ray_dir = get_ray_direction(ray_angle);
		map_y = (int)player->position.y;
		map_x = (int)player->position.x;
		if (ray_dir.x == 0)
			delta_dist.x = 1e30;
		else
			delta_dist.x = fabs(1 / ray_dir.x);
		if (ray_dir.y == 0)
			delta_dist.y = 1e30;
		else
			delta_dist.y = fabs(1 / ray_dir.y);
		// delta_dist.x = fabs(1 / ray_dir.x);
		// delta_dist.y = fabs(1 / ray_dir.y);
		
		// distance to the next grid line
		if (ray_dir.x < 0)
		{
			step_x = -1;
			nxt_line.x = (player->position.x - map_x) * delta_dist.x; 
		}
		else 
		{
			step_x = 1;
			nxt_line.y = (map_x + 1.0 - player->position.x) * delta_dist.x; 
		}
		if (ray_dir.y < 0) 
		{
			step_y = -1;
			nxt_line.y = (player->position.y - map_y) * delta_dist.y;
		}
		else
		{
			step_y = 1;     
			nxt_line.y = (map_y + 1.0 - player->position.y) * delta_dist.y;
		}
		// ***** DDA
		while (1)
		{   
			if (nxt_line.x < nxt_line.y) 
			{
				nxt_line.x += delta_dist.x;
				map_x += step_x;
				is_wall = 0;
			}
			else
			{
				nxt_line.y += delta_dist.y;
				map_y += step_y;
				is_wall = 1;
			}
			if (m[map_y][map_x] > 0)
				break ;
		}
		if (is_wall == 0)
			//wall_dist = (map_x - player->position.x + (1 - step_x) / 2) / ray_dir.x;
			wall_dist = nxt_line.x - delta_dist.x;
		else 
			//wall_dist = (map_y - player->position.y + (1 - step_y) / 2) / ray_dir.y;
			wall_dist = nxt_line.y - delta_dist.y;
		//wall_dist = wall_dist * cos(player->looking_angle - atan2(ray_dir.y, ray_dir.x));
		wall_line_height = (int)(screenHeight / wall_dist);
		start = (screenHeight / 2) - (wall_line_height / 2);
		if (start < 0)
			start = 0;
		end = (wall_line_height / 2) + (screenHeight / 2);
		if (end >= screenHeight)
			end = screenHeight - 1;
		// if (is_wall == 0)
		// 	wall.x = player->position.y + wall_dist * ray_dir.y;
		// else
		// 	wall.x = player->position.x + wall_dist * ray_dir.y;
		// wall.x -= floor(wall.x);
		draw_v_line(player->map->game->screen, i, start, end, wall_dist, m[map_y][map_x]);
		ray_angle += player->ray_angle;
	}
}

void draw_v_line(mlx_image_t *screen, int x, int start, int end, float dist, int color) 
{
    int y;

    if (start < 0)
		start = 0;
	if (end >= HEIGHT_WIN)
		end = HEIGHT_WIN - 1;
	
    //if (side == 1)
    //{
		color = get_distance_color(dist);
   // }
    y = start;
    while (y <= end)
    {
 		mlx_put_pixel(screen, x, y, color);
		y++;
    }
}
