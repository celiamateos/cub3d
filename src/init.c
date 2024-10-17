/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:07:33 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/18 00:30:58 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_game(t_game *game)
{
	game->mlx = mlx_init(WIDTH_WIN, HEIGHT_WIN, "Cub3D", true);
	if (!game->mlx)
		puts(mlx_strerror(mlx_errno)), exit(1);
	game->screen = mlx_new_image(game->mlx, WIDTH_WIN, HEIGHT_WIN);
	if (!game->screen)
		mlx_close_window(game->mlx), puts(mlx_strerror(mlx_errno)), exit(1);
}

t_player	*init_player()
{
	t_player	*p;

	p = ft_calloc(1, sizeof(t_player));
	if (!p)
		err("Error: malloc\n"), exit(1);
	p->player_dir = 0;
	p->player_count = 0;
	p->position.x = 0;
	p->position.y = 0;
	p->speed = 1;
	p->looking_angle = 0;
	p->dist_pplane.x = 0;
	p->dist_pplane.y = 0;
	p->dist_wall.x = 0;
	p->dist_wall.y = 0;
	return (p);
}

t_map	*init_map()
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		err("Error: malloc\n"), exit(1);
	map->map = NULL;
	map->num_elem = 0;
	map->north_route = NULL;
	map->south_route = NULL;
	map->east_route = NULL;
	map->west_route = NULL;
	map->ceiling_route = 0;
	map->floor_route = 0;
	map->position.x = 0;
	map->position.y = 0;
	return (map);
}

void	init_cub3d(t_player *p, t_map *m)
{
	m = init_map();
	p = init_player();
}
