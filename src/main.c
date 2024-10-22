/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:56:50 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/22 21:28:57 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static mlx_image_t* image;
t_map		*init_map();
t_player	*init_player(t_map *map);
void		init_game(t_game *game);
void		free_cub3D(t_map *map, t_player *player);

int check_name_file(char *av)
{
	if ((ft_strlen(av)) < 4 || av[ft_strlen(av) - 1] != 'b'
		|| av[ft_strlen(av) - 2] != 'u' || av[ft_strlen(av) - 3] != 'c'
		|| av[ft_strlen(av) - 4] != '.')
		return (1);
	return (0);
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);

}

void ft_randomize(void* param)
{
	t_game *game = param;

	for (uint32_t i = 0; i < game->screen->width; ++i)
	{
		for (uint32_t y = 0; y < game->screen->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(game->screen, i, y, color);
		}
	}
}

void player_move_minimap(void* param)
{
	t_player	*p;

	p = (t_player *)param;

	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(p->map->game->mlx);
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_UP))
		p->position.y -= 0.1f;
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_DOWN))
		p->position.y += 0.1f;
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_LEFT))
		p->position.x -= 0.1f;
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_RIGHT))
		p->position.x += 0.1f;
	draw_player(p);
}

int32_t main(int ac, char **av)
{
	t_map		*map;
	t_player	*player;

	(void)ac;
	
    if (ac != 2 || check_name_file(av[1]))
		err("Bad arguments. Enter a .cub file\n"), exit(1);
	map = init_map();
	player = init_player(map);
	load_map(map, player, av[1]);
	if (mlx_image_to_window(map->game->mlx, map->game->screen, 0, 0) == -1)
	{
		mlx_close_window(map->game->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	//minimap
	mlx_loop_hook(map->game->mlx, draw_2d_map, map);
	mlx_loop_hook(map->game->mlx, draw_player, player);
	mlx_loop_hook(map->game->mlx, player_move_minimap, player);

	mlx_loop(map->game->mlx);
	mlx_terminate(map->game->mlx);
	free_cub3D(map, player);
	return (EXIT_SUCCESS);
}
