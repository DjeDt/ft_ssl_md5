/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_md5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 15:30:44 by ddinaut           #+#    #+#             */
/*   Updated: 2018/12/17 15:38:33 by ddinaut          ###   ########.fr       */
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

void    init_mdb(t_mdbuffer *mdb)
{
	/* word A: 01 23 45 67 */
	mdb->context[0] = 0x67452301;
	/* word B : 89 ab cd ef */
	mdb->context[1] = 0xefcdab89;
	/* word C : fe dc ba 98 */
	mdb->context[2] = 0x98badcfe;
	/* word D : 76 54 32 10 */
	mdb->context[3] = 0x10325476;

	mdb->count[0] = 0;
	mdb->count[1] = 0;
}

/*
** https://fthb321.github.io/MD5-Hash/MD5OurVersion2.html
** According to step 1 from rfc 1321
*/
size_t	len_padded(size_t len)
{
	/*
	** how many bits we have ( +1 stand for the mandatory 1 bit padding)
	*/
	len = len * 8 + 1;
	while (len % 512 != 448)
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

char	*pad_input(char *src, size_t len, size_t lenpad)
{
	uint32_t	bits;
	char*		strpad;

	bits = len * 8;

	/*'+ 64' stand for padded string*/
	strpad = malloc(lenpad + 64);
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

/* step 4 */

void	cut_out_block(uint32_t *block, t_mdbuffer *mdb)
{
	size_t		count;
	t_mdbuffer	tmp;

	count = 0;
	ft_memcpy(&tmp, mdb, sizeof(*mdb));
	(void)block;

	(void)r;
	(void)k;
	while (count < 16)
	{
		/* round 1 */


		/* mise a jour des valeurs */
		/*
		  mdb->a += tmp->a;
		  mdb->b += tmp->b;
		  mdb->c += tmp->c;
		  mdb->d += tmp->d;
		 */
		count++;
	}
}

void	proccess_message(char *strpad, size_t pad, t_mdbuffer *mdb)
{
	size_t		count;
	uint32_t	*block;

	count = 0;
   	while (count < pad)
	{
		/* to get 32 bit word */
		block = (uint32_t*)&strpad[count];
		cut_out_block(block, mdb);
		/* to go to the next 512 bits block */
		count += 64;
	}
}

/*
test()
{
	if ((context->count[0] += ((UINT4)inputLen << 3)) < ((UINT4)inputLen << 3))
		context->count[1]++;
	context->count[1] += ((UINT4)inputLen >> 29);

	partLen = 64 - index;

 Transform as many times as possible.

	if (inputLen >= partLen)
	{
		MD5_memcpy			((POINTER)&context->buffer[index], (POINTER)input, partLen);
		MD5Transform (context->state, context->buffer);
		for (i = partLen; i + 63 < inputLen; i += 64)
			MD5Transform (context->state, &input[i]);
		index = 0;
	}
	else
	{
		i = 0;
	}
}
*/

void	encode(unsigned char* output, uint32_t *input, unsigned int len)
{
	int count;
	unsigned int count2;

	count = 0;
	count2 = 0;
	while (count2 < len)
	{
		output[count2] = (unsigned char)(input[count] & 0xff);
		output[count2 + 1] = (unsigned char)((input[count] >> 8) & 0xff);
		output[count2 + 2] = (unsigned char)((input[count] >> 16) & 0xff);
		output[count2 + 3] = (unsigned char)((input[count] >> 24) & 0xff);
		count++;
		count2 += 4;
	}
}

void	decode(uint32_t *output, unsigned char *input, unsigned int len)
{
	int count;
	unsigned int count2;

	count = 0;
	count2 = 0;
	while (count2 < len)
	{
		output[count] = (input[count2]) | (input[count2 + 1] << 8) | \
			(input[count2 + 2] << 16) | (input[count2 + 3] << 24);
		count++;
		count2 += 4;
	}
}

void	round_context(t_mdbuffer *mdb)
{
	uint32_t tmp[4];

	ft_memcpy(tmp, mdb, sizeof(tmp));
	mdb->context[0] = tmp[3];
	mdb->context[1] = tmp[0];
	mdb->context[2] = tmp[1];
	mdb->context[3] = tmp[2];
	ft_bzero(tmp, 4);
}

void	md5_transform(t_mdbuffer *mdb, unsigned char block[64])
{
	int			count;
	uint32_t	x[16];
	t_mdbuffer	tmp;

	count = 0;
	ft_memcpy(&tmp, mdb, sizeof(tmp));
	decode(x, block, 64);
	while (count < 16)
	{
		auxiliary_func_FF(tmp.context, x[count], r[count], k[count]);
		round_context(&tmp);
		count++;
	}
	while (count < 32)
	{
		auxiliary_func_GG(tmp.context, x[count], r[count], k[count]);
		round_context(&tmp);
		count++;
	}
	while (count < 48)
	{
		auxiliary_func_HH(tmp.context, x[count], r[count], k[count]);
		round_context(&tmp);
		count++;
	}
	while (count < 64)
	{
		auxiliary_func_II(tmp.context, x[count], r[count], k[count]);
		round_context(&tmp);
		count++;
	}

/*	auxiliary_func_FF (tmp.a, tmp.b, tmp.c, tmp.d, x[ 0], S11, 0xd76aa478);
	auxiliary_func_FF (tmp.d, tmp.a, tmp.b, tmp.c, x[ 1], S12, 0xe8c7b756);
	auxiliary_func_FF (tmp.c, tmp.d, tmp.a, tmp.b, x[ 2], S13, 0x242070db);
	auxiliary_func_FF (tmp.b, tmp.c, tmp.d, tmp.a, x[ 3], S14, 0xc1bdceee);
	auxiliary_func_FF (tmp.a, tmp.b, tmp.c, tmp.d, x[ 4], S11, 0xf57c0faf);
	auxiliary_func_FF (tmp.d, tmp.a, tmp.b, tmp.c, x[ 5], S12, 0x4787c62a);
	auxiliary_func_FF (tmp.c, tmp.d, tmp.a, tmp.b, x[ 6], S13, 0xa8304613);
	auxiliary_func_FF (tmp.b, tmp.c, tmp.d, tmp.a, x[ 7], S14, 0xfd469501);
	auxiliary_func_FF (tmp.a, tmp.b, tmp.c, tmp.d, x[ 8], S11, 0x698098d8);
	auxiliary_func_FF (tmp.d, tmp.a, tmp.b, tmp.c, x[ 9], S12, 0x8b44f7af);
	auxiliary_func_FF (tmp.c, tmp.d, tmp.a, tmp.b, x[10], S13, 0xffff5bb1);
	auxiliary_func_FF (tmp.b, tmp.c, tmp.d, tmp.a, x[11], S14, 0x895cd7be);
	auxiliary_func_FF (tmp.a, tmp.b, tmp.c, tmp.d, x[12], S11, 0x6b901122);
	auxiliary_func_FF (tmp.d, tmp.a, tmp.b, tmp.c, x[13], S12, 0xfd987193);
	auxiliary_func_FF (tmp.c, tmp.d, tmp.a, tmp.b, x[14], S13, 0xa679438e);
	auxiliary_func_FF (tmp.b, tmp.c, tmp.d, tmp.a, x[15], S14, 0x49b40821);

	auxiliary_func_GG (tmp.a, tmp.b, tmp.c, tmp.d, x[ 1], S21, 0xf61e2562);
	auxiliary_func_GG (tmp.d, tmp.a, tmp.b, tmp.c, x[ 6], S22, 0xc040b340);
	auxiliary_func_GG (tmp.c, tmp.d, tmp.a, tmp.b, x[11], S23, 0x265e5a51);
	auxiliary_func_GG (tmp.b, tmp.c, tmp.d, tmp.a, x[ 0], S24, 0xe9b6c7aa);
	auxiliary_func_GG (tmp.a, tmp.b, tmp.c, tmp.d, x[ 5], S21, 0xd62f105d);
	auxiliary_func_GG (tmp.d, tmp.a, tmp.b, tmp.c, x[10], S22,  0x2441453);
	auxiliary_func_GG (tmp.c, tmp.d, tmp.a, tmp.b, x[15], S23, 0xd8a1e681);
	auxiliary_func_GG (tmp.b, tmp.c, tmp.d, tmp.a, x[ 4], S24, 0xe7d3fbc8);
	auxiliary_func_GG (tmp.a, tmp.b, tmp.c, tmp.d, x[ 9], S21, 0x21e1cde6);
	auxiliary_func_GG (tmp.d, tmp.a, tmp.b, tmp.c, x[14], S22, 0xc33707d6);
	auxiliary_func_GG (tmp.c, tmp.d, tmp.a, tmp.b, x[ 3], S23, 0xf4d50d87);
	auxiliary_func_GG (tmp.b, tmp.c, tmp.d, tmp.a, x[ 8], S24, 0x455a14ed);
	auxiliary_func_GG (tmp.a, tmp.b, tmp.c, tmp.d, x[13], S21, 0xa9e3e905);
	auxiliary_func_GG (tmp.d, tmp.a, tmp.b, tmp.c, x[ 2], S22, 0xfcefa3f8);
	auxiliary_func_GG (tmp.c, tmp.d, tmp.a, tmp.b, x[ 7], S23, 0x676f02d9);
	auxiliary_func_GG (tmp.b, tmp.c, tmp.d, tmp.a, x[12], S24, 0x8d2a4c8a);

	auxiliary_func_HH (tmp.a, tmp.b, tmp.c, tmp.d, x[ 5], S31, 0xfffa3942);
	auxiliary_func_HH (tmp.d, tmp.a, tmp.b, tmp.c, x[ 8], S32, 0x8771f681);
	auxiliary_func_HH (tmp.c, tmp.d, tmp.a, tmp.b, x[11], S33, 0x6d9d6122);
	auxiliary_func_HH (tmp.b, tmp.c, tmp.d, tmp.a, x[14], S34, 0xfde5380c);
	auxiliary_func_HH (tmp.a, tmp.b, tmp.c, tmp.d, x[ 1], S31, 0xa4beea44);
	auxiliary_func_HH (tmp.d, tmp.a, tmp.b, tmp.c, x[ 4], S32, 0x4bdecfa9);
	auxiliary_func_HH (tmp.c, tmp.d, tmp.a, tmp.b, x[ 7], S33, 0xf6bb4b60);
	auxiliary_func_HH (tmp.b, tmp.c, tmp.d, tmp.a, x[10], S34, 0xbebfbc70);
	auxiliary_func_HH (tmp.a, tmp.b, tmp.c, tmp.d, x[13], S31, 0x289b7ec6);
	auxiliary_func_HH (tmp.d, tmp.a, tmp.b, tmp.c, x[ 0], S32, 0xeaa127fa);
	auxiliary_func_HH (tmp.c, tmp.d, tmp.a, tmp.b, x[ 3], S33, 0xd4ef3085);
	auxiliary_func_HH (tmp.b, tmp.c, tmp.d, tmp.a, x[ 6], S34,  0x4881d05);
	auxiliary_func_HH (tmp.a, tmp.b, tmp.c, tmp.d, x[ 9], S31, 0xd9d4d039);
	auxiliary_func_HH (tmp.d, tmp.a, tmp.b, tmp.c, x[12], S32, 0xe6db99e5);
	auxiliary_func_HH (tmp.c, tmp.d, tmp.a, tmp.b, x[15], S33, 0x1fa27cf8);
	auxiliary_func_HH (tmp.b, tmp.c, tmp.d, tmp.a, x[ 2], S34, 0xc4ac5665);

	auxiliary_func_II (tmp.a, tmp.b, tmp.c, tmp.d, x[ 0], S41, 0xf4292244);
	auxiliary_func_II (tmp.d, tmp.a, tmp.b, tmp.c, x[ 7], S42, 0x432aff97);
	auxiliary_func_II (tmp.c, tmp.d, tmp.a, tmp.b, x[14], S43, 0xab9423a7);
	auxiliary_func_II (tmp.b, tmp.c, tmp.d, tmp.a, x[ 5], S44, 0xfc93a039);
	auxiliary_func_II (tmp.a, tmp.b, tmp.c, tmp.d, x[12], S41, 0x655b59c3);
	auxiliary_func_II (tmp.d, tmp.a, tmp.b, tmp.c, x[ 3], S42, 0x8f0ccc92);
	auxiliary_func_II (tmp.c, tmp.d, tmp.a, tmp.b, x[10], S43, 0xffeff47d);
	auxiliary_func_II (tmp.b, tmp.c, tmp.d, tmp.a, x[ 1], S44, 0x85845dd1);
	auxiliary_func_II (tmp.a, tmp.b, tmp.c, tmp.d, x[ 8], S41, 0x6fa87e4f);
	auxiliary_func_II (tmp.d, tmp.a, tmp.b, tmp.c, x[15], S42, 0xfe2ce6e0);
	auxiliary_func_II (tmp.c, tmp.d, tmp.a, tmp.b, x[ 6], S43, 0xa3014314);
	auxiliary_func_II (tmp.b, tmp.c, tmp.d, tmp.a, x[13], S44, 0x4e0811a1);
	auxiliary_func_II (tmp.a, tmp.b, tmp.c, tmp.d, x[ 4], S41, 0xf7537e82);
	auxiliary_func_II (tmp.d, tmp.a, tmp.b, tmp.c, x[11], S42, 0xbd3af235);
	auxiliary_func_II (tmp.c, tmp.d, tmp.a, tmp.b, x[ 2], S43, 0x2ad7d2bb);
	auxiliary_func_II (tmp.b, tmp.c, tmp.d, tmp.a, x[ 9], S44, 0xeb86d391); */

	mdb->context[0] += tmp.context[0];
	mdb->context[1] += tmp.context[1];
	mdb->context[2] += tmp.context[2];
	mdb->context[3] += tmp.context[3];
	ft_bzero(x, 16);
}

void	md5_update(t_mdbuffer *mdb, char *input, size_t size)
{
	unsigned int count;
	unsigned int offset;
	unsigned int partlen;

	/* Compute number of bytes mod 64 */
	offset = (unsigned int)((mdb->count[0] >> 3) & 0x3F);

	/* Update number of bits */
	if ((mdb->count[0] += ((unsigned int)size << 3)) < ((unsigned int)size << 3))
		mdb->count[1]++;
	mdb->count[1] += ((unsigned int)size >> 29);
	partlen = 64 - offset;

	if (size >= partlen)
	{
		ft_memcpy(&mdb->buffer[offset], input, partlen);
		md5_transform(mdb, mdb->buffer);

		count = partlen;
		while (count + 63 < size)
		{
			md5_transform(mdb, (unsigned char*)&input[count]);
			count += 64;
		}
		offset = 0;
	}
	else
		count = 0;
	ft_memcpy(&mdb->buffer[offset], (unsigned char*)&input[count], size - offset);

}

/*
void MD5Final (digest, context)
	unsigned char digest[16];
	MD5_CTX *context;
{
  unsigned char bits[8];
  unsigned int index, padLen;

  Encode (bits, context->count, 8);

  index = (unsigned int)((context->count[0] >> 3) & 0x3f);
  padLen = (index < 56) ? (56 - index) : (120 - index);
  MD5Update (context, PADDING, padLen);

  MD5Update (context, bits, 8);
  Encode (digest, context->state, 16);

  MD5_memset ((POINTER)context, 0, sizeof (*context));
}
*/

void	md5_final(t_mdbuffer *mdb, char *input)
{
	unsigned char	final[16];
	unsigned char	bits[8];
	unsigned int	count; // index
	unsigned int	padlen;

	encode(bits, mdb->count, 8);
	count = (unsigned int)((mdb->count[0] >> 3) & 0x3f);
	//padlen = (index < 56) ? ()
	if (count < 56)
		padlen = 56 - count;
	else
		padlen = 120 - count;
	md5_update(mdb, input, padlen);
	md5_update(mdb, (char*)bits, 8);
	encode(final, mdb->count, 16);
	ft_printf("%s\n", final);
	ft_memset(mdb, 0, sizeof(*mdb));
}

void	algo_md5(char *input, size_t size)
{
	t_mdbuffer	mdb;

	init_mdb(&mdb);
	md5_update(&mdb, input, size);
	md5_final(&mdb, input);
}
