
#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include "mlx.h"

typedef enum e_idf {
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
	FLOOR = 4,
	CEILING = 5
}	t_idf;

typedef struct s_textures {
	char	*filename[4];
	int		floor[3];
	int		ceiling[3];
}	t_textures;

typedef struct s_info {
	char	**map;
	int		max_wid;
	int		max_hei;
	int		pos_x;
	int		pos_y;
	int		dir;
}	t_info;

typedef struct s_img
{
	void	*image;
	int		img_width;
	int		img_height;
	int		bpp;
	int		size_l;
	int		endian;
}	t_img;

typedef struct s_data {
	void	*mlx;
	void	*win;
	t_img	imgs[4];
}	t_data;

void	cut_map(char	**file, t_info	*info);
void	perror_exit(void);
void	parser(t_textures	*textures, t_info	*info, char	*arg);
char	**ft_split2(char	*str, char	*charset);
int	padding_map(char **map, t_info *info);
int		validate_map(t_info *info, t_textures *textures, char	*filename);

#endif