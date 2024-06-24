/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamouri <ylamouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:51:32 by ylamouri          #+#    #+#             */
/*   Updated: 2024/06/24 17:22:56 by ylamouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	display_error(int errnum)
{
	if (errnum > 0 && errnum < 3)
	{
		ft_putstr_fd("Too few arguments.\n", 1);
		ft_putstr_fd("Usage: ./client [PID] [STRING]\n", 1);
		ft_putstr_fd("Try './client --help' for more information.\n", 1);
	}
	else if (errnum > 3)
	{
		ft_putstr_fd("Too many arguments.\n", 1);
		ft_putstr_fd("Usage: ./client [PID] [STRING]\n", 1);
		ft_putstr_fd("Try './client --help' for more information.\n", 1);
	}
	else if (errnum == -1)
		ft_putstr_fd("Please check that the process id is correct.\n", 1);
	else if (errnum == -2)
		ft_putstr_fd("There is no process running with this id.\n", 1);
}

static void	display_help(void)
{
	ft_putstr_fd("UUsage: ./client [PID] [STRING]\n", 1);
	ft_putstr_fd("Minitalk is a process that enables dialogue \
between a client and a server.\n", 1);
	ft_putstr_fd("It is necessary to have launched the server \
file before trying to dialogue via the client file, otherwise \
it won't work.\n", 1);
	ft_putstr_fd("Example : ./client 40158 \"Hello World !\"\n", 1);
	ft_putstr_fd("	[PID] is the process id displayed when launching \
the server file\n", 1);
	ft_putstr_fd("	[STRING] is the message you wish to send\n", 1);
}

static int	ft_check_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (str[i] == 0 && str[i + 1] == '\0')
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_args(int argc, char **argv)
{
	if (argc == 2 && ft_strncmp(argv[1], "--help", 6) == 0)
	{
		display_help();
		return (0);
	}
	else if (argc != 3)
	{
		display_error(argc);
		return (0);
	}
	else if (!ft_check_only_digits(argv[1]))
	{
		display_error(-1);
		return (0);
	}
	else if (kill(ft_atoi(argv[1]), 0) != 0)
	{
		display_error(-2);
		return (0);
	}
	return (1);
}
