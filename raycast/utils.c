
#include "cub3d.h"

int get_sign(float value)
{
    if (value < 0)
        return (-1);
    return (1);
}

int ft_destroy_exit(Game *game)
{
    int i;

    mlx_clear_window(game->mlx, game->win);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    i = -1;
    while (++i < 4)
    {
        if (game->texture[i].img)
            mlx_destroy_image(game->mlx, game->texture[i].img);
    }
    if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
    exit(0);
}
