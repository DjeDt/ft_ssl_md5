/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_md5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 15:30:44 by ddinaut           #+#    #+#             */
/*   Updated: 2018/12/09 22:06:56 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static const char padding[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void    init_mdb(t_mdbuffer *mdb)
{
	/* word A: 01 23 45 67 */
	mdb->a = 0x67452301;

	/* word B : 89 ab cd ef */
	mdb->b = 0xefcdab89;

	/* word C : fe dc ba 98 */
	mdb->c = 0x98badcfe;

	/* word D : 76 54 32 10 */
	mdb->d = 0x10325476;
}

uint32_t	auxiliary_func_F(uint32_t x, uint32_t y, uint32_t z)
{
	return (((x) & (y)) | ((~x) & (z)));
}

uint32_t	auxiliary_func_G(uint32_t x, uint32_t y, uint32_t z)
{
	return (((x) & (z)) | ((y) & (~z)));
}

uint32_t	auxiliary_func_H(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x) ^ (y) ^ (z));
}

uint32_t	auxiliary_func_I(uint32_t x, uint32_t y, uint32_t z)
{
	return ((y) ^ ((x) | (~z)));
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
void	proccess_message(uint8_t *strpad, size_t pad, t_mdbuffer *mdb)
{
	size_t	count;
	size_t	count2;
	size_t	limit;

	count = 0;
	limit = 0;
	while (count < pad)
	{
		count2 = 0;
		while (count2 < 16)
		{
			count2++;
		}
		count += (512 / 8);
	}
	(void)strpad;
	(void)mdb;
}

void	algo_md5(char *src, size_t len)
{
	char		*strpad;
	size_t		lenpad;
	t_mdbuffer	mdb;

	/* step 1 & 2 */
	lenpad = len_padded(len);
	strpad = pad_input(src, len, lenpad);
//	print_string((char*)strpad, 64);
	/* step 3 */
	init_mdb(&mdb);

	/* step 4 */
//	lets_roll(strpad, mdb);
}
