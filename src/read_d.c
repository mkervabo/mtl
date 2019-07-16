/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:28:50 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/16 11:38:59 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mtl.h"

t_mtl_error		read_d(t_reader *r, t_material_value *value)
{
	t_mtl_error	err;

	value->type = Mtl_D;
	reader_next(r);
	skip_ws(r, false);
	if ((err = read_digit(r, &value->value.d)) != No_Error)
	{
		return (err);
	}
	if (value->value.d < 0 || value->value.d > 1)
		return (Invalid_D_Value);
	return (No_Error);
}