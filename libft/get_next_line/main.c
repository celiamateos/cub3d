/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:11:03 by cmateos-          #+#    #+#             */
/*   Updated: 2023/05/08 19:24:58 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
static void	ft_leaks()
{	
	system("leaks a.out");
}
*/
int	main(void)
{
	int		fd;
	char	*gnl;

//	atexit(ft_leaks);
	fd = open("myfd.txt", O_RDONLY);
//	printf("File descriptor asignado: %d\n", fd);
	if (fd < 0)
		return (0);
	while (1)
	{
		gnl = get_next_line(fd);
		printf("line: %s", gnl);
		free(gnl);
		if (gnl == NULL)
			break ;
	}
	system("leaks -q a.out");
	close(fd);
	return (0);
}

















/*
int	main(int argc, char **argv)
{
 	int	fd;
	char *line;
	(void)argc;

	fd = open(argv[1], O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
//	system("leaks a.out");
	}
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
	return (0);
}*/
