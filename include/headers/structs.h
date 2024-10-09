/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:33:50 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/10 00:44:04 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H

# define STRUCTS_H

typedef struct s_vec2
{
	int	x;
	int	y;
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
typedef struct s_map
{
	t_vec2	position;
	t_wall	**wall;
	int		**grid;
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
	t_vec2	position;
	int		speed;
	t_vec2	direction;
	t_vec2	dist_pplane;
	t_vec2	dist_wall;
	t_vec2	init_dir;
}	t_player;

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