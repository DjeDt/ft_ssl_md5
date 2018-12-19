/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_func_md5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 12:01:11 by ddinaut           #+#    #+#             */
/*   Updated: 2018/12/19 15:13:48 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

uint32_t rotate_left(uint32_t a, uint32_t b)
{
	return ((a << b) | (a >> (32 - b)));
}

uint32_t	f1(uint32_t x, uint32_t y, uint32_t z)
{
	return ((z) ^ ((x) & ((y) ^ (z))));
}

uint32_t	f2(uint32_t x, uint32_t y, uint32_t z)
{
	return ((y) ^ ((z) & ((x) ^ (y))));
}

uint32_t	f3(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x) ^ (y) ^ (z));
}

uint32_t	f4(uint32_t x, uint32_t y, uint32_t z)
{
	return ( y ^ ( x | ~z ) );
}
