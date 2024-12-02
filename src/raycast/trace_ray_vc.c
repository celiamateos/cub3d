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
void draw_v_line(mlx_image_t *screen, int side, int x, int start, int end, float dist, mlx_texture_t *t, int tex_x, int tex_y);
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
	double	perp_wall_dist;
	t_vec2	delta_dist;
	t_vec2	side_dist;	// distance to next grid line
	t_int2	map;
	t_int2	texture;
	double	ray_angle;
	int		i;
	int		start;
	int		end;
	int		wall_line_height;
	t_int2	step;
	int		side;
	double		dist_to_projection;
	double		camera;
	t_vec2		wall;
	t_vec2		ray;
	double		step_d;
	int			texture_n;
	int			tex_x;
	double tex_y;
	double		tex_pos;
	uint32_t	color;
	xpm_t* img;
	double	resize;
	
	img = mlx_load_xpm42("/home/settes/cursus/cub3D/textures/wolf/purplestone.xpm42");
	if (!img)
       	perror("Error: mlx_load_xpm42\n"), exit(1);

	i = -1;
	ray_angle = player->looking_angle - (player->fov / 2);
	dist_to_projection = (player->width_win / 2) / tan(player->fov / 2 * (M_PI / 180));
	while (++i < player->width_win) 
	{
		camera = 2 * i / (double)player->width_win - 1;
		ray_dir.x = cos(player->looking_angle + atan(camera));
		ray_dir.y = sin(player->looking_angle + atan(camera));
		// ray_dir.x = player->rotation.x + player->plane.x * camera;
		// ray_dir.y = player->rotation.y + player->plane.y * camera;
		//ray_dir = get_ray_direction(ray_angle);
		map.y = (int)player->position.y;
		map.x = (int)player->position.x;
		// if (ray_dir.x == 0)
		// 	delta_dist.x = 1e30;
		// else
		// 	delta_dist.x = fabs(1 / ray_dir.x);
		// if (ray_dir.y == 0)
		// 	delta_dist.y = 1e30;
		// else
		// 	delta_dist.y = fabs(1 / ray_dir.y);
		delta_dist.x = fabs(1 / ray_dir.x);
		delta_dist.y = fabs(1 / ray_dir.y);
		
		// distance to the next grid line
		if (ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (player->position.x - map.x) * delta_dist.x; 
		}
		else 
		{
			step.x = 1;
			side_dist.y = (map.x + 1.0 - player->position.x) * delta_dist.x; 
		}
		if (ray_dir.y < 0) 
		{
			step.y = -1;
			side_dist.y = (player->position.y - map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;     
			side_dist.y = (map.y + 1.0 - player->position.y) * delta_dist.y;
		}
		// ***** DDA
		while (1)
		{   
			if (side_dist.x < side_dist.y) 
			{
				side_dist.x += delta_dist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				side = 1;
			}
			if (m[map.y][map.x] > 0)
				break ;
		}
		if (side == 0)
			//perp_wall_dist = (map.x - player->position.x + (1 - step_x) / 2) / ray_dir.x;
			perp_wall_dist = side_dist.x - delta_dist.x;
		else 
			//perp_wall_dist = (map_y - player->position.y + (1 - step_y) / 2) / ray_dir.y;
			perp_wall_dist = side_dist.y - delta_dist.y;
		//perp_wall_dist = perp_wall_dist * cos(player->looking_angle - atan2(ray_dir.y, ray_dir.x));
		wall_line_height = (int)(screenHeight / perp_wall_dist);
		start = (screenHeight / 2) - (wall_line_height / 2);
		if (start < 0)
			start = 0;
		end = (wall_line_height / 2) + (screenHeight / 2);
		if (end >= screenHeight)
			end = screenHeight - 1;

		texture_n = m[map.y][map.x] - 1;

		if (wall_line_height > screenHeight)
		{
			tex_y = (wall_line_height - screenHeight) / 2 * resize;
		}


		if (side == 0)
			tex_x = player->position.y + perp_wall_dist * ray_dir.y;
		else
			tex_x = player->position.x + perp_wall_dist * ray_dir.y;
		tex_x = fmod(tex_x, 1);



		//img->texture.width = (int)(tex_x * (double)(SIZE));
		if(side == 0 && ray_dir.x > 0)
	  		tex_x = player->position.y + perp_wall_dist * ray_dir.y;
      	if(side == 1 && ray_dir.y < 0)
			tex_x = player->position.x + perp_wall_dist * ray_dir.x;
		// How much to increase the texture coordinate per screen pixel
		step_d = 1.0 * SIZE / wall_line_height;

		resize = 1.0 * img->texture.height / (wall_line_height + 1);

		// Starting texture coordinate
		tex_pos = (start - screenHeight / 2 + wall_line_height / 2) * step_d;
		//printf("tex_pos: %f\n", tex_pos);
		// get a random specific pixel data from img
		// if (side == 0)
		// {
		// 	tex_x = (int)(player->position.y + perp_wall_dist * ray_dir.y);
		// }
		// else
		// {
		// 	tex_x = (int)(player->position.x + perp_wall_dist * ray_dir.x);
		// }
		// for(int y = start; y < end; y++)
		// {
		// 	//texture.y = (int)tex_pos & (SIZE - 1);
		// 	img->texture.height = (int)tex_pos & (SIZE - 1);
		// 	tex_pos += step_d;
		// 	//color = m[texture_n][SIZE * img->texture.height + img->texture.width];
		// 	//color = mlx_get_pixel(img, img->texture.width, img->texture.height);
		// 	color = get_pixel(&img->texture, start % 64 -1, img->texture.height);
		// 	//color = get_distance_color(perp_wall_dist);
		// 	if(side == 1)
		// 		color = (color >> 1) & 8355711;	// 01111111 01111111 01111111
		// 		//color = (color >> 1) & 2139062143;	// 01111111 01111111 01111111 01111111
		// // buffer[y][x] = color;
		// }
		
		draw_v_line(player->map->game->screen, side, i, start, end, perp_wall_dist, &img->texture, tex_x, tex_y);
		ray_angle += player->ray_angle;
	}
	mlx_delete_xpm42(img);
}

void draw_v_line(mlx_image_t *screen, int side, int x, int start, int end, float dist, mlx_texture_t *t, int tex_x, int tex_y) 
{
    int		y;
	int		texture_y;
	int		line_height;
	float	step;	//scale
	float	texture_pos;
	int		color;
	
	line_height = end - start;
	step = (float)t->width / line_height;
	texture_pos = 0.0;
    if (start < 0)
	{
		//texture_pos = (float)(-start) / line_height * step;
		texture_pos = -start * step;
		start = 0;
	}
	if (end >= HEIGHT_WIN)
		end = HEIGHT_WIN - 1;

	//x = start % SIZE;

    //if (side == 1)
    //{
		
   // }
    y = start;
    while (y <= end)
    {
		texture_y = (int)texture_pos & (t->height - 1);
		color = get_pixel(t, tex_x, tex_y);
		if(side == 1)
			color = (color >> 1) & 2139062143;
 		mlx_put_pixel(screen, x, y, color);
		texture_pos += step;
		y++;
    }
}
