/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:19:10 by hyna              #+#    #+#             */
/*   Updated: 2022/12/27 14:36:33 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include "mlx.h"

typedef struct s_textures {
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor[3];
	int		ceiling[3];
}	t_textures;

typedef struct s_info {
	char	**map;
	int		max_wid;
	int		pos_x;
	int		pos_y;
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

void	perror_exit(void);
void	parser(t_textures	*textures, t_info	*info, char	*arg);
char	**ft_split2(char	*str, char	*charset);

#endif