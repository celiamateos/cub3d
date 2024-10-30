/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:26:57 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/30 22:54:52 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int check_player_direction(t_player *player, char c, int row, int i)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (1);
	else
	{
		set_looking_angle(c, &player->looking_angle);
		player->player_dir = c;
		player->player_count += 1 ;
		player->position.y = row;
		player->position.x = i;
		player->ray_angle = player->looking_angle - HALF_FOV;
	}
	return (0);
}


void    check_content_map_and_save_player_dir(t_map *map, t_player *p, char *line, int row)
{
	int i;

	i = 0;
	if (line && line[i])
	{
		while (line[i])
		{
			if (line[i] && line[i] != '0' && line[i] != '1' && line[i] != ' ' && line[i] != '\n')
			{
				if (check_player_direction(p, line[i], row, i))
					err(RED"error: invalid map: Bad character\n"RESET), exit(1); //freee
			}
			i++;
		}
	}
	if (map->width < i)
		map->width = i - 1;
}

void	save_map(t_map *map, char *str)
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
		exit(1); //Free
	while (++i != len)
	{
		aux[i] = ft_strdup(map->map[i]);
		if (!aux[i])
			ft_free_error_arr(aux, i), exit(1); //Free
	}
	aux[i] = ft_strdup(str);
	if (!aux[i])
		ft_free_error_arr(aux, i), exit(1); //Free
	aux[++i] = NULL;
	if (map->map)
		ft_freearray(map->map);
	map->map = aux;
}

void readmap(t_map *map, t_player *player)
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
				check_content_map_and_save_player_dir(map, player, line, i);
				save_map(map, line);
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
void	set_player_info(t_map map, t_player *p)
{
	
}
void load_map(t_map *map, t_player *player, char *file)
{
	int i;
	
	i = 0;
	map->fd = open(file, O_RDONLY);
	if (map->fd < 0)
		err(RED"error: fd: cannot open\n"RESET), exit(1);
	readmap(map, player);
	close(map->fd);
	if (map->num_elem != 6)
		err(RED"error: map: invalid elements count\n"RESET), exit(1); //free
	if (player->player_count != 1)
		err(RED"error: invalid map: Enter a player\n"RESET), exit(1); //freee 
	printf(YELLOW"\nplayer_direction:%c\n\n"RESET, player->player_dir);
	if (!map_closed(map->map,player->position.x, player->position.y) || !check_valid_map(map->map))
		printf(RED"error: Map is not closed\n"RESET), exit(1);
	ft_printarray(map->map); //PRINT map-> char **map
	printf(BLUE"\nPlayer position: [%d][%d]\n"RESET, player->position.y, player->position.x); //PRINTF
	printf(GREEN"\nMap height: %d\n"RESET, map->height); //PRINTF
	printf(GREEN"Map width: %d\n"RESET, map->width); //PRINTF
	map->grid = map_to_int(map->map, map->height, map->width);
	// print grid to check:
	while (map->grid[i])
	{
		ft_printintarray(map->grid[i], map->width);
		i++;
	}
}