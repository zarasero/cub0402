#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <unistd.h> 
# define STEP_LINE 0.1
# define STEP_ANGLE 0.05
# define M_PI 3.14159265358979323846


# define WINDOW_W 800
# define WINDOW_H 600

# define VIEW_ANGLE (M_PI / 3)

typedef struct s_texture {
    void *img;
    int width;
    int height;
    int bits_per_pixel;
    int line_length;
    int endian;
    char *addr;
} t_texture;


typedef struct s_image {
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_image;

typedef struct s_draw_params {
    float line_height;
    float texture_position;
    float texture_step;
    t_texture *texture;
} t_draw_params;


typedef struct {
    int color_ceiling;
    int color_floor;
    int map_height;
    int map_width;
    int temp_j;
    int temp_i;
    char **map;
    float player_x;
    float player_y;
    float player_angle;
    t_texture texture[4];  // Текстуры для N, S, W, E
    char *path_text[4];  // Пути к файлам текстур
    void *mlx;  // Экземпляр MiniLibX
    void *win;  // Указатель на окно
    t_image img;  // Изображение для рендеринга
    int textur_index;  // Индекс текущей текстуры
    float textur_shift;   // Смещение в текстуре
    float view;  // Viewing angle, e.g., player view angle

} Game;

// Структура для работы с лучами
typedef struct s_ray {
    float direction_x;
    float direction_y;
    float step_x;
    float step_y;
    float next_vertical_x;
    float next_vertical_y;
    float next_horizontal_x;
    float next_horizontal_y;
    float vertical_distance;
    float horizontal_distance;
    float texture_x; 
    float texture_y;
        int map_x;
    int map_y;
} Ray;


int ft_prepare_texture(Game *game, float distance, t_draw_params *params);
void ft_draw_column(Game *game, int x, t_draw_params *params);
void ft_draw_vertical_line(Game *game, int x, float distance);
void ft_init_vertical_line(Game *game);
void ft_draw_ceiling_and_floor(Game *game);
int ft_draw(Game *game);

void find_player_position(Game *game);
void ft_resoures_initialisation(Game *game);
void ft_param_initialisation(Game *game);

void ft_move(Game *game, int direction);
int ft_key(int keycode, Game *game);

float trace_ray(Game *game, float angle);
float handle_horizontal_intersection(Game *game, Ray *ray);
float handle_vertical_intersection(Game *game, Ray *ray);
float handle_check(Game *game, Ray *ray, int flag);
void calculate_next_intersection(Game *game, Ray *ray);
void initialize_ray(Game *game, Ray *ray, float angle);


int ft_destroy_exit(Game *game);
int get_sign(float value);


#endif
