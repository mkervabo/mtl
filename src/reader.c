/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:13:11 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/15 12:29:59 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mtl.h"
#include <unistd.h>

t_mtl_reader	create_reader(int fd, char *buffer, size_t buffer_size)
{
	return ((t_mtl_reader){
		.fd = fd,
		.buffer = buffer,
		.buffer_size = buffer_size,
		.len = 0,
		.i = 0,
		.column = 0,
		.line = 1
	});
}

int16_t		reader_peek(t_mtl_reader *self)
{
	size_t	len;

	if (self->i >= self->len)
	{
		len = read(self->fd, self->buffer, self->buffer_size);
		if (len <= 0)
			return (-1);
		self->i = 0;
		self->len = len;
	}
	return (self->buffer[self->i]);
}

void		reader_next(t_mtl_reader *self)
{
	if (reader_peek(self) == '\n')
	{
		self->line++;
		self->column = 0;
	}
	else
		self->column++;
	self->i++;
}
