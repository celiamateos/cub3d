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

//     char *dir;
//     int     i;
//     while (line[i])
//     {
//         while (ft_isspace(line[i]))
//             i++;
//         if (line[i++] == elem[0] && line[i++] == elem[1])
//             while (ft_isspace(line[i]))
//                 i++;
//         if (line[i])
//              = ft_substr(line, i, ft_strlen(line))

//         i++;
//     }
//     return NULL;
// }

char *ft_search_element(char *line, char *elem)
{
    char **element;
    char    *dir;
    int fd;

    element = ft_split(line, ' ');
    if (!element)
        return NULL;
    printf("element[0]:%s|\n", element[0]);
    printf("element[1]:%s|\n", element[1]);
    if (ft_strncmp(element[0], elem, ft_strlen(element[0])))
    {
        printf("ei");
        dir = ft_substr(element[1], 0, ft_strlen(element[1]));
        fd = open(element[1], O_RDONLY);
        ft_freearray(element);
        if (fd < 0)
            err("error: fd: invalid map\n"), exit(1);
        return dir;
    }
    return NULL;
}

void save_data_map(t_data *data, char *line)
{
    char *element;
    // while (line && data->map->num_elem < 7)
    // {
        element = ft_search_element(line, "NO");
        if (element)
        {
            if (data->map->north_route)
                err("invalid map\n"), exit(1);
            data->map->north_route = element;
            printf("north_route:%s\n", data->map->north_route);
            free (element);
        }
    // }
}

void readmap(t_data *data, char *file)
{
    char    *line;
    // t_map	*map;

    // line = data->map->line;
    data->map->fd = open(file, O_RDONLY);
    if (data->map->fd < 0)
        exit(1);
    if ((line = (char *)malloc(sizeof(char))) == NULL)
        exit(1);
    while (1)
    {
        // printf("reading map\n");
        line = get_next_line(data->map->fd);
        if (line == NULL)
            break ;
        if (line && !check_emptyorspace(line))
        {
            printf("line:%s", line);
            save_data_map(data, line);
            data->map->num_elem++;
            if (data->map->num_elem  > 3)
                break ;
        }
        free(line);
    }
    free(line);
    close(data->map->fd);
    //segmentation fault ?? 
}

void load_map(t_data *data, char *file)
{

    // if (!map)
    //     exit(1);
    readmap(data, file);

}