/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:19:37 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/29 16:03:07 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include <structs.h>

void	draw_2d_map(void *param);
void    draw_player(void *param);
void    draw_background(mlx_image_t *screen);
uint32_t get_distance_color(float distance);

#endif