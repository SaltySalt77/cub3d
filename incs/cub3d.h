/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyna@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:19:10 by hyna              #+#    #+#             */
/*   Updated: 2022/12/26 16:14:37 by hyna             ###   ########.fr       */
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

void	perror_exit(void);
void	parser(t_textures	*textures, t_info	*info, char	*arg);

#endif