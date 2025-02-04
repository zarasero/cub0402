#include "cub3d.h"

void initialize_ray(Game *game, Ray *ray, float angle)
{
    ray->direction_x = cos(angle);
    ray->direction_y = -sin(angle);
    ray->step_x = get_sign(ray->direction_x);
    ray->step_y = get_sign(ray->direction_y);
    ray->next_vertical_x = floor(game->player_x) + (ray->step_x > 0);
    ray->next_horizontal_y = floor(game->player_y) + (ray->step_y > 0);
}

static float save_texture_info(Game *game, float distance, int texture_index, float texture_x)
{
    game->textur_index= texture_index;
    game->textur_shift = texture_x;
    return (distance);
}

void calculate_next_intersection(Game *game, Ray *ray)
{
    if (ray->step_x != 0)
    {
        ray->next_vertical_y = game->player_y + ray->direction_y / ray->direction_x * (ray->next_vertical_x - game->player_x);
        ray->vertical_distance = sqrt(pow(game->player_x - ray->next_vertical_x, 2.0) + pow(game->player_y - ray->next_vertical_y, 2.0));
        ray->texture_x = ray->next_vertical_y - (int) ray->next_vertical_y;
        if (ray->step_x > 0)
            ray->texture_x = 1 - ray->texture_x;
    } 
    else
        ray->vertical_distance = INFINITY;
    if (ray->step_y != 0)
    {
        ray->next_horizontal_x = game->player_x + ray->direction_x / ray->direction_y * (ray->next_horizontal_y - game->player_y);
        ray->horizontal_distance = sqrt(pow(game->player_x - ray->next_horizontal_x, 2.0) + pow(game->player_y - ray->next_horizontal_y, 2.0));
        ray->texture_y = ray->next_horizontal_x - (int) ray->next_horizontal_x;
        if (ray->step_y < 0) ray->texture_y = 1 - ray->texture_y;
    }
    else
        ray->horizontal_distance = INFINITY;
}

float handle_check(Game *game, Ray *ray, int flag)
{
    if(flag == 1)
    {
        ray->map_x = (int)ray->next_vertical_x;
        ray->map_y = (int)ray->next_vertical_y;
    }
    else
    {
        ray->map_y = (int)ray->next_horizontal_y;
        ray->map_x = (int)ray->next_horizontal_x;
    }
    if (ray->map_x < 0 || ray->map_x >= game->map_width || ray->map_y < 0 || ray->map_y >= game->map_height)
    {
        printf("Error: out of bounds array access");
        return (-1);
    }
    return (0);
}

float handle_vertical_intersection(Game *game, Ray *ray)
{
    int texture_index;
    int map_x_offset;

    if (handle_check(game, ray, 1) == -1)
        return (-1);
    if (ray->step_x > 0)
        map_x_offset = 0;
    else
        map_x_offset = -1;
    if (game->map[ray->map_y][ray->map_x + map_x_offset] == '1')
    {
        if (ray->step_x > 0)
            texture_index = 1;
        else
            texture_index = 3;
        return (save_texture_info(game, ray->vertical_distance, texture_index, ray->texture_x));
    }
    ray->next_vertical_x += ray->step_x;
    ray->next_vertical_y += ray->step_y;
    return (0);
}

float handle_horizontal_intersection(Game *game, Ray *ray)
{
    int texture_index;
     int map_y_offset;
    
    if (handle_check(game, ray, 0) == -1)
        return (-1);
    if (ray->step_y > 0)
        map_y_offset = 0;
    else
        map_y_offset = -1;
    if (game->map[ray->map_y + map_y_offset][ray->map_x] == '1')
    {   
        if (ray->step_y > 0)
            texture_index = 2;
        else
            texture_index = 0;
        return (save_texture_info(game, ray->horizontal_distance, texture_index, ray->texture_y));
    }
    ray->next_horizontal_x += ray->step_x;
    ray->next_horizontal_y += ray->step_y;
    return (0);
}

float trace_ray(Game *game, float angle)
{
    Ray ray;

    initialize_ray(game, &ray, angle);
    while (1)
    {
        calculate_next_intersection(game, &ray);
        if (ray.vertical_distance < ray.horizontal_distance)
        {
            float result = handle_vertical_intersection(game, &ray);
            if (result != 0)
                return (result);
        }
        else
        {
            float result = handle_horizontal_intersection(game, &ray);
            if (result != 0)
                return (result);
        }
    }
}
