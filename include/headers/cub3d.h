/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:00:09 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/01 20:54:43 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../libft/libft.h" 
# include <unistd.h>
# include <stdio.h>
# include <string.h> 
# include <stdlib.h> 
# include <fcntl.h>
# include <MLX42.h>
# include <stdarg.h> 
# include <limits.h> 
# include <errno.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define PURPLE "\033[1m\033[35m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define RESET "\033[0m" 

# define WIDTH_WIN 1500
# define HEIGHT_WIN 1500

typedef struct map
{
    int     fd;
    char    *line;
    int     num_elem;
    char    *north_route;
    char    *south_route;
    char    *east_route;
    char    *west_route;
    int    *ceiling_route;
    int    *floor_route;
    char    **map;
    int     x;
    int     y;
}   t_map;

typedef struct t_player
{
    char    player_dir; //Direction player (N,S,E,W)
    int     player_count;
}   t_player;

typedef struct  s_data
{
	t_map       *map;
	t_player    *player;
    void		*mlx;
	void		*mlx_win;

}   t_data;



void err(char *str);
void load_map(t_data *data, char *file);
void readmap(t_data *data, char *file);
int ft_arraylen(char **array);
void ft_printarray(char **arr);

#endif
