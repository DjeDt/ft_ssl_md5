/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_md5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 21:52:50 by ddinaut           #+#    #+#             */
/*   Updated: 2018/12/08 22:44:35 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

int		wrong_option(char *prog, char opt)
{
	ft_printf_fd(STDERR_FILENO, "%s: illegal option -- %c\n", prog, opt);
	ft_printf_fd(STDERR_FILENO, "usage: %s [-pqrt] [-s string] [files ...]\n", prog);
	return (-1);
}

int		manage_options(char **av, int *count, int *flag)
{
	int count2;

	count2 = 0;
	while (av[(*count)][++count2])
	{
		if (av[(*count)][count2] == 'p')
			!((*flag) & FLAG_P) ? (*flag) |= FLAG_P : 0;
		else if (av[(*count)][count2] == 'q')
			!((*flag) & FLAG_Q) ? (*flag) |= FLAG_Q : 0;
		else if (av[(*count)][count2] == 'r')
			!((*flag) & FLAG_R) ? (*flag) |= FLAG_R : 0;
		else if (av[(*count)][count2] == 's')
		{
			++count2;
			if (av[(*count)][count2] == '\0')
				return (md5_from_string(av[++(*count)], *flag));
			else
				return (md5_from_string(&av[(*count)][count2], *flag));
		}
		else
			return (wrong_option(av[0], av[(*count)][count2]));
	}
	return (0);
}

int		run_md5(char **av, int *count, int flag)
{
	int	ret;

	ret = 0;
	while (av[(*count)] && ft_strlen(av[(*count)]) > 1)
	{
		if (av[(*count)][0] != '-')
			break ;
		if (manage_options(av, count, &flag) == -1)
			return (-1);
		(*count)++;
	}
	while (av[(*count)] != NULL)
		ret = md5_from_file(av[(*count)++], flag);
	return (ret);
}

int		manage_md5(char **av, int *count, int ac)
{
	int	ret;
	int	flag;

	ret = -1;
	flag = 0;
	if (ac < 3)
		ret = md5_from_standard_input(flag);
	else
	{
		(*count)++;
		ret = run_md5(av, count, flag);
	}
	return (ret);
}
