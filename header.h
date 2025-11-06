#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "./libft/libft.h"
#include "./minilibx-linux/mlx.h"
#include "./get_next_line/get_next_line.h"


#define HEIGHT 800
#define WIDTH 600
#define ROW
#define COL
#define SUCCESS 0
#define ERROR 1
#define PARSING_ERROR -1
#define LINE_EMPTY 0
#define LINE_CONFIG 1
#define LINE_MAP 2

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363


typedef struct s_img
{
	void *img_ptr;
	char *addr;
	int bpp;
	int line_len;
	int endiant;
} t_img;

typedef struct s_datagame
{
	t_img *img;
	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;

	int floor_color;
	int ceiling_color;

	// info de la map
	char **map;
	int map_height;
	int map_width;
	char *map_firstline;
	// info joueur

	int player_x;
	int player_y;
	char player_dir;
	
	int config_elements_read;
	void *mlx;
	void *win;
	int width;
	int height;
} t_datagame;

//parsing


//texture
int parse_texture_no(char *line, t_datagame *data);
int parse_texture_so(char *line, t_datagame *data);
int parse_texture_ea(char *line, t_datagame *data);
int parse_texture_we(char *line, t_datagame *data);

int	parse_fcolor(char *line, t_datagame *data);
int	parse_ccolor(char *line, t_datagame *data);

int	process_line(char *line, t_datagame *data);
int	parse_file(char *filename, t_datagame *data);
int parse_map(char *first_line,int fd, t_datagame *data);
int check_walls(t_datagame *data);
int valid_map(t_datagame *data);
int check_neighbor(t_datagame *data, int y, int x);
void init_data(t_datagame *data);
int draw_background(t_datagame *data);
// static void	put_pixel(t_datagame *data, int x, int y, int color);



// utils
int	ft_isspace(char c);
int ft_strlen_array(char **arr);
void free_array(char **arr);
int ft_lstadd_back_new(t_list **list, void *content);
void cleanup_data(t_datagame *data);
int	is_valid_number(char *str);


#endif
