/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_k.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:18:08 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/15 16:36:44 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mtl.h"

static t_mtl_error		read_ka_kd(t_reader *r, t_material_value *value, bool ka)
{
	t_mtl_error	err;

	if (ka == true)
		value->type = Mtl_Ka;
	else
		value->type = Mtl_Kd;
	reader_next(r);
	skip_ws(r, false);
	if ((err = read_digit(r, &value->value.color.a)) != No_Error)
		return (err);
	skip_ws(r, false);
	if ((err = read_digit(r, &value->value.color.b)) != No_Error)
		return (err);
	skip_ws(r, false);
	if ((err = read_digit(r, &value->value.color.c)) != No_Error)
		return (err);
	return (No_Error);
}

t_mtl_error				read_k(t_reader *r, t_material_value *value)
{
	t_mtl_error	err;
	char		c;

	reader_next(r);
	if ((c = reader_peek(r)) == 'a')
	{
		if ((err = read_ka_kd(r, value, true)) != No_Error)
			return (err);
	}
	else if (c == 'd')
	{
		if ((err = read_ka_kd(r, value, false)) != No_Error)
			return (err);
	}
	else
		return (No_Valid_K_Value);
	return (No_Error);
}