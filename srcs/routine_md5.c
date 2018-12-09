/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_md5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 21:03:32 by ddinaut           #+#    #+#             */
/*   Updated: 2018/12/09 19:03:10 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

int		md5_from_string(char *str, int flag)
{
	size_t		len;

	if (!str)
	{
		ft_printf("error: -s option require an argument.\n");
		return (-1);
	}
	len = ft_strlen(str);
	algo_md5(str, len);
	ft_printf("md5 from string [%s]\n", str);
	(void)flag;
	return (0);
}

int		md5_from_file(char *str, int flag)
{
	ft_printf("md5 from file [%s]\n", str);
	(void)flag;
	return (0);
}

int		md5_from_standard_input(int flag)
{
	ft_printf("md5_from_standard_input\n");
	(void)flag;
	return (0);
}
