/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:15:35 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/21 21:15:19 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void err(char *str)
{
	while(*str)
		write(2, str++, 1);
}

void	free_cub3D(t_map *map, t_player *player)
{
	int i;

	i = 0;
	if (map)
	{
		if (map->map)
			ft_freearray(map->map);
		while (map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->game);
		free(map->grid);
		free(map);
	}
	if (player)
		free(player);
}
