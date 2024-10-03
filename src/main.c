/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:56:50 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/01 21:05:03 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
    data->map->map = ft_calloc(1, sizeof(char *));
    data->map->map = NULL;
    data->map->num_elem = 0;
    data->map->north_route = NULL;
    data->map->south_route = NULL;
    data->map->east_route = NULL;
    data->map->west_route = NULL;
    data->map->ceiling_route = 0,0,0;
    data->map->floor_route = 0,0,0;
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

int main(int ac, char **av)
{
    t_data  data;

    (void)ac;
    if (ac != 2 || check_name_file(av[1]))
        err(RED"Bad arguments. Enter a .cub file\n"RESET), exit(1);
    printf(PURPLE"Bienvenido a Cub3d\n"RESET);
    load_data(&data);
    load_map(&data, av[1]);
    // ft_init(&data);

    return (0);
}