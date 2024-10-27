#include <cub3d.h>

void draw_line(t_vec2 start, t_vec2 end, mlx_image_t *img, uint32_t color);
t_vec2 get_ray_direction(double angle);

// void    do_raycast(t_vec2 pos, double look_angle, t_raycast *r, int **map)
// {
//     r->pos = pos;
//     r->dir = get_ray_direction(look_angle);
// }

int trace_ray(t_vec2 pos, double look_angle, t_raycast *r, t_map *map)
{
    t_vec2  ray_dir = get_ray_direction(look_angle);
    t_vec2  ray_pos = pos;
    float   step_size = 0.1f;
    int     max_steps = 100;
    int     i;

    i = -1;
    while (++i < max_steps)
    {
        ray_pos.x += ray_dir.x * step_size;
        ray_pos.y += ray_dir.y * step_size;

        int map_x = (int)ray_pos.x;
        int map_y = (int)ray_pos.y;

        if (map->grid[map_y][map_x] != 0)
        {
            printf("Ray hit wall [%d][%d]\n", map_x, map_y);
            return (1);
        }
    }

    draw_line(pos, ray_pos, map->game->screen, 0xFFFF88);
    return (0);
}

t_vec2 get_ray_direction(double angle)
{
    t_vec2  direction;

    direction.x = cos(angle * PI_ / 180.0);
    direction.y = sin(angle * PI_ / 180.0);
    return (direction);
}

void draw_line(t_vec2 start, t_vec2 end, mlx_image_t *img, uint32_t color)
{
    t_vec2  delta;
    t_vec2  px;
    int  pixels;
    int  i;

    i = -1;
    delta.x = end.x - start.x;
    delta.y = end.y - start.y;
    px.x = start.x;
    px.y = start.y;
    pixels = sqrt((delta.x * delta.x) + (delta.y * delta.y));
    while (++i < pixels)
    {
        mlx_put_pixel(img, px.x, px.y, color);
        px.x += delta.x / pixels;
        px.y += delta.y / pixels;
    }
}
