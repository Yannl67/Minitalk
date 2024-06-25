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
	}
	else if (errnum > 3)
	{
		ft_putstr_fd("Too many arguments.\n", 1);
		ft_putstr_fd("Usage: ./client [PID] [STRING]\n", 1);
	}
	else if (errnum == -1)
		ft_putstr_fd("Please check that the process id is correct.\n", 1);
	else if (errnum == -2)
		ft_putstr_fd("There is no process running with this id.\n", 1);
}

static int	ft_check_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		else if (str[i] == '0' && str[i + 1] == '\0')
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_args(int argc, char **argv)
{
	if (argc != 3)
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
	else if (ft_strlen(argv[1]) == 1)
	{
		display_error(-1);
		return (0);
	}
	return (1);
}
