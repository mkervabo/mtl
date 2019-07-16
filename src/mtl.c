/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 12:26:58 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/16 13:04:30 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mtl.h"
#include <stdlib.h>

void			skip_ws(t_reader *r, bool newline)
{
	int16_t	c;

	while ((c = reader_peek(r)) != -1 && (c == ' ' || c == '\t' || c == '#'
				|| (newline && c == '\n')))
	{
		if (c == '#')
		{
			while ((c = reader_peek(r)) != -1 && c != '\n')
				reader_next(r);
		}
		reader_next(r);
	}
}

bool			reader_cmp(t_reader *r, char *str)
{
	char c;
	size_t i;

	i = 0;
	while ((c = reader_peek(r)) != -1 && str[i] != '\0' && c == str[i])
	{
		reader_next(r);
		i++;
	}
	if (str[i] != '\0')
		return (false);
	return true;
}

static bool 	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (s1[i] == s2[i])
		return (false);
	return (true);
}

static bool		new_name(t_mtl	*mtl, t_material *material)
{
	size_t	i;

	i = 0;
	while (i < mtl->len)
	{
		if (ft_strcmp(mtl->inner[i].name, material->name) == false)
			return (false);
		i++;
	}
	return (true);
}

t_mtl_error		read_mtl(t_reader *r, t_mtl *mtl)
{
	t_mtl_error	err;
	t_material	material;
	char		c;

	skip_ws(r, true);
	*mtl = create_mtl(10);
	while ((c = reader_peek(r))!= -1 && c == 'n')
	{
		reader_next(r);
		if (reader_cmp(r, "ewmtl") == false)
			return (Wrong_Newmtl);
		skip_ws(r, false);
		if ((err = read_material(r, &material)) != No_Error)
			return (err);
		if (new_name(mtl, &material) == false)
			return (Name_Already_Exists);	
		if (append_material(mtl, material) == false)
			return (Error_Malloc);
	}
	return (No_Error);
}