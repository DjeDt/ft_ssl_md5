/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_md5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 21:03:32 by ddinaut           #+#    #+#             */
/*   Updated: 2018/12/08 22:38:24 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

int		md5_from_string(char *str, int flag)
{
	if (!str)
	{
		ft_printf("error: -s option require an argument.\n");
		return (-1);
	}
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
