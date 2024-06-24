/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamouri <ylamouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:32:11 by ylamouri          #+#    #+#             */
/*   Updated: 2024/06/24 17:21:59 by ylamouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_send_terminated_string(int pid)
{
	int	bit;

	bit = 7;
	while (bit != -1)
	{
		if (1 & ('\0' >> bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		bit--;
	}
}

static void	ft_send_str_to_binary(int pid, unsigned char *str)
{
	int		bit;
	int		i;

	i = 0;
	while (str[i])
	{
		bit = 7;
		while (bit >= 0)
		{
			if (str[i] & (1 << bit))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(500);
			bit--;
		}
		i++;
	}
	if (str[i] == '\0')
		ft_send_terminated_string(pid);
}

int	main(int argc, char **argv)
{
	int				pid;
	unsigned char	*str;

	if (!ft_check_args(argc, argv))
		return (0);
	if (ft_strlen(argv[1]) == 1)
	{
		display_error(-2);
		return (0);
	}
	pid = ft_atoi(argv[1]);
	str = (unsigned char *)argv[2];
	ft_send_str_to_binary(pid, str);
}
