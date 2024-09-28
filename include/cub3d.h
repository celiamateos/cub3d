/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:00:09 by cmateos-          #+#    #+#             */
/*   Updated: 2024/09/26 18:00:17 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../libft/libft.h" 
# include <unistd.h>
# include <stdio.h>
# include <string.h> 
# include <stdlib.h> 
# include <fcntl.h>
//# include <mlx.h>
# include <stdarg.h> 
# include <limits.h> 
# include <errno.h>



typedef struct map
{
    int     fd;
    char    *line;
}   t_map;

typedef struct  s_data
{
	t_map   *map;

}   t_data;



void err(char *str);
void load_map(t_data *data, char *file);
void readmap(t_data *data, char *file);

#endif
