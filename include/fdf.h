/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:29:57 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/22 13:53:18 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"

typedef enum e_event
{
	KEYDOWN = 2,
	KEYUP = 3,
	MOUSEDOWN = 4,
	MOUSEUP = 5,
	MOUSEMOVE = 6,
	EXPOSE = 12,
	DESTROY = 17
}				t_event;

typedef enum e_key_linux
{
	ESC = 65307
}			t_key_linux;

typedef enum e_key_macos
{
	ESCM = 53
}			t_key_macos;

typedef struct s_point
{
	int				h;
	int				x;
	int				y;
	int				z;
	unsigned int	color;
}				t_point;

typedef struct s_pts_arr
{
	int	rows;
	int	cols;
	t_point	***arr;
}				t_pts_arr;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp; //bits_per_pixel
	int		size; //size_line
	int		end; //endian
}				t_img;

typedef struct s_fdata
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_pts_arr	pts;
	int		fd;
	t_list	*trash;
}				t_fdata;

/************************************ MAIN ************************************/
t_pts_arr		parse_map(t_fdata *data);

/************************** GARBAGE COLLECTOR *********************************/
void			*ft_mylloc(size_t size, t_list **trash);
void			*ft_cylloc(size_t nmemb, size_t size, t_list **trash);
void			*ft_add_garbage(t_list **trash, void *ptr);
void			ft_empty_trash(t_list **trash);

/********************************* MLX UTILS **********************************/
int				trgb_to_i(int t, int r, int g, int b);
int				i_to_trgb(int color, int *r, int *g, int *b);
void			pixel_put_img(t_img *img, int x, int y, int color);
int				put_points(t_fdata *d);

/******************************* EVENTS HANDLING ******************************/
int				handle_close(t_fdata *data);
int				handle_key(int keycode, t_fdata *data);

/************************** COMPATIBILITY FUNCTIONS ***************************/
int				mlx2_destroy_display(void *xvar);

/****************************** POINTS FUNCTIONS ******************************/
t_point			*new_point(t_point **res, t_point p, t_fdata *data);
t_point			***alloc_point_arr(t_pts_arr *pts, t_fdata *d);

/*********************************** UTILS ************************************/
int				ft_atoi_forward(const char *nptr, int *i);
unsigned int	ft_atou_base_forward(const char *nptr, const char *base, int *i);
t_list			*ft_lstnew2(void *content, t_list **trash);
int				end_fdf(t_fdata *data, int exit_code);
int				stop_perror(char *msg, t_fdata *data, int error);
int				stop_error(char *msg, t_fdata *data);

#endif
