/* ************************************************************************** */
/*																			*/
/*														:::		::::::::	 */
/*	 structs.h											:+:		:+:	:+:	 */
/*													+:+ +:+		 +:+	 */
/*	 By: iostancu <iostancu@student.42.fr>			+#+	+:+		 +#+		*/
/*												+#+#+#+#+#+	 +#+			 */
/*	 Created: 2024/10/10 00:33:50 by iostancu			#+#	#+#			 */
/*	 Updated: 2024/10/10 22:32:24 by iostancu		 ###	 ########.fr		 */
/*																			*/
/* ************************************************************************** */

#ifndef STRUCTS_H

# define STRUCTS_H

# include <MLX42.h>

typedef struct	s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct	s_ray
{
	t_vec2	start;
	t_vec2	end;
	double	tan_angle;
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

typedef struct	s_game
{
	mlx_t		*mlx;
	mlx_image_t	*screen;
}	t_game;

typedef struct s_images
{
	mlx_image_t	*no;
	mlx_image_t	*so;
	mlx_image_t	*we;
	mlx_image_t	*ea;
}	t_images;

typedef struct s_textures
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_textures;

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
	t_textures	textures;
	t_images	images;
	int			fd;
	char		*line;
	int			num_elem;
	// char		*north_route;	//QUIT
	// char		*south_route;	//QUIT
	// char		*east_route; 	//QUIT
	// char		*west_route;	//QUIT
	int			ceiling_color;	//RGB Format, not texture
	int			floor_color;	//RGB Format, not texture
	char		**map;			//Only map content
	int			height;
	int			width;
	t_game		*game;
	t_vec2		position;
	t_wall		**wall;
	int			**grid;	// **map to atoi (-1, 0, 1)
	char		player_dir;
}	t_map;

typedef struct s_control
{
	/* data */
}	t_control;

/**
 * @brief Raycast info.
 * 
 * @param angle Angle between each ray
 * @param num_rays 
 */
typedef struct	s_raycast
{
	double	angle;
	int		num_rays;
	t_ray	*ray;	// maybe didnt need save every info of each ray if i only use it for draw
}	t_raycast;

/**
	@brief Player struct, that works as camera.

			 pplane
	P....|  W W
	..........walls
	@param position Player position in the map.
	@param speed Moving speed
	@param looking_angle Initialized with the angle where player is looking at init spawn
	with the rotation movement
	@param dist_pplane Distance to the projection plane
	@param dist_wall Distance of the player to the wall
	@param raycast Struct that contains raycasting info and each rays info
 */
typedef struct	s_player
{
	int		spawn_direction;	// change char dir(N, S, W, E) by macros NO SO WE EA
	t_vec2	position;
	double	speed;
	double	looking_angle;	//direction
	t_vec2	dist_pplane;
	t_vec2	dist_wall;
	t_raycast	*raycast;
}	t_player;


typedef struct	s_camera
{
	t_vec2	direction;
	t_vec2	plane;
}	t_camera;

#endif



