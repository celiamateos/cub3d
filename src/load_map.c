/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:26:57 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/01 21:05:18 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

char *ft_search_element(char **element, char *elem)
{
    char    *dir;
    int     fd;

    dir = ft_substr(element[1], 0, (ft_strlen(element[1]) - 1));
    if (!dir)
        return (err(RED"error: malloc\n"RESET)), NULL; //free
    fd = open(dir, O_RDONLY);
    if (fd < 0)
        return err(RED "error: map: fd: invalid element route\n" RESET), NULL;
    return (dir);
}

int *load_data_color_map(char *str)
{
    int *result;

    char **tmp = ft_split(str, ',');
    if (!tmp || (ft_arraylen(tmp) != 3))
        err(RED"error: element map: ceiling or floor\n"RESET), exit(1); //free y tal
    result[0] = ft_atoi(tmp[0]);
    result[1] = ft_atoi(tmp[1]);
    result[2] = ft_atoi(tmp[2]);

    if (result[0] < 0 || result[0] > 255 || result[1] < 0 || result[1] > 255 || result[2] < 0 || result[2] > 255)
        err(RED"error: element map: bad rgb params\n"RESET), exit(1); //free y tal
    ft_freearray(tmp);
    return (result);
}

void save_colors_map(t_data *data, char ***elements)
{
    char **element = *elements;
    if (!data->map->ceiling_route && !ft_strncmp(element[0], "C", ft_strlen(element[0])))
    {
        if ((data->map->ceiling_route = load_data_color_map(element[1])) && !data->map->ceiling_route)
            err(RED"error: invalid map\n"RESET), ft_freearray(element), exit(1); //free..
        printf(GREEN"ceiling_route:"RESET);
        ft_printintarray(data->map->ceiling_route, 3);
    }
    else if (!data->map->floor_route && !ft_strncmp(element[0], "F", ft_strlen(element[0])))
    {
        if ((data->map->floor_route = load_data_color_map(element[1])) && !data->map->floor_route)
            err(RED"error: invalid map\n"RESET), ft_freearray(element), exit(1); //free..
        printf(GREEN"floor_route:"RESET);
        ft_printintarray(data->map->floor_route, 3);
    }
    else
        err(RED"error: map: invalid elements\n"RESET), ft_freearray(element), exit(1);
    data->map->num_elem += 1;
}

void save_element_map(t_data *data, char ***elements)
{
    char **element = *elements;

    if (!data->map->north_route && !ft_strncmp(element[0], "NO", ft_strlen(element[0])))
    {
        if ((data->map->north_route = ft_search_element(element, "NO")) && !data->map->north_route)
            err(RED"error: invalid map\n"RESET), ft_freearray(element), exit(1); //free..
        printf(GREEN"north_route:%s\n"RESET, data->map->north_route);
    }
    else if (!data->map->south_route && !ft_strncmp(element[0], "SO", ft_strlen(element[0])))
    {
        if ((data->map->south_route = ft_search_element(element, "SO")) && !data->map->south_route)
            err(RED"error: invalid map\n"RESET), ft_freearray(element), exit(1); //free..
        printf(GREEN"south_route:%s\n"RESET, data->map->south_route);
    }
    else if (!data->map->east_route && !ft_strncmp(element[0], "EA", ft_strlen(element[0])))
    {
        if ((data->map->east_route = ft_search_element(element, "EA")) && !data->map->east_route)
            err(RED"error: invalid map\n"RESET), ft_freearray(element), exit(1); //free..
        printf(GREEN"east_route:%s\n"RESET, data->map->east_route);
    }
    else if (!data->map->west_route && !ft_strncmp(element[0], "WE", ft_strlen(element[0])))
    {
        if ((data->map->west_route = ft_search_element(element, "WE")) && !data->map->west_route)
            err(RED"error: invalid map\n"RESET), ft_freearray(element), exit(1); //free..
        printf(GREEN"west_route:%s\n"RESET, data->map->west_route);
    }
    else
        err(RED"error: map: invalid elements\n"RESET), ft_freearray(element), exit(1); //free..
    data->map->num_elem += 1;
}

