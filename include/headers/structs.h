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
	mlx_image_t	*c;
	mlx_image_t	*f;

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
 * @param grid Map to int
 * @param height Map height in pixels (y)
 * @param width Map width in pixels (x)
 */
typedef struct	s_map
{
	t_textures	textures;
	t_images	images;
	int			fd;
	char		*line;
	int			num_elem;
	char		*north_route;	//QUIT
	char		*south_route;	//QUIT
	char		*east_route; 	//QUIT
	char		*west_route;	//QUIT
	char		*floor_route; 	//QUIT
	char		*ceiling_route;	//QUIT
	int			ceiling_color;	//RGB Format, not texture
	int			floor_color;	//RGB Format, not texture
	char		**map;			//Only map content
	int			height;
	int			width;
	t_game		*game;
	int			**grid;	// **map to atoi (-1, 0, 1)
	mlx_image_t	*floor;
	mlx_image_t	*ceiling;
}	t_map;

typedef struct s_control
{
	/* data */
}	t_control;

/**
	@brief Player struct, that works as camera.

	@param position Player position in the map.
	@param rotation Player rotation in the map.
	@param speed Moving speed
	@param rotation_speed Rotation speed
	@param looking_angle Initialized with the angle where player is looking at init spawn
	with the rotation movement. Updated every rotation movement.
	@param raycast_angle Angle between each ray
 */
typedef struct	s_player
{
	char		player_dir;	//Direction player (N,S,E,W)
	int			player_count;
	//t_control	control;		// in future with time, clean player struct and put all controls here
	t_vec2		position;
	t_vec2		rotation;
	float		speed;
	float		rotation_speed;
	double		looking_angle;	//direction
	int			fov;
	double		ray_angle;
	t_map		*map;
	int			width_win;
	int			height_win;
}	t_player;

#endif
