#ifndef RAYCAST_H
# define RAYCAST_H

#include <structs.h>

void	set_looking_angle(char dir, double *angle);
void	set_spawn_position(double x, double y, t_vec2 *player_pos);
void	do_raycast(void* param);
double	set_radius(double angle);
void    my_keyhook(mlx_key_data_t k, void* param);
int trace_ray(t_vec2 pos, double angle, t_map *map, t_player *p);

#endif
