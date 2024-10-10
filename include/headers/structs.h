/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   structs.h										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: iostancu <iostancu@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/10 00:33:50 by iostancu		  #+#	#+#			 */
/*   Updated: 2024/10/10 22:32:24 by iostancu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef STRUCTS_H

# define STRUCTS_H

# include <MLX42.h>

typedef struct	s_vec2
{
	float	x;
	float	y;
}	t_vec2;

/**
 * @brief Info of a individual wall
 * 
 * @param img Image of the wall
 * @param start The position of the left-down vertex
 * @param end The position of the right-down vertex
 */
typedef struct	s_wall
{
	mlx_image_t	*img;
	t_vec2		start;
	t_vec2		end;
}	t_wall;

/**
 * @brief Map
 * 
 * @param position Position of the map
 * @param wall Array of walls
 * @param grid Raw info taked from the .cub file
 */
typedef struct	s_map
{
	// celia's params
	int			fd;
	char		*line;
	int			num_elem;
	char		*north_route;	//Route textures
	char		*south_route;
	char		*east_route;
	char		*west_route;
	int			*ceiling_route;	//RGB Format
	int			*floor_route;	//RGB Format
	char		**map;			//Only map content
	int			height;
	int			width;
	// rox params
	t_vec2		position;
	t_wall		**wall;
	int			**grid;
	mlx_image_t	*floor;
	mlx_image_t	*ceiling;
	
}	t_map;

/**
  @brief Player struct.

  Player will be the camera too (?) maybe not. Thinking about it
  @param position Player position in the map.
  @param speed Moving speed
  @param direction Player direction
  @param dist_pplane Distance to the projection plane
  @param dist_wall Distance to the wall
  @param init_dir Which direction the player is facing when program starts
 */
typedef struct	s_player
{
	// celia's params
	char	player_dir;	//Direction player (N,S,E,W)
	int		player_count;
	int		y;			//Coord. y player
	int		x;			//Coord. x player
	// rox params
	t_vec2	position;
	float	speed;
	float	looking_angle;
	t_vec2	direction;
	t_vec2	dist_pplane;
	t_vec2	dist_wall;
	int		init_dir;
}	t_player;

/**
 * @brief Camera
 * 
 * @param direction 
 */
typedef struct	s_game
{
	mlx_t		*mlx;
	mlx_image_t	*screen;
}	t_game;

/**
 * @brief Camera
 * 
 * @param direction 
 */
typedef struct	s_camera
{
	t_vec2	direction;
	t_vec2	plane;
}	t_camera;

#endif
