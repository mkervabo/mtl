/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:46:34 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/16 10:59:49 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mtl.h"
#include <stdlib.h>

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*c_src = src;
	char		*c_dst;

	c_dst = dst;
	while (n--)
		*c_dst++ = *c_src++;
	return (dst);
}

static bool			append_char(char **str, char c, size_t *size , size_t i)
{
	size_t	new_size;
	char 	*new;

	if (i == *size)
	{
		new_size = *size * 2;
		if (!(new = malloc(new_size * sizeof(char))))
			return (false);
		ft_memcpy(new, *str, *size);
		free(*str);
		*str = new;
		*size = new_size;
	}
	(*str)[i] = c;
	return (true);
}

t_mtl_error		read_str(t_reader *r, char **str)
{
	int16_t c;
	size_t size;
	size_t i;

	size = 10;
	if (!(*str = (char*)malloc(sizeof(char) * size)))
		return (Error_Malloc);
	i = 0;
	while ((c = reader_peek(r)) != -1 && c != '\n' && c != ' ' && c != '\t')
	{
		if (append_char(str, c, &size, i) == false)
			return (Error_Malloc);
		i++;
		reader_next(r);
	}
	if (append_char(str, '\0', &size, i) == false)
			return (Error_Malloc);
	return (No_Error);
}

t_mtl_error		read_material(t_reader *r, t_material *material)
{
	t_mtl_error			err;
	t_material_value	value;
	char				c;
	char				*name;

	if((err = read_str(r, &name)) != No_Error)
		return (err);
	*material = create_material(10);
	skip_ws(r, true);
	while((c = reader_peek(r)) != -1 && c != 'n')
	{
		if (c == 'K')
		{
			if((err = read_k(r, &value)) != No_Error)
				return (err);
		}
		else if (c == 'm')
		{
			if((err = read_map(r, &value)) != No_Error)
				return (err);
		}
		else if (c == 'd')
		{
			if((err = read_d(r, &value)) != No_Error)
				return (err);
		}
		else
			return (No_Valid_Value);
		if (append_material_value(material, value) == false)
			return (Error_Malloc);
		skip_ws(r, true);
	}
	return (No_Error);
}