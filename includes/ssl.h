/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 15:39:26 by ddinaut           #+#    #+#             */
/*   Updated: 2018/12/18 19:16:49 by ddinaut          ###   ########.fr       */
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

typedef struct		s_mdbuffer
{
	size_t			size;
	unsigned int	offset[2];
	uint32_t		context[4];
	uint8_t			buffer[64];
}					t_mdbuffer;

int					ft_ssl(int ac, char **av);
int					manage_input(char **argv, int ac);

/* md5 */
int					manage_md5(char **argv, int *count, int ac);
int					md5_from_string(char *str, int flag);
int					md5_from_file(char *str, int flag);
int					md5_from_standard_input(int flag);
void				algo_md5(char *input, size_t size);

uint32_t			f1(uint32_t x, uint32_t y, uint32_t z);
uint32_t			f2(uint32_t x, uint32_t y, uint32_t z);
uint32_t			f3(uint32_t x, uint32_t y, uint32_t z);
uint32_t			f4(uint32_t x, uint32_t y, uint32_t z);

/* sha512 */
int					secure_hash_algo_512(void);

/* swap */
uint64_t			swap_64(uint64_t n);

#endif
