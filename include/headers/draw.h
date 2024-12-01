/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:19:37 by iostancu          #+#    #+#             */
/*   Updated: 2024/12/01 03:18:17 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include <structs.h>

void		draw_2d_map(void *param);
void		draw_player(void *param);
void		draw_background(mlx_image_t *screen);
uint32_t	get_distance_color(float distance);
void		draw_line(t_vec2 start, t_vec2 end, mlx_image_t *img,
						uint32_t color);
int			get_rgba(int r, int g, int b, int a);
uint32_t	get_pixel(mlx_texture_t *texture, int x, int y);

#endif
