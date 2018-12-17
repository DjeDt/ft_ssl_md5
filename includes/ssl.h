/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 15:39:26 by ddinaut           #+#    #+#             */
/*   Updated: 2018/12/17 13:20:45 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include "libft.h"
# include "printf.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>

# define TRUE 0
# define FALSE 1

# define FLAG_P (1 << 0)
# define FLAG_Q (1 << 1)
# define FLAG_R (1 << 2)
# define FLAG_S (1 << 3)

typedef struct			s_mdbuffer
{
	unsigned int		count[2];
	uint32_t			context[4];
	unsigned char		buffer[64];
}						t_mdbuffer;

# define S11 7
# define S12 12
# define S13 17
# define S14 22
# define S21 5
# define S22 9
# define S23 14
# define S24 20
# define S31 4
# define S32 11
# define S33 16
# define S34 23
# define S41 6
# define S42 10
# define S43 15
# define S44 21


int						ft_ssl(int ac, char **av);
int						manage_input(char **argv, int ac);

/* md5 */
int						manage_md5(char **argv, int *count, int ac);
int						md5_from_string(char *str, int flag);
int						md5_from_file(char *str, int flag);
int						md5_from_standard_input(int flag);
void					algo_md5(char *input, size_t size);

uint32_t auxiliary_func_F(uint32_t x, uint32_t y, uint32_t z);
uint32_t auxiliary_func_G(uint32_t x, uint32_t y, uint32_t z);
uint32_t auxiliary_func_H(uint32_t x, uint32_t y, uint32_t z);
uint32_t auxiliary_func_I(uint32_t x, uint32_t y, uint32_t z);
/* uint32_t auxiliary_func_FF(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t m, uint32_t s, uint32_t t); */
/* uint32_t auxiliary_func_GG(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t m, uint32_t s, uint32_t t); */
/* uint32_t auxiliary_func_HH(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t m, uint32_t s, uint32_t t); */
/* uint32_t auxiliary_func_II(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t m, uint32_t s, uint32_t t); */
uint32_t auxiliary_func_FF(uint32_t *context, uint32_t m, uint32_t s, uint32_t t);
uint32_t auxiliary_func_GG(uint32_t *context, uint32_t m, uint32_t s, uint32_t t);
uint32_t auxiliary_func_HH(uint32_t *context, uint32_t m, uint32_t s, uint32_t t);
uint32_t auxiliary_func_II(uint32_t *context, uint32_t m, uint32_t s, uint32_t t);

/* sha512 */
int						secure_hash_algo_512(void);

#endif
