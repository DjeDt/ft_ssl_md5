/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 15:39:26 by ddinaut           #+#    #+#             */
/*   Updated: 2018/12/08 22:24:28 by ddinaut          ###   ########.fr       */
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

int			ft_ssl(int ac, char **av);
int			manage_input(char **argv, int ac);

/* md5 */
int			manage_md5(char **argv, int *count, int ac);
int			md5_from_string(char *str, int flag);
int			md5_from_file(char *str, int flag);
int			md5_from_standard_input(int flag);

/* */
int			secure_hash_algo_512(void);

#endif
