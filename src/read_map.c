/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:18:28 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/15 15:28:05 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mtl.h"


static t_mtl_error		read_map_ka_kd(t_reader *r, t_material_value *value, bool ka)
{
	char		c;
	t_mtl_error	err;

	if (ka == true)
		value->type = Mtl_Map_Ka;
	else
		value->type = Mtl_Map_Kd;
	if ((err = read_str(r, &value->value.map)) != No_Error)
		return (Invalid_Map_Value);
	return (No_Error);
}

t_mtl_error		read_map(t_reader *r, t_material_value *value)
{
	t_mtl_error	err;
	char		c;

	reader_next(r);
	if (reader_cmp(r, "ap_K") == false)
		return (No_Valid_Map_Value);
	if ((c = reader_peek(r)) == 'a')
	{
		if ((err = read_map_ka_kd(r, value, true)) != No_Error)
			return (err);
	}
	else if (c == 'd')
	{
		if ((err = read_map_ka_kd(r, value, false)) != No_Error)
			return (err);
	}
	else
		return (No_Valid_Map_Value);
	return (No_Error);
}