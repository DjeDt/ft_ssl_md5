/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_md5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 15:30:44 by ddinaut           #+#    #+#             */
/*   Updated: 2018/12/18 20:01:56 by ddinaut          ###   ########.fr       */
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

size_t	len_padded(size_t len)
{
	/*
	** how many bits we have ( +1 stand for the mandatory 1 bit padding)
	*/
	len = (len * 8);
	while ((len % 512) != 448)
		len++;
	/* revert to actual str len */
	len /= 8;
	return (len);
}

const char *byte_to_binary(int x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
		strcat(b, ((x & z) == z) ? "1" : "0");
	return b;
}

void	print_string(char *ret, size_t len)
{
	size_t i = 0;
	while (i < len)
	{
		char c;
		if ((i + 1) % 8 == 0)
			c = '\n';
		else
			c = ' ';
		printf("%s%c", byte_to_binary(ret[i]), c);
		i++;
	}

}

uint8_t	*pad_input(char *src, size_t len, size_t lenpad)
{
	uint32_t	bits;
	uint8_t		*strpad;

	bits = len * 8;
	bits = len_padded(bits);
	strpad = (uint8_t*)malloc(bits);

	/*'+ 64' stand for padded string*/
	printf("lenpad  = %lu\n", lenpad);
	exit(1);
	strpad = (uint8_t*)malloc(lenpad);
	if (!strpad)
		return (NULL);
	ft_bzero(strpad, lenpad + 64);


	/* step 1 : to add padded  string */
	ft_memcpy(strpad, src, len);
	ft_memcpy(strpad + len, padding, lenpad - len);


	/* step 2 to add orinal input len */
	ft_memcpy(strpad + lenpad, &bits, 4);
	return (strpad);
}

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
	mdb->offset[0] = 0;
	mdb->offset[1] = 0;
	mdb->size = size;
}

void	transform_md5(uint32_t *context, uint32_t *buffer)
{
	int			count;
	uint32_t	cpy[4];

	count = 0;
	ft_memcpy(cpy, context, sizeof(uint32_t) * 4);
	while (count < 64)
	{
		if (count < 16)
			master_func(f1, cpy, buffer[count] + k[count], r[count]);
		else if (count < 32)
			master_func(f2, cpy, buffer[count] + k[count], r[count]);
		else if (count < 48)
			master_func(f3, cpy, buffer[count] + k[count], r[count]);
		else if (count < 64)
			master_func(f4, cpy, buffer[count] + k[count], r[count]);
		round_context(cpy);
		count++;
	}
	context[0] += cpy[0];
	context[1] += cpy[1];
	context[2] += cpy[2];
	context[3] += cpy[3];
}

void	update_md5(t_mdbuffer *mdb, uint8_t *input, size_t size)
{
	/*
	uint32_t	nb;
	uint8_t		*tmp;

	nb = mdb->offset[0];
	mdb->offset[0] = nb + (size << 3);
	if (mdb->offset[0] < nb)
		mdb->offset[1]++;
	mdb->context[1] += size >> 29;
	nb = (nb >> 3) & 0x3f;
	if (nb)
	{
		tmp = mdb->buffer + nb;
		nb = 64 - nb;
		if (size < nb)
		{
			ft_memcpy(tmp, input, nb);
			return ;
		}
		ft_memcpy(tmp, input, size);
		transform_md5(mdb->context, (uint32_t*)mdb->buffer);
		input += nb;
		size -= nb;
	}
	while (size > 64)
	{
		ft_memcpy(mdb->buffer, input, 64);
		transform_md5(mdb->context, (uint32_t*)mdb->buffer);
		input += 64;
		size -= 64;
	}
	*/
	size_t size2 = size;
	while (size > 64)
	{
		ft_memcpy(mdb->buffer, input, 64);
		transform_md5(mdb->context, (uint32_t*)mdb->buffer);
		input += 64;
		size -= 64;
	}
	ft_memcpy(mdb->buffer, input, size);
	ft_memcpy(mdb->buffer + size, padding, 64 - size);
	ft_memcpy(mdb->buffer + 56, &size2, 8);
	transform_md5(mdb->context, (uint32_t*)mdb->buffer);

    uint8_t *p;
	p=(uint8_t *)&mdb->context[0];
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    p=(uint8_t *)&mdb->context[1];
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    p=(uint8_t *)&mdb->context[2];
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    p=(uint8_t *)&mdb->context[3];
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);

}

void	final_md5(t_mdbuffer *mdb, char *final)
{
	uint32_t	nb;
	uint8_t		*tmp;

	nb = (mdb->offset[0] >> 3) & 0x3f;
	tmp = mdb->buffer + nb;
	*tmp++ = 0x80;
	nb = 64 - 1 - nb;
	if (nb)
	{
		ft_memset(tmp, 0, nb);
		transform_md5(mdb->context, (uint32_t*)mdb->buffer);
		ft_memset(mdb->buffer, 0, 56);
	}
	else
		ft_memset(tmp, 0, nb - 8);
	mdb->buffer[14] = mdb->offset[0];
	mdb->buffer[15] = mdb->offset[1];
	transform_md5(mdb->context, (uint32_t*)mdb->buffer);
	ft_memcpy(final, mdb->context, 16);
}

void	algo_md5(char *input, size_t size)
{
	t_mdbuffer		mdb;
	char			final[64];

	init_md5(&mdb, size);
	update_md5(&mdb, (uint8_t*)input, size);
	(void)final;
//	final_md5(&mdb, final);


//	printf("%s\n", final);
}
