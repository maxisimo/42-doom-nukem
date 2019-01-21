/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:11:51 by thbernar          #+#    #+#             */
/*   Updated: 2019/01/16 17:37:42 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	bmp_getfile_size(t_bmp *bmp, int fd)
{
	unsigned char	c;
	int				i;
	int				bytes_read;

	i = 0;
	while (i < 18 && (bytes_read = read(fd, &c, 1)) != 0)
	{
		i++;
	}
	read(fd, &c, 1);
	bmp->width = c;
	read(fd, &c, 1);
	bmp->width += c << 8;
	read(fd, &c, 1);
	bmp->width += c << 16;
	read(fd, &c, 1);
	bmp->width += c << 24;
	read(fd, &c, 1);
	bmp->height = c;
	read(fd, &c, 1);
	bmp->height += c << 8;
	read(fd, &c, 1);
	bmp->height += c << 16;
	read(fd, &c, 1);
	bmp->height += c << 24;
}

static void	bmp_getfile_data(t_bmp *bmp, int fd, int i, int b_r)
{
	unsigned char	c;
	int				size;

	i = 0;
	size = bmp->width * bmp->height * 3;
	while ((b_r = read(fd, &c, 1)) != 0 && i < size)
	{
		bmp->data[i] = c;
		i++;
	}
}

static void	bmp_readfile(t_bmp *bmp, int fd, int w, int h)
{
	int				i;
	int				j;
	int				bytes_read;
	unsigned char	c;

	i = 0;
	j = 0;
	bytes_read = 1;
	bmp_getfile_size(bmp, fd);
	if (bmp->width != w || bmp->height != h)
		ft_error("Oops, something went wrong !");
	i = i + 8;
	bmp->data = (int *)malloc(sizeof(int) * bmp->width * bmp->height * 3);
	if (!bmp->data)
		exit(-1);
	while (i < 36 && read(fd, &c, 1))
	{
		i++;
	}
	bmp_getfile_data(bmp, fd, i, bytes_read);
}

void		bmp_loadfile(t_bmp *bmp, char *fname, int w, int h)
{
	int fd;

	if (((fd = open(fname, O_RDONLY)) < 0))
	{
		ft_putstr("Fatal error : invalid file.");
		exit(-1);
	}
	bmp_readfile(bmp, fd, w, h);
	bmp->scale = 1.0;
	ft_putstr(fname);
	ft_putstr(" loaded.\n");
}

t_color		get_pixel_color(t_bmp *img, int x, int y)
{
	int		os;
	t_color	color;

	if ((x >= 0 && x <= img->width) && (y >= 0 && y <= img->height))
	{
		os = (x + (img->height - (y + 1)) * img->width);
		os = os * 3;
		color.b = img->data[os];
		color.g = img->data[os + 1];
		color.r = img->data[os + 2];
	}
	else
	{
		color.b = 0;
		color.g = 0;
		color.r = 0;
	}
	return (color);
}
