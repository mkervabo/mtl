/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_digit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:44:56 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/15 15:00:17 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mtl.h"

static double	read_integer(t_reader *r, bool *s)
{
	double	num;
	int16_t	c;

	*s = false;
	num = 0;
	c = reader_peek(r);
	if (c == '-')
		*s = true;
	if (c == '-' || c == '+')
		reader_next(r);
	while ((c = reader_peek(r)) != -1 && ((c >= '0' && c <= '9') || c == '_'))
	{
		if (c >= '0' && c <= '9')
			num = num * 10 + (c - 48);
		reader_next(r);
	}
	return (num);
}

static double	read_float(t_reader *r)
{
	double	num;
	size_t	i;
	int16_t c;

	i = 0;
	num = 0;
	while ((c = reader_peek(r)) != -1 && ((c >= '0' && c <= '9') || c == '_'))
	{
		if (c >= '0' && c <= '9')
		{
			num = num * 10 + (c - 48);
			i++;
		}
		reader_next(r);
	}
	while (i-- > 0)
		num *= 0.1;
	return (num);
}

t_mtl_error		read_digit(t_reader *r, double *digit)
{
	bool	sign;
	int16_t	c;

	c = reader_peek(r);
	if ((c < '0' || c > '9') && c != '-' && c != '+')
		return (Invalid_Digit);
	*digit = read_integer(r, &sign);
	if (reader_peek(r) != '.')
		return (Invalid_Digit_Dot);
	reader_next(r);
	c = reader_peek(r);
	if ((c < '0' || c > '9') && c != '-' && c != '+')
		return (Invalid_Digit);
	*digit = (sign ? -1 : 1) * (*digit + read_float(r));
	return (No_Error);
}