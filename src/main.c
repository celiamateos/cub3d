/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:56:50 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/14 20:35:38 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static mlx_image_t* image;

// void	*ft_init(t_data *data)
// {
// //  fdf->mlx = mlx_init(WIDTH - 100, HEIGHT - 50, "Wire-frame (fdf)", true);
// 	data->mlx = mlx_init(WIDTH_WIN - 100, HEIGHT_WIN - 50, "hola que tal", true);
// 	// data->mlx_win = mlx_new_window(data->mlx, WIDTH_WIN, HEIGHT_WIN, "MEOW!:3");
	
// 	return (data->mlx_win);
// }


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
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
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
	p->fov = FOV;
	p->dist_pplane.x = 0;
	p->dist_pplane.y = 0;
	p->dist_wall.x = 0;
	p->dist_wall.y = 0;
	return (p);
}

t_map	*init_map()
{
	t_map	*map;
	//map = ft_calloc(1, sizeof(t_map));
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

void	free_cub3D(t_map *map, t_player *player)
{
	if (map)
	{
		if (map->map)
			ft_freearray(map->map);
		if (map->north_route)
			free(map->north_route);
		if (map->south_route)
			free(map->south_route);
		if (map->east_route)
			free(map->east_route);
		if (map->west_route)
			free(map->west_route);
		if (map->ceiling_route)
			free(map->ceiling_route);
		if (map->floor_route)
			free(map->floor_route);
		
		free(map);
	}
	if (player)
		free(player);
}

int32_t main(int ac, char **av)
{
	t_map		*map;
	t_player	*player;
	t_game		*game;

	(void)ac;
	mlx_t* mlx;
	
    if (ac != 2 || check_name_file(av[1]))
		err("Bad arguments. Enter a .cub file\n"), exit(1);
	printf("Bienvenido a Cub3d\n");
	//init_cub3d(player, map);
	map = init_map();
	player = init_player();
	//load_data(&data);
	if (!load_map(map, player, av[1]))
		return (1); // Free map and player

	// // Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_cub3D(map, player);
	return (EXIT_SUCCESS);
}


/*


*/