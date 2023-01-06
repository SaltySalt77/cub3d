/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:08:54 by hyna              #+#    #+#             */
/*   Updated: 2023/01/06 12:08:57 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "mlx.h"

typedef enum e_idf {
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
	FLOOR = 4,
	CEILING = 5
}	t_idf;

# define SCREEN_HEIGHT 480
# define SCREEN_WIDTH 640
# define TEX_WIDTH 32

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT	17
# define KEY_ESC			53
# define KEY_W				13
# define KEY_A				0
# define KEY_S				1
# define KEY_D				2
# define KEY_L				123
# define KEY_R				124

# define ROT_SPEED			0.03
# define MOVE_SPEED			0.05

typedef struct s_textures {
	char	*filename[4];
	int		floor[3];
	int		ceiling[3];
}	t_textures;

typedef struct s_move{
	int	w;
	int	a;
	int	s;
	int	d;
	int	l;
	int	r;
}	t_move;

typedef struct s_info {
	char	**map;
	int		max_wid;
	int		max_hei;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		dir;
	t_move	move;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	double	ray_dir_x;
	double	ray_dir_y;
}	t_info;

typedef struct s_img
{
	void	*image;
	int		img_width;
	int		img_height;
	int		bpp;
	int		size_l;
	int		endian;
	int		*addr;
	int		tex_x;
	int		tex_y;
}	t_img;

typedef struct s_data {
	void		*mlx;
	void		*win;
	t_img		imgs[4];
	t_textures	textures;
	t_info		*info;
	t_img		*img_buff;
}	t_data;

void	cut_map(char	**file, t_info	*info);
void	perror_exit(char *err_msg);
void	parser(t_textures	*textures, t_info	*info, char	*arg);
char	**ft_split2(char	*str, char	*charset);
int		padding_map(t_info *info);
int		validate_map(t_info *info, char	*filename);
int		check_vec(t_info *info);
void	assort_textures(char **file, t_textures	*textures, char	*std[6]);
int		save_rgb(int	*rgb, char	**line);
int		validate_newline(char	*filename, t_info	*info);
void	init_info(t_info *info);

int		key_hook(t_info *info);
void	key_hook_a(t_info	*info);
void	key_hook_d(t_info	*info);
void	key_hook_w(t_info *info);
void	key_hook_s(t_info	*info);

void	key_hook_r(t_info	*info);
void	key_hook_l(t_info	*info);

int		press_key(int key_code, t_data *m_data);
int		release_key(int key_code, t_info *info);

int		exit_game(t_data *m_data);
void	init_game(t_data *m_data, t_textures *textures);

int		ray_casting(void	*value);

void	paint_back(t_data *m_data, t_img *buffer);
void	draw_line(t_data *m_data, int text_num, int lineHeight, int x);
int		init_side_dist(double rayDir, double pos, double *sideDist,
			double deltaDist);
int		check_texture(double rayDirX, double rayDirY, int side);
void	check_fc(char **file);

#endif
