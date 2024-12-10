#ifndef DUAL_H
# define DUAL_H

# define MLX_CONNECTION "connection between with the display not established"
# define WIN_CONNECTION "window could not be created"

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

typedef struct s_data
{
	t_img		img;
	void		*mlx;
	void		*win;
}	t_data;

#endif