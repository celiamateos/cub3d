/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:07:33 by iostancu          #+#    #+#             */
/*   Updated: 2024/11/07 19:22:31 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_game	*init_game(void)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	game->mlx = mlx_init(WIDTH_WIN, HEIGHT_WIN, "Cub3D", true);
	if (!game->mlx)
		puts(mlx_strerror(mlx_errno)), exit(1);
	game->screen = mlx_new_image(game->mlx, WIDTH_WIN, HEIGHT_WIN);
	if (!game->screen)
		mlx_close_window(game->mlx), puts(mlx_strerror(mlx_errno)), exit(1);
	return(game);
}

double	set_radius(double angle)
{
	return ((angle * 3.14159265359) / 180.0);
}

t_player	*init_player(t_map *map)
{
	t_player	*p;

	p = ft_calloc(1, sizeof(t_player));
	if (!p)
		err("Error: malloc\n"), exit(1);
	p->player_dir = 0;
	p->player_count = 0;
	p->position.x = 0;
	p->position.y = 0;
	p->speed = 0.05f;
	p->rotation_speed = 1.5f;
	p->fov = 90;
	p->looking_angle = 90.0;
	p->rotation.x = cos(set_radius(90.0));
	p->rotation.y = -sin(set_radius(90.0));
	p->width_win = 2200;
	p->height_win = 1000;
	printf("p->height_win: %d\n", p->height_win);
	printf("p->width_win: %d\n", p->width_win);
	printf("fov: %d\n", p->fov);
	p->ray_angle = 90.0 / 2200.0;
	printf("p->raycast_angle: %f\n", p->ray_angle);
	p->map = map;
	return (p);
}

t_map	*init_map()
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		err("Error: malloc\n"), exit(1);
	map->game = init_game();
	map->map = NULL;
	map->num_elem = 0;
	map->north_route = NULL;
	map->south_route = NULL;
	map->east_route = NULL;
	map->west_route = NULL;
	map->ceiling_route = 0;
	map->floor_route = 0;
	return (map);
}

void	init_cub3d(t_player *p, t_map *m)
{
	m = init_map();
	p = init_player(m);
}
