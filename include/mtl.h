/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 12:30:28 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/16 13:17:24 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>

typedef enum	e_mtl_error
{
	No_Error,
	Error_Malloc,
	Wrong_Newmtl,
	No_Valid_Value,
	No_Valid_K_Value,
	No_Valid_Map_Value,
	Invalid_Map_Value,
	Invalid_D_Value,
	Invalid_Digit,
	Invalid_Digit_Dot,
	Invalid_Color,
	Invalid_Ns_Value,
	Invalid_Ni_Value,
	Invalid_Sharpness_Value,
	Color_Already_Attribute,
	Wrong_Illum,
	Invalid_Illum,
	Info_Already_Exists,
	Name_Already_Exists,
}				t_mtl_error;

typedef struct	s_mtl_reader
{
	int		fd;
	char	*buffer;
	size_t	buffer_size;
	size_t	len;
	size_t	i;
	size_t	column;
	size_t	line;
}				t_mtl_reader;

typedef struct	s_mtl_color
{
	double		a;
	double		b;
	double		c;
}				t_mtl_color;

typedef struct s_mtl_material
{
	char		*name;
	t_mtl_color	ka;
	t_mtl_color kd;
	t_mtl_color ks;
	double		d;
	double		illum;
	double		ns;
	double		ni;
	double		sharpeness;
	char		*ka_map;
	char		*kd_map;
	char		*ks_map;
	char		*ni_map;
	char		*ns_map;

}				t_mtl_material;

typedef struct	s_mtl
{
	size_t			len;
	size_t			capacity;
	t_mtl_material	*inner;
}				t_mtl;


void			skip_ws(t_mtl_reader *r, bool newline);
bool			reader_cmp(t_mtl_reader *r, char *str);

t_mtl			create_mtl(size_t capacity);
bool			append_material(t_mtl *mtl, t_mtl_material material);
bool			append_char(char **str, char c, size_t *size , size_t i);

t_mtl_error		read_digit(t_mtl_reader *r, double *digit);
t_mtl_error		read_str(t_mtl_reader *r, char **str);

t_mtl_error     read_material(t_mtl_reader *r, t_mtl_material *material);
t_mtl_error     read_material_k(t_mtl_reader *r, t_mtl_material *material);
t_mtl_error     read_material_n(t_mtl_reader *r, t_mtl_material *material);

t_mtl_reader	create_reader(int fd, char *buffer, size_t buffer_size);
int16_t			reader_peek(t_mtl_reader *self);
void			reader_next(t_mtl_reader *self);


#endif