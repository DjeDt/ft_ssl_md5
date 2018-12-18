/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_func_md5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 12:01:11 by ddinaut           #+#    #+#             */
/*   Updated: 2018/12/18 20:37:33 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

uint32_t rotate_left(uint32_t a, uint32_t b)
{
	return ((a << b) | (a >> (32 - b)));
}

uint32_t	f1(uint32_t x, uint32_t y, uint32_t z)
{
//	return (z ^ (x & ( y ^ z)));
	return (((x) & (y)) | ((~x) & (z)));
}

uint32_t	f2(uint32_t x, uint32_t y, uint32_t z)
{

//	return (f1(z, x, y));
	return (((x) & (z)) | ((y) & (~z)));
}

uint32_t	f3(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x) ^ (y) ^ (z));
}

uint32_t	f4(uint32_t x, uint32_t y, uint32_t z)
{
//	return ( y ^ ( x | ~z ) );
	return ((y) ^ ((x) | (~z)));
}


#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits.
 */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation.
 */
#define FF(a, b, c, d, x, s, ac) { \
 (a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
	}

#define GG(a, b, c, d, x, s, ac) { \
 (a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
	}

#define HH(a, b, c, d, x, s, ac) { \
 (a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

#define II(a, b, c, d, x, s, ac) { \
 (a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
