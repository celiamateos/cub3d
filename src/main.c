/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:56:50 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/10 20:43:19 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>


#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;


// void	*ft_init(t_data *data)
// {
// //  fdf->mlx = mlx_init(WIDTH - 100, HEIGHT - 50, "Wire-frame (fdf)", true);
// 	data->mlx = mlx_init(WIDTH_WIN - 100, HEIGHT_WIN - 50, "hola que tal", true);
// 	// data->mlx_win = mlx_new_window(data->mlx, WIDTH_WIN, HEIGHT_WIN, "MEOW!:3");
	
// 	return (data->mlx_win);
// }

void load_data(t_data *data)
{    
    ft_bzero(data, sizeof(t_data));
    if (!data)
        exit(1);
    data->map = ft_calloc(1, sizeof(t_map));
    data->player = ft_calloc(1, sizeof(t_player));
    // data->map = (t_map *)malloc(sizeof(t_map));
    // data->map->line = ft_calloc(1, sizeof(data->map->line));
    // data->map->map = ft_calloc(1, sizeof(char *));
    data->map->map = NULL;
    data->map->num_elem = 0;
    data->map->north_route = NULL;
    data->map->south_route = NULL;
    data->map->east_route = NULL;
    data->map->west_route = NULL;
    data->map->ceiling_route = 0;
    data->map->floor_route = 0;
    data->player->player_count = 0;
    data->mlx = NULL;
}

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

    // ft_init(&data);

    // return (0);

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

// -----------------------------------------------------------------------------

int32_t main(int ac, char **av)
{
	t_data  data;

	(void)ac;
	mlx_t* mlx;
	
    if (ac != 2 || check_name_file(av[1]))
		err("Bad arguments. Enter a .cub file\n"), exit(1);
	printf("Bienvenido a Cub3d\n");
	load_data(&data);
	load_map(&data, av[1]);

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
	return (EXIT_SUCCESS);
}
