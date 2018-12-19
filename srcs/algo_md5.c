/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_md5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 15:30:44 by ddinaut           #+#    #+#             */
/*   Updated: 2018/12/19 15:33:57 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static const char padding[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*
** constante des sinus d'entiers
*/
static const uint32_t r[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

/*
** Use binary integer part of the sines of integers (in radians) as constants// Initialize variables:
*/
static const uint32_t k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

void	round_context(uint32_t *val)
{
	uint32_t tmp;

	tmp = val[3];
	val[3] = val[2];
	val[2] = val[1];
	val[1] = val[0];
	val[0] = tmp;
}

void	master_func(uint32_t func(uint32_t x, uint32_t y, uint32_t z), uint32_t *context, uint32_t data, uint32_t s)
{
	context[0] += func(context[1], context[2], context[3]) + data;
	context[0] = context[0] << s | context[0] >> (32 - s);
	context[0] += context[1];
}

void    init_md5(t_mdbuffer *mdb, size_t size)
{
	mdb->context[0] = 0x67452301;
	mdb->context[1] = 0xefcdab89;
	mdb->context[2] = 0x98badcfe;
	mdb->context[3] = 0x10325476;
	mdb->size = size;
	ft_bzero(mdb->buffer, 64);
}

void	transform_md5(uint32_t *context, uint8_t *buffer)
{
	int			count;
	uint32_t	cpy[4];

	count = 0;
	ft_memcpy(cpy, context, sizeof(uint32_t) * 4);
	while (count < 64)
	{

/*
		if (count < 16)
			master_func(f1, cpy, swap_uint32(buffer[count]) + k[count], r[count]);
		else if (count < 32)
			master_func(f2, cpy, swap_uint32(buffer[count]) + k[count], r[count]);
		else if (count < 48)
			master_func(f3, cpy, swap_uint32(buffer[count]) + k[count], r[count]);
		else
			master_func(f4, cpy, swap_uint32(buffer[count]) + k[count], r[count]);
*/
		if (count < 16)
			master_func(f1, cpy, buffer[count] + k[count], r[count]);
		else if (count < 32)
			master_func(f2, cpy, buffer[count] + k[count], r[count]);
		else if (count < 48)
			master_func(f3, cpy, buffer[count] + k[count], r[count]);
		else
			master_func(f4, cpy, buffer[count] + k[count], r[count]);
		round_context(cpy);
		count++;
	}
	context[0] += cpy[0];
	context[1] += cpy[1];
	context[2] += cpy[2];
	context[3] += cpy[3];
}

uint32_t		reverse(uint32_t i)
{
	uint32_t new;

	new = 0;
	new += i << 24 & 0xff000000;
	new += i << 8 & 0xff0000;
	new += i >> 8 & 0xff00;
	new += i >> 24 & 0xff;
	return (new);
}


void	update_md5(t_mdbuffer *mdb, uint8_t *input)
{
	uint64_t size;
	uint8_t	*tmp;

	size = mdb->size;
	while (size > 64)
	{
		ft_memcpy(mdb->buffer, input, 64);
		transform_md5(mdb->context, mdb->buffer);
		input += 64;
		size -= 64;
	}
//	if (size)
//	{
		ft_memcpy(mdb->buffer, input, size);
		tmp = mdb->buffer + size;
		ft_memcpy(tmp, padding, 64 - size);
		tmp = mdb->buffer + 56;
		ft_memcpy(tmp, &mdb->size, 8);
		transform_md5(mdb->context, mdb->buffer);
//	}

		mdb->context[0] = reverse(mdb->context[0]);
		mdb->context[1] = reverse(mdb->context[1]);
		mdb->context[2] = reverse(mdb->context[2]);
		mdb->context[3] = reverse(mdb->context[3]);
		ft_printf("%.8x%.8x%.8x%.8x\n", mdb->context[0], mdb->context[1], mdb->context[2], mdb->context[3]);

		/*
	uint8_t *p;
	p=(uint8_t *)&mdb->context[0];
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p=(uint8_t *)&mdb->context[1];
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p=(uint8_t *)&mdb->context[2];
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p=(uint8_t *)&mdb->context[3];
	printf("%2.2x%2.2x%2.2x%2.2x\n", p[0], p[1], p[2], p[3]);
		*/
}

int x=1;
#define TEST (*(char*)&(x)==1)?printf("little endian"):printf("Big endian")

void	algo_md5(char *input, uint64_t size)
{
	t_mdbuffer		mdb;

//	TEST;
	init_md5(&mdb, size);
	update_md5(&mdb, (uint8_t*)input);

    /* uint8_t *p; */
	/* p=(uint8_t *)&mdb.context[0]; */
    /* printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]); */
    /* p=(uint8_t *)&mdb.context[1]; */
    /* printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]); */
    /* p=(uint8_t *)&mdb.context[2]; */
    /* printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]); */
    /* p=(uint8_t *)&mdb.context[3]; */
	/* printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]); */
}
