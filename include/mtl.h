/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 12:30:28 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/16 11:30:43 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

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
	Info_Already_Exists,
}				t_mtl_error;

typedef struct	s_reader
{
	int		fd;
	char	*buffer;
	size_t	buffer_size;
	size_t	len;
	size_t	i;
	size_t	column;
	size_t	line;
}				t_reader;

typedef struct	s_color
{
	double		a;
	double		b;
	double		c;
}				t_color;

typedef union	u_mtl_value
{
	t_color		color;
	double		d;
	char 		*map;
}				t_mtl_value;

typedef enum	e_mtl_type
{
	Mtl_Ka,
	Mtl_Kd,
	Mtl_D,
	Mtl_Map_Ka,
	Mtl_Map_Kd
}				t_mtl_type;

typedef struct	s_material_value
{
	t_mtl_type	type;
	t_mtl_value	value;
}				t_material_value;

typedef	struct s_material
{
	char				*name;
	size_t				len;
	size_t				capacity;
	t_material_value	*inner;
	
}				t_material;

typedef struct	s_mtl
{
	size_t		len;
	size_t		capacity;
	t_material	*inner;
}				t_mtl;

int16_t			reader_peek(t_reader *self);
void			reader_next(t_reader *self);

bool			reader_cmp(t_reader *r, char *str);
void			*ft_memcpy(void *dst, const void *src, size_t n);

void			skip_ws(t_reader *r, bool newline);

t_reader		create_reader(int fd, char *buffer, size_t buffer_size);
t_mtl			create_mtl(size_t capacity);
t_material		create_material(size_t capacity);

bool			append_material(t_mtl *mtl, t_material material);
bool			append_material_value(t_material *material, t_material_value value);

t_mtl_error		read_mtl(t_reader *r, t_mtl *mtl);
t_mtl_error		read_digit(t_reader *r, double *digit);
t_mtl_error		read_str(t_reader *r, char **str);
t_mtl_error		read_material(t_reader *r, t_material *material);
t_mtl_error		read_k(t_reader *r, t_material_value *value);
t_mtl_error		read_map(t_reader *r, t_material_value *value);
t_mtl_error		read_d(t_reader *r, t_material_value *value);

#endif