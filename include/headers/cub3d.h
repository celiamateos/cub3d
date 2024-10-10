/* ************************************************************************** */
/*																														 */
/*																						 :::		 ::::::::	*/
/*	cub3d.h																	:+:		 :+:	:+:	*/
/*																				  +:+ +:+			+:+		*/
/*	By: iostancu <iostancu@student.42.fr>				+#+  +:+		  +#+			*/
/*																			+#+#+#+#+#+	+#+				 */
/*	Created: 2024/09/26 18:00:09 by cmateos-				#+#	#+#					*/
/*	Updated: 2024/10/10 19:11:40 by iostancu			###	########.fr		  */
/*																														 */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# define HEIGHT 720
# define WIDTH 1280

#ifndef FOV
# define FOV 120
#endif

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>
# include <errno.h>
# include <stdbool.h>
# include <MLX42.h>

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
    char    *north_route; //Route textures
    char    *south_route;
    char    *east_route;
    char    *west_route;
    int    *ceiling_route; //RGB Format
    int    *floor_route; //RGB Format
    char    **map; //Only map content
    int     height;
    int     width;

}   t_map;

typedef struct t_player
{
    char    player_dir; //Direction player (N,S,E,W)
    int     player_count;
    int     y; //Coord. y player
    int     x; //Coord. x player
}   t_player;

typedef struct  s_data
{
	t_map       *map;
	t_player    *player;
    void		*mlx;
	void		*mlx_win;

}   t_data;


//PARSE
void    load_map(t_data *data, char *file);
void    readmap(t_data *data);
bool    check_valid_map(t_data *data);
bool    map_closed(char **m, size_t x, size_t y);
size_t  double_pointer_len(char **double_pointer);
bool    cover_char(char c);
void    save_data_map(t_data *data, char *line);
void    save_element_map(t_data *data, char ***elements);
void    save_colors_map(t_data *data, char ***elements);
int     *load_data_color_map(char *str);
char    *ft_search_element(char **element);

// UTILS
void    err(char *str);
int     ft_arraylen(char **array);
void    ft_printarray(char **arr);
void    ft_printintarray(int *nb, int size);
int     ft_free_error_arr(char **mem, long row);
void    save_map(t_data *data, char *str);

#endif
