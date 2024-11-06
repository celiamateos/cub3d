/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:56:50 by cmateos-          #+#    #+#             */
/*   Updated: 2024/11/06 20:15:01 by iostancu         ###   ########.fr       */
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


void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

int	load_images(t_map *map)
{
	int height;

	height = HEIGHT_WIN;
    mlx_image_to_window(map->game->mlx, map->images.c, 0, 0);
    mlx_image_to_window(map->game->mlx, map->images.f, 0, height / 2);
	mlx_image_to_window(map->game->mlx, map->images.no, 300, 500);
	mlx_image_to_window(map->game->mlx, map->images.so, 400, 500);
	mlx_image_to_window(map->game->mlx, map->images.ea, 500, 500);
	mlx_image_to_window(map->game->mlx, map->images.we, 600, 500);
	if (mlx_image_to_window(map->game->mlx, map->game->screen, 0, 0) == -1)
	{
		mlx_close_window(map->game->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	return 0;
}

void	destroy_images(t_map *map)
{
	mlx_delete_image(map->game->mlx, map->images.no);
	mlx_delete_image(map->game->mlx, map->images.so);
	mlx_delete_image(map->game->mlx, map->images.we);
	mlx_delete_image(map->game->mlx, map->images.ea);
	mlx_delete_image(map->game->mlx, map->images.c);
	mlx_delete_image(map->game->mlx, map->images.f);

	mlx_delete_texture(map->textures.no);
	mlx_delete_texture(map->textures.so);
	mlx_delete_texture(map->textures.we);
	mlx_delete_texture(map->textures.ea);
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
	if (!load_map(map, player, av[1]))
	{
		mlx_close_window(map->game->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	
	//mlx_loop_hook(map->game->mlx, draw_player, player);
	
	mlx_loop_hook(map->game->mlx, do_raycast, player);
	//mlx_key_hook(map->game->mlx, my_keyhook, player);
	// //minimap
	// mlx_loop_hook(map->game->mlx, draw_2d_map, map);
	
	mlx_loop(map->game->mlx);
	mlx_terminate(map->game->mlx);
	free_cub3D(map, player);
	return (EXIT_SUCCESS);
}
