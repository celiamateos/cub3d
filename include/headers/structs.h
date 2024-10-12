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

typedef struct	s_ray
{
	t_vec2	start;
	t_vec2	end;
	t_vec2	offset;
}	t_ray;

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
 * @brief Map. All of the data included in the file, will be extracted here
 * 
 * @param position Position of the map
 * @param wall Array of walls
 * @param grid Raw info taked from the .cub file
 * @param floor Floor texture
 * @param ceiling Ceiling texture
 * @param player_dir Player spawn direction
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
	char		player_dir;
}	t_map;

/**
  @brief Player struct. 

  Player will be the camera too (?) maybe not. Thinking about it
  @param position Player position in the map.
  @param speed Moving speed
  @param looking_angle Initialized with the direction spawn value and setted
  with the rotation movement
  @param fov Field of view. Area that will be visible in the screen
  //@param direction Player direction
  @param dist_pplane Distance to the projection plane
  @param dist_wall Distance to the wall
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
	float	looking_angle;	//direction
	float	fov;
	//t_vec2	direction;
	t_vec2	dist_pplane;
	t_vec2	dist_wall;
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
