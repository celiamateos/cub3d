#include <cub3d.h>

void draw_line(t_vec2 start, t_vec2 end, mlx_image_t *img, uint32_t color);
t_vec2 get_ray_direction(double angle);
t_vec2 get_scaled_pos(t_vec2 pos);
// void    do_raycast(t_vec2 pos, double look_angle, t_raycast *r, int **map)
// {
//     r->pos = pos;
//     r->dir = get_ray_direction(look_angle);
// }
/**
 * @brief 
 * 
 * @param pos 
 * @param look_angle 
 * @param r_angle 
 * @param r 
 * @param map 
 * @return Distance to the first wall
 */
int trace_ray(t_vec2 pos, double look_angle, double r_angle, t_raycast *r, t_map *map)
{
    t_vec2  ray_dir = get_ray_direction(look_angle);
    t_vec2  ray_pos = pos;
    float   step_size = 0.1f;
    int     max_steps = 100;
    int     i;
    int map_x;
    int map_y;
    t_vec2  start;
    t_vec2  end;

    i = -1;
    while (++i < max_steps)
    {
        ray_pos.x += ray_dir.x * PROJECTION_DISTANCE;
        ray_pos.y += ray_dir.y * PROJECTION_DISTANCE;

        map_x = (int)ray_pos.x;
        map_y = (int)ray_pos.y;

        if (map->grid[map_y][map_x] != 0)
        {
            // printf("Ray hit wall [%d][%d]\n", map_x, map_y);
            // start = get_scaled_pos(pos);
            // end = get_scaled_pos(ray_pos);
            // draw_line(start, end, map->game->screen, 0xFFFF88);
            return (sqrt((ray_pos.x - pos.x) * (ray_pos.x - pos.x) + (ray_pos.y - pos.y) * (ray_pos.y - pos.y)));
        }
    }
    // start = get_scaled_pos(pos);
    // end = get_scaled_pos(ray_pos);
    // draw_line(start, end, map->game->screen, 0xFFFF88);
    return (-1);
}

/**
 * @brief Same as set_rotation. Delete one of them
 * 
 * @param angle 
 * @return t_vec2 
 */
t_vec2 get_ray_direction(double angle)
{
    t_vec2  direction;

    direction.x = cos(angle * PI_ / 180.0);
    direction.y = -sin(angle * PI_ / 180.0);
    return (direction);
}

/**
 * @brief Obtains the magnitude(distance) between player and wall using the
 * pythagorean rule (distance formula), and draws it.
 * 
 * @param start player position
 * @param end wall position
 * @param img 
 * @param color 
 */
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

/**
 * @brief Scales player position to the minimap size. 
 * (Adds + MINIMAP_SIZE because border of minimap)
 * 
 * @param pos player position
 * @return t_vec2 scaled position
 */
t_vec2 get_scaled_pos(t_vec2 pos)
{
    t_vec2  scaled;

    scaled.x = pos.x * MINIMAP_SIZE + MINIMAP_SIZE;
    scaled.y = pos.y * MINIMAP_SIZE + MINIMAP_SIZE;
    return (scaled);
}
