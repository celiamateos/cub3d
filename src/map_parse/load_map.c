/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:26:57 by cmateos-          #+#    #+#             */
/*   Updated: 2024/11/06 20:15:52 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int check_player_direction(t_player *player, char c, int row, int i)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (-1);
	else
	{
		set_looking_angle(c, &player->looking_angle); //looking_angle es lo mismo que spawn_direction ?
		// player->player_dir = c;
		player->position.y = row;
		player->position.x = i;
		//player->ray_angle = player->looking_angle - HALF_FOV;
	}
	return (1);
}


int    check_map_player_info(t_map *map, t_player *p)
{
	int i;
	int row = -1;
	int player_count = 0;
	i = -1;
	if (map->map)
	{
		while (map->map[++row])
		{
			while (map->map[row][++i])
			{
				if (map->map[row][i] && map->map[row][i] != '0' && map->map[row][i] != '1' && map->map[row][i] != ' ' && map->map[row][i] != '\n')
				{
					if (check_player_direction(p, map->map[row][i], row, i) == -1)
							err(RED"Error:\n invalid map: Bad character\n"RESET), exit(1); //freee
					else
						player_count += 1;

				}
			}
			if (map->width < i)
				map->width = i - 1;
			i = -1;
		}
	}
	// printf("player_count:%d\n", player_count);
	if (player_count != 1)
		return (err(RED"Error\n set a valid player\n"RESET), 1);
	return (0);
}

int	save_map(t_map *map, char *str)
{
	int     i;
	int     len;
	char    **aux;

	i = -1;
	if (map->map)
		len = ft_arraylen(map->map);
	else
		len = 0;
	aux = ft_calloc(len + 2, sizeof(char *));
	if (!aux)
		return (err("Error\n"), 1); //Free
	while (++i != len)
	{
		aux[i] = ft_strdup(map->map[i]);
		if (!aux[i])
			return (ft_free_error_arr(aux, i), 1);
	}
	aux[i] = ft_strdup(str);
	if (!aux[i])
		return (err("Error\n"), ft_free_error_arr(aux, i), 1); //Free
	aux[++i] = NULL;
	if (map->map)
		ft_freearray(map->map);
	map->map = aux;
	map->map = ft_arraydup(aux);
	ft_freearray(aux);
	return (0);
}

int readmap(t_map *map)
{
	char    *line;
	int     i;

	i = 0;
	// if ((line = (char *)malloc(sizeof(char))) == NULL)
	// 	return (1);
	while (1)
	{
		line = get_next_line(map->fd);
		if (!line)
			break ;
		if (line && !check_emptyorspace(line))
		{
			if (map->num_elem != 6)
			{
				if (save_data_map(map, line))
					return (err(RED"Error\n Cannot save data map\n"RESET), free(line), 1);
			}
			else
			{
				if (save_map(map, line))
					return (err(RED"Error\n Cannot save map\n"RESET), free(line), 1);
				i++;
			}
		}
		free(line);
	}
	map->height = i;
	return (0);
}



int load_map(t_map *map, t_player *player, char *file)
{
	char **map_cp;
	
	map->fd = open(file, O_RDONLY);
	if (map->fd < 0)
		return (err(RED"Error\n fd: cannot open\n"RESET), 1);
	if (readmap(map))
		return (err(RED"Error\n cannot read map\n"RESET), 1);
	close(map->fd);
	if (check_map_player_info(map, player))
		return (err(RED"Error\n invalid player info\n"RESET), 1);
	if (map->num_elem != 6)
		return (err(RED"Error\n map: invalid elements count\n"RESET), 1);
	// printf(YELLOW"\nplayer_direction:%i\n\n"RESET, player->spawn_direction);
	map_cp = ft_arraydup(map->map);
	if (!map_cp)
		return (err("Err\n"), 1);
	if (!map_closed(map_cp,player->position.x, player->position.y) || !check_valid_map(map_cp))
		return (err(RED"Error\n Map is not closed\n"RESET), ft_freearray(map_cp), 1);
	ft_freearray(map_cp);
	// ft_printarray(map->map); //PRINT map-> char **map
	// printf(BLUE"\nPlayer position: [%f][%f]\n"RESET, player->position.y, player->position.x); //PRINTF
	// printf(GREEN"\nMap height: %d\n"RESET, map->height); //PRINTF
	// printf(GREEN"Map width: %d\n"RESET, map->width); //PRINTF
	map->grid = map_to_int(map->map, map->height, map->width);
	// return (1);
	return (0);
}