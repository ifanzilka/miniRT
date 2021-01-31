/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_bmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:52:05 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/31 17:43:25 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>

#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

/*
**	BMP
** Bit Map file header - 14 bytes
**
** 2 [0-1] 2 bytes  -> in FileType
** 6 [2-5] 4 bytes  -> unsigned integer in File size
** 10 [6 -9] 4 bytes -> 	 RESERVED!!!
** 11 [10]   1 bytes -> FILE_HEADER_SIZE(14) + INFO_HEADER_SIZE(40)
*/

/*
**	BMP
**	Bit Map INFO_HEADER_SIZE - 40-bytes
**
**	12 [11 - 14] 4 bytes -> size of the header in bytes(40)
**	16 [15 - 18] 4 bytes ->	the width of the final image in pixels
**	20 [19 - 22] 4 bytes ->	the height of the final image in pixels
**	24 [23 - 24] 2 bytes -> plane the number of color planes
**		of the target device. Should be '1' in decimal.
** 	26 [25 - 26] 2 bytes  -> BitsPerPixel
** 	28 [27 - 30] 4 bytes ->	Compression
** 	32 [31 - 34] 4 bytes -> ImageSize
** 	36 [35 - 38] 4 bytes -> XpixelsPerMeter
** 	40 [39 - 42] 4 bytes -> YpixelsPerMeter
** 	44 [43 - 46] 4 bytes -> TotalColors
** 	48 [47 - 50] 4 bytes -> ImportantColors
*/

static	void		ft_create_file_header(t_rt *rt, int fd)
{
	unsigned char	*file_header;
	int				i;
	int				file_size;

	file_header = (unsigned char *)malloc(14 * sizeof(unsigned char));
	if (!file_header)
		ft_error_rt(err_malloc, rt);
	i = 0;
	while (i < 14)
	{
		file_header[i] = (unsigned char)(0);
		i++;
	}
	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE
		+ (4 * rt->reso.width * rt->reso.height);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
	write(fd, file_header, 14);
	free(file_header);
}

static	void		ft_create_info_header(t_rt *rt, int fd)
{
	int				i;
	unsigned char	*file_header;

	i = 0;
	file_header = (unsigned char *)malloc(40 * sizeof(unsigned char));
	if (!file_header)
		ft_error_rt(err_malloc, rt);
	while (i < 40)
	{
		file_header[i] = (unsigned char)(0);
		i++;
	}
	file_header[0] = (unsigned char)(40);
	file_header[4] = (unsigned char)(rt->reso.width);
	file_header[5] = (unsigned char)(rt->reso.width >> 8);
	file_header[6] = (unsigned char)(rt->reso.width >> 16);
	file_header[7] = (unsigned char)(rt->reso.width >> 24);
	file_header[8] = (unsigned char)(rt->reso.height);
	file_header[9] = (unsigned char)(rt->reso.height >> 8);
	file_header[10] = (unsigned char)(rt->reso.height >> 16);
	file_header[11] = (unsigned char)(rt->reso.height >> 24);
	file_header[12] = (unsigned char)(1);
	file_header[14] = (unsigned char)(32);
	write(fd, file_header, 40);
	free(file_header);
}

static	void		ft_create_image_to_file(t_rt *rt, t_img *img, int fd)
{
	int y;
	int line_length;

	line_length = rt->reso.width * img->bits_per_pixel / 8;
	y = rt->reso.height;
	while (0 <= y)
	{
		write(fd, (unsigned char *)(img->addr +
		y * img->line_length), line_length);
		y--;
	}
}

void				ft_create_bmp(t_rt *rt, t_img *img)
{
	int fd;

	if ((fd = open("screen.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0655)) > 1)
	{
		ft_create_file_header(rt, fd);
		ft_create_info_header(rt, fd);
		ft_create_image_to_file(rt, img, fd);
		close(fd);
	}
	else
	{
		perror("Error\n");
		ft_error_rt(err_rt, rt);
		exit(0);
	}
}
