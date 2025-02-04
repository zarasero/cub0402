#include "cub3d.h"

void find_player_position(Game *game)
{
    while (game->temp_i < game->map_height)
    {
        while (game->temp_j < game->map_width)
        {
            if (strchr("NSWE", game->map[game->temp_i][game->temp_j]))
            {
                game->player_x = game->temp_j;
                game->player_y = game->temp_i;
                if (game->map[game->temp_i][game->temp_j] == 'E')
                    game->player_angle = 0;
                else if (game->map[game->temp_i][game->temp_j] == 'N')
                    game->player_angle = M_PI / 2;
                else if (game->map[game->temp_i][game->temp_j] == 'W')
                    game->player_angle = M_PI;
                else if (game->map[game->temp_i][game->temp_j] == 'S')
                    game->player_angle = 3 * M_PI / 2;
                return;
            }
            game->temp_j++;
        }
        game->temp_i++;
        game->temp_j = 0;
    }
}

void ft_resoures_initialisation(Game *game)
{
    int i;

    i = -1;
    while (++i < 4) 
    {
        game->texture[i].img = mlx_xpm_file_to_image(game->mlx, game->path_text[i],
                &game->texture[i].width, &game->texture[i].height);
        if (!game->texture[i].img)
        {
            printf("Error\nCan't read texture file: %s\n", game->path_text[i]);
            ft_destroy_exit(game);
        }
        game->texture[i].addr = mlx_get_data_addr(game->texture[i].img,
                &game->texture[i].bits_per_pixel, &game->texture[i].line_length,
                &game->texture[i].endian);
        if (!game->texture[i].addr)
        {
            printf("Error\nFailed to get image data for texture:  %s\n", game->path_text[i]);
            ft_destroy_exit(game);
        }
    }
}

void ft_param_initialisation(Game *game)
{
    game->map_height = 10;
    game->map_width = 12;
    game->player_x = 0.0;
    game->player_y = 0.0;
    game->temp_j = 0;
    game->temp_i = 0;
    game->color_ceiling = 0x87CEEB;
    game->color_floor = 0x2E8B57;
    game->path_text[0] = "./textures/N.xpm";
    game->path_text[1] = "./textures/E.xpm";
    game->path_text[2] = "./textures/S.xpm";
    game->path_text[3] = "./textures/W.xpm";
    game->mlx = mlx_init();
    if (!game->mlx)
    {
         printf("Error: mlx_init() returned NULL\n");
         exit(1);
    }
    game->win = mlx_new_window(game->mlx, WINDOW_W, WINDOW_H, "Game");
    if (!game->win)
    {
        printf("Error: game.win == NULL\n");
        exit(1);
    }
}

int main() {
    Game game;
    char *map[] = {
        "111111111111",
        "100000000101",
        "100000010001",
        "1000000000S1",
        "100000010001",
        "100000000001",
        "100000000001",
        "100000000001",
        "100000010001",
        "111111111111",
    };
    game.map = map;
    ft_param_initialisation(&game);
    ft_resoures_initialisation(&game);
    find_player_position(&game);
    ft_draw(&game);
    mlx_key_hook(game.win, ft_key, (void *)&game);
   // mlx_hook(game.win, 2, 1, ft_key, (void *)&game);
    mlx_hook(game.win, 17, 0, ft_destroy_exit, (void *)&game); 
   // mlx_hook(game.win, 17, 0, mlx_loop_end, (void *)&game); 
    mlx_loop(game.mlx);
    ft_destroy_exit(&game);
    return (0);
}