void save_data_map(t_data *data, char *line)
{
    char **element = ft_split(line, ' ');
    if (!element)
        exit(1); //Free data
    printf(BLUE"data->map->num_elem:%d\n"RESET, data->map->num_elem);
    if (data->map->num_elem < 4)
        save_element_map(data, &element);
    else if (data->map->num_elem < 6)
        save_colors_map(data, &element);
    ft_freearray(element);
}

int check_player_direction(t_data *data, char c, int row, int i)
{
    if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
        return (1);
    else
    {
        data->player->player_dir = c;
        data->player->player_count += 1 ;
        data->player->y = row;
        data->player->x = i;
    }
    return (0);
}

bool	cover_char(char c)
{
	return (c == '1' || c == '0' || c == '.');
}

size_t	double_pointer_len(char **double_pointer)
{
	size_t	len;

	if (!double_pointer)
		return (0);
	len = 0;
	while (double_pointer[len])
		len++;
	return (len);
}


bool	covered(char **m, size_t x, size_t y)
{
	bool	valid;

	valid = true;
	if (x == 0 || y == 0 || y == double_pointer_len(m) - 1
		|| x == ft_strlen(m[0]) - 1 || !cover_char(m[y - 1][x])
		|| !cover_char(m[y + 1][x]) || !cover_char(m[y][x - 1])
		|| !cover_char(m[y][x + 1]))
		valid = false;
	if (valid && (m[y - 1][x] == '0' || m[y + 1][x] == '0' || m[y][x - 1] == '0'
		|| m[y][x + 1] == '0'))
		m[y][x] = '.';
	if (valid && m[y - 1][x] == '0')
		valid = covered(m, x, y - 1);
	if (valid && m[y + 1][x] == '0')
		valid = covered(m, x, y + 1);
	if (valid && m[y][x - 1] == '0')
		valid = covered(m, x - 1, y);
	if (valid && m[y][x + 1] == '0')
		valid = covered(m, x + 1, y);
	m[y][x] = '.';
	return (valid);
}
bool	valid_map_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == '.' || c == '1')
		return (true);
	return (false);
}


int check_valid_map(t_data *data)
{
    int row;
    int i;
    char **m;

    row = 0;
    i = 0;
    m = data->map->map;
    while (m[row])
    { 
        while (m[row][i])
        {
            if (m[row][i] == '0')
                return (0);
            i++;
        }
        row++;
    }
    return (1);
}


int check_content_map_and_save_player_dir(t_data *data, char *line, int row)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] && line[i] != '0' && line[i] != '1' && line[i] != ' ' && line[i] != '\n')
        {
            if (check_player_direction(data, line[i], row, i))
                err(RED"error: invalid map: Bad character\n"RESET), exit(1); //freee
        }
        i++;
    }
    if (data->map->width < i)
        data->map->width = i - 1;
}


void readmap(t_data *data, char *file)
{
    char    *line;
    int     i;

    i = 0;
    data->map->fd = open(file, O_RDONLY);
    if (data->map->fd < 0)
        exit(1);
    if ((line = (char *)malloc(sizeof(char))) == NULL)
        exit(1);
    while (1)
    {
        line = get_next_line(data->map->fd);
        if (line && !check_emptyorspace(line))
        {
            if (data->map->num_elem != 6)
                save_data_map(data, line);
            else
            {
                check_content_map_and_save_player_dir(data, line, i);
                save_map(data, line);
                i++;
            }
        }
        if (line == NULL)
            break ;
        free(line);
    }
    free(line);
    close(data->map->fd);
    data->map->height = i;
}


void load_map(t_data *data, char *file)
{
    readmap(data, file);
    if (data->map->num_elem != 6)
        err(RED"error: map: invalid elements count\n"RESET), exit(1); //free
    if (data->player->player_count != 1)
        err(RED"error: invalid map: Enter a player\n"RESET), exit(1); //freee 
    printf(YELLOW"\nplayer_direction:%c\n\n"RESET, data->player->player_dir);
    covered(data->map->map, data->player->x, data->player->y);
    ft_printarray(data->map->map); //PRINT data->map-> char **map
    if (check_valid_map(data) == 0)
        printf(RED"error: Mapa no rodeado\n"RESET);
    printf(BLUE"\nPlayer position: [%d][%d]\n"RESET, data->player->y, data->player->x);
    printf(GREEN"\nMap height: %d\n"RESET, data->map->height);
    printf(GREEN"Map width: %d\n"RESET, data->map->width);
}