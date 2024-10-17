/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:26:57 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/16 23:01:10 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int check_player_direction(t_player *player, char c, int row, int i)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (-1);
	else
	{
		set_looking_angle(c, &player->looking_angle);
		player->player_dir = c;
		player->position.y = row;
		player->position.x = i;
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
							err(RED"error: invalid map: Bad character\n"RESET), exit(1); //freee
					else
						player_count += 1;

				}
			}
			if (map->width < i)
				map->width = i - 1;
			i = -1;
		}
	}
	printf("player_count:%d\n", player_count);
	if (player_count != 1)
		return (err(RED"error set a valid player\n"RESET), 1);
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
		return (1); //Free
	while (++i != len)
	{
		aux[i] = ft_strdup(map->map[i]);
		if (!aux[i])
			return (ft_free_error_arr(aux, i), 1);
	}
	aux[i] = ft_strdup(str);
	if (!aux[i])
		return (ft_free_error_arr(aux, i), 1);
	aux[++i] = NULL;
	if (map->map)
		ft_freearray(map->map);
	map->map = aux;
	return (0);
}

int readmap(t_map *map, t_player *player)
{
	char    *line;
	int     i;


	i = 0;
	if ((line = (char *)malloc(sizeof(char))) == NULL)
		exit(1);
	while (1)
	{
		line = get_next_line(map->fd);
		if (line && !check_emptyorspace(line))
		{
			if (map->num_elem != 6)
				save_data_map(map, line);
			else
			{
				if (save_map(map, line))
					return (free(line), 1);
				i++;
			}
		}
		if (line == NULL)
			break ;
		free(line);
	}
	free(line);
	map->height = i;
}
///Esta funcion no termina de funcionar bien xd cuando el mapa no es cuadrado como map->widht es la longitud de la string más larga pinta cosas raras....
int	**convert_to_grid(t_map *map)
{
	int i = 0;
	int row = 0;
	map->grid = malloc(map->height * sizeof(int *));
	if (!map->grid)
		return (err("ERROOOORR"), NULL);
	while(row < map->height)
	{
		map->grid[row] = malloc(map->width * sizeof(int));
		if (!map->grid[row])
			return (err("ERROOOORR"), NULL);

		while(i < map->width)
		{
			if (map->map[row][i] == '0' || map->map[row][i] == 'N' || map->map[row][i] == 'E'
			 || map->map[row][i] == 'S' || map->map[row][i] == 'W')
				map->grid[row][i] = 0;
			else if (map->map[row][i] == '1')
				map->grid[row][i] = 1;
			else if (map->map[row][i] == 32)
				map->grid[row][i] = -1;
			else
				break ;
			i++;
		}
		i = 0;
		row++;
	}
	return map->grid;
}

int load_map(t_map *map, t_player *player, char *file)
{
	char **map_cp;

	map->fd = open(file, O_RDONLY);
	if (map->fd < 0)
		err(RED"error: fd: cannot open\n"RESET), exit(1);
	if (!readmap(map, player))
		return (err("error: readmap\n"), 1);
	close(map->fd);
	if (check_map_player_info(map, player))
		return (ft_freearray(map->map), 1);
	if (map->num_elem != 6)
		err(RED"error: map: invalid elements count\n"RESET), exit(1); //free
	printf(YELLOW"\nplayer_direction:%c\n\n"RESET, player->player_dir);
	map_cp = ft_arraydup(map->map);
	if (!map_closed(map_cp,player->position.x, player->position.y) || !check_valid_map(map_cp))
		return (err(RED"error: Map is not closed\n"RESET), ft_freearray(map->map), ft_freearray(map_cp), 1);
	ft_freearray(map_cp);
	ft_printarray(map->map); //PRINT map-> char **map
	printf(BLUE"\nPlayer position: [%f][%f]\n"RESET, player->position.y, player->position.x); //PRINTF
	printf(GREEN"\nMap height: %d\n"RESET, map->height); //PRINTF
	printf(GREEN"Map width: %d\n"RESET, map->width); //PRINTF
	convert_to_grid(map);
	ft_print_grid(map->grid, map->height, map->width);
	return (0);
}