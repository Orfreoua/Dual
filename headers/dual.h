#ifndef DUAL_H
# define DUAL_H

# define MLX_CONNECTION	"Connection between with the display not established."
# define WIN_CONNECTION	"Window could not be created."
# define IMG_CREATE		"Unable to create a new image with MiniLibX"

typedef struct s_img
{
	void		*img;
	void		*data;
	int			bpp;
	int			size_line;
	int			endian;
	int			height;
	int			width;
	char		*addr;
}	t_img;

typedef struct s_point {
    int x;
    int y;
} t_point;

typedef struct s_size {
    int width;
    int height;
} t_size;

typedef struct s_data
{
	t_img		img;
	void		*mlx;
	void		*win;
	t_point		point;
}	t_data;

void paste_resized_image(t_data *data, t_point point, t_size size, char *path);
t_size get_image_size(void *mlx, char *path);

#endif