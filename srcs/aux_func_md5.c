/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_func_md5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 12:01:11 by ddinaut           #+#    #+#             */
/*   Updated: 2018/12/17 15:58:22 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

uint32_t auxiliary_func_F(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) | (~x & z));
}

uint32_t auxiliary_func_G(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & z) | (y & ~z));
}

uint32_t auxiliary_func_H(uint32_t x, uint32_t y, uint32_t z)
{
	return (x ^ y ^ z);
}

uint32_t auxiliary_func_I(uint32_t x, uint32_t y, uint32_t z)
{
	return (y ^ (x | ~z));
}

uint32_t rotate_left(uint32_t a, uint32_t b)
{
	return ((a << b) | (a >> (32 - b)));
}

//uint32_t auxiliary_func_FF(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t m, uint32_t s, uint32_t t)
uint32_t auxiliary_func_FF(uint32_t *context, uint32_t m, uint32_t s, uint32_t t)
{
	context[0] += auxiliary_func_F(context[1], context[2], context[3]) + m + t;
	context[0] = context[1] + rotate_left(context[0], s);
//	a += auxiliary_func_F(b, c, d) + m + t;
//	a = b + rotate_left(a, s);
	return (context[0]);
}

//uint32_t auxiliary_func_GG(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t m, uint32_t s, uint32_t t)
uint32_t auxiliary_func_GG(uint32_t *context, uint32_t m, uint32_t s, uint32_t t)
{
	context[0] += auxiliary_func_G(context[1], context[2], context[3]) + m + t;
	context[0] = context[1] + rotate_left(context[0], s);
//	a += auxiliary_func_G(b, c, d) + m + t;
//	a = b + rotate_left(a, s);
	return (context[0]);
}

//uint32_t auxiliary_func_HH(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t m, uint32_t s, uint32_t t)
uint32_t auxiliary_func_HH(uint32_t *context, uint32_t m, uint32_t s, uint32_t t)
{
	context[0] += auxiliary_func_H(context[1], context[2], context[3]) + m + t;
	context[0] = context[1] + rotate_left(context[0], s);
//	a += auxiliary_func_H(b, c, d) + m + t;
//	a = b + rotate_left(a, s);
	return (context[0]);
}

//uint32_t auxiliary_func_II(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t m, uint32_t s, uint32_t t)
uint32_t auxiliary_func_II(uint32_t *context, uint32_t m, uint32_t s, uint32_t t)
{
	context[0] += auxiliary_func_I(context[1], context[2], context[3]) + m + t;
	context[0] = context[1] + rotate_left(context[0], s);

	/* a += auxiliary_func_I(b, c, d) + m + t; */
	/* a = b + rotate_left(a, s); */
	return (context[0]);
}

/*
MD5STEP(f, w, x, y, z, data, s) \
	( w += f(x, y, z) + data,  w = w<<s | w>>(32-s),  w += x )
*/

void uint32_t	ultimate_func(uint32_t *func, uint32_t *context, uint32_t data, uint32_t s)
{
	context[0] += func(context[1], context[2], context[3]) + data;
	context[0] = context[0] << s | w >> (32 - s);
	context[0] += context[1];
}
