/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 15:38:53 by ddinaut           #+#    #+#             */
/*   Updated: 2018/12/08 22:46:00 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void	print_usage(const char *prog)
{
	ft_printf("usage: %s command [ command_opts ] [ command_args ]\n", prog);
}

int		manage_input(char **argv, int ac)
{
	int	count;

	count = 1;
	if (argv[count] != NULL && count < ac)
	{
		if (ft_strcmp(argv[count], "md5") == TRUE)
			return (manage_md5(argv, &count, ac));
		else if (ft_strcmp(argv[count], "sha256") == TRUE)
			return (secure_hash_algo_512());
		else
		{
			ft_printf_fd(STDERR_FILENO, "unknow message digest command: abort\n.");
			return (-1);
		}
	}
	return (0);
}

int		main(int ac, char **av)
{
	int		ret;

	if (ac < 2)
		print_usage(av[0]);
	ret = manage_input(av, ac);
	return (ret);
}
