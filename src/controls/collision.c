#include <cub3d.h>

int is_wall(t_map *map, t_vec2 pos)
{
    int x;
    int y;

    x = (int)pos.x;
    y = (int)pos.y;
    if (x < 0 || x >= map->width || y < 0 || y >= map->height)
        return (1);
    if (map->grid[y][x] != 0)
    {
        printf("A WALL !!\n");
        return (1);
    }
    return (0);
}