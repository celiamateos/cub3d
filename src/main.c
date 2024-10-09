/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:56:50 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/10 00:28:43 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// // is_floor(char *c)
// // {
// //     if (c == '0' || c == '' )
// // }


// /// @brief 
// /// @param map 
// /// @param x 
// /// @param y 
// // /// @return 1 case of player not surrounded by wall
// // int floodfill_cub3d(char **map, int x, int y)
// // {

// // /* 	if (x == e->widthmap - 1 || y == e->heightmap - 1
// // 		|| (y == 0 && map[y][x] == '0') || (x == 0 && map[y][x] == '0'))
// // 		ft_error(e, 3); */
// // 	if (x <= 0 || y <= 0) // o es el len del ancho o largo de la linea: return 1
// //         return (1);
// //     //Si arriba, abajo, izq o der hay espacio o tab: error.
// //     if (map[y + 1][x] != '1' || (map[y - 1][x] != '1')
// // 		|| map[y][x + 1] != '1' || map[y][x - 1] != '1')
// // 		map[y][x] = '1';
// // 	if (map[y + 1][x] != '1')
// //         floodfill_cub3d(map, x + 1, y);
// // 	if (map[y - 1][x] != '1')
// //         floodfill_cub3d(map, x - 1, y);
// // 	if (map[y][x + 1] != '1')
// //         floodfill_cub3d(map, x, y + 1);
// // 	if (map[y][x - 1] != '1')
// //         floodfill_cub3d(map, x, y - 1);
// // 	map[y][x] = '1';

// // 	if (e->count_collect == e->collectable && e->count_exit == 1)
// // 		return (1);
// // }

// //     /* 
// //     con GNL leer cada linea del mapa y ir guardandolas en una lista cada nodo es una linea con su char *
// //     y su int longitud hor y ver, el total de nodos es el total de lineas del mapa   
// //     Añadir lista y ancho y largo del mapa...
// //     Esta funcion parte de la posicion de player y rastrea su alrededor llenando los  */
// //     //Verificar si (hay) los espacios están rodeados de 1 o espacios, si no es así: error.
// // 	return (0);




// void load_data(t_data *data)
// {    
// 	ft_bzero(data, sizeof(t_data));
// 	if (!data)
// 		exit(1);
// 	data->map = (t_map *)malloc(sizeof(t_map));
// 	// data->map->line = ft_calloc(1, sizeof(data->map->line));
// 	//data->map->elements = 0;
// }

// int check_name_file(char *av)
// {
// 	if ((ft_strlen(av)) < 4 || av[ft_strlen(av) - 1] != 'b'
// 		|| av[ft_strlen(av) - 2] != 'u' || av[ft_strlen(av) - 3] != 'c'
// 		|| av[ft_strlen(av) - 4] != '.')
// 		return (1);
// 	return (0);
// }

// int main(int ac, char **av)
// {
// 	t_data  data;

// 	(void)ac;
// 	if (ac != 2 || check_name_file(av[1]))
// 		err("Bad arguments. Enter a .cub file\n"), exit(1);
// 	printf("Bienvenido a Cub3d\n");
// 	load_data(&data);
// 	load_map(&data, av[1]);
// 	// char *line;
// 	// int fd;

// 	// fd = open(av[1], O_RDONLY);
// 	// if (fd == -1 || !av[1])
// 	//     return 1;
// 	// while (1)
// 	// {
// 	//     line = get_next_line(fd);
// 	//     printf("line:%s\n", line);
// 	//     if (!line)
// 	//         break ;
// 	// }
// 	// close (fd);
// 	return (0);
// }

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;

// -----------------------------------------------------------------------------

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

// -----------------------------------------------------------------------------

int32_t main(void)
{
	mlx_t* mlx;
	t_player player;

	// Gotta error check this stuff
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