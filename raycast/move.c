#include "cub3d.h"

void ft_move(Game *game, int direction)
{
    float dist;
    float move_x, move_y;
    float angle;

    angle = game->player_angle + direction * M_PI / 2;
    move_x = STEP_LINE * cos(angle);
    move_y = STEP_LINE * sin(angle);
    dist = trace_ray(game, angle);
    if (dist < STEP_LINE)
        move_x = move_y = 0;
    game->player_x += move_x;
    game->player_y -= move_y;
}

int ft_key(int keycode, Game *game)
{
    if (keycode == 65307)
       mlx_loop_end(game->mlx);
    else if (keycode == 65362 || keycode == 119)
        ft_move(game, 0);
    else if (keycode == 65364 || keycode == 115)
        ft_move(game, 2);
    else if (keycode == 97)
        ft_move(game, 1);
    else if (keycode == 100)
        ft_move(game, -1);
    else if (keycode == 65361 || keycode == 65363)
    {
        if (keycode == 65361)
          game->player_angle += STEP_ANGLE;
        else
            game->player_angle -= STEP_ANGLE;
        if (game->player_angle >= 2 * M_PI)
            game->player_angle -= 2 * M_PI;
        if (game->player_angle < 0)
            game->player_angle += 2 * M_PI;
        }
    else
        return (0);
    ft_draw(game);
    return (0);
}

