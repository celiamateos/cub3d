/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:19:37 by iostancu          #+#    #+#             */
/*   Updated: 2024/11/06 20:05:04 by iostancu         ###   ########.fr       */
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

#endif
