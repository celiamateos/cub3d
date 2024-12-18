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

# define FOV	90
# define WIDTH_WIN		2200
# define HEIGHT_WIN		1000
# define HALF_HEIGHT	(HEIGHT_WIN / 2)
# define HALF_FOV		(FOV / 2)
# define SIZE			64
# define MINIMAP_SIZE	(SIZE / 2)
# define ROTATION_ANGLE	1
# define PI_			3.14159265
# define PROJECTION_DISTANCE	0.5f
# define SIZE_MULTIPL_HEIGHT	(MINIMAP_SIZE * HEIGHT_WIN)


# define NO		1
# define SO		2
# define EA		3
# define WE		4



# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <structs.h>
# include <raycast.h>
# include <draw.h>
# include <math.h>

# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define PURPLE	"\033[1m\033[35m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define RESET	"\033[0m"



//PARSE
int     load_map(t_map *map, t_player *player, char *file);
int     readmap(t_map *map);
int     save_map(t_map *map, char *str);
int    check_valid_map(char **map);
int    map_closed(char **m, size_t x, size_t y);
size_t  double_pointer_len(char **double_pointer);
int    cover_char(char c);
int     save_data_map(t_map *map, char *line);
int    save_element_map(t_map *map, char ***elements);
int    save_colors_map(t_map *map, char ***elements);
int     load_data_color_map(char *str);
char    *ft_search_element(char **element);
int     check_map_player_info(t_map *map, t_player *p);


int		**map_to_int(char **map, int h, int w);
// UTILS
void    err(char *str);
int     ft_arraylen(char **array);
void    ft_printarray(char **arr);
void    ft_printintarray(int *nb, int size);
int     ft_free_error_arr(char **mem, long row);
char    **ft_arraydup(char **arr);
void ft_print_grid(int **grid, int height, int width);

#endif
