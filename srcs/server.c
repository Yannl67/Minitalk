/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamouri <ylamouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:32:19 by ylamouri          #+#    #+#             */
/*   Updated: 2024/06/24 17:24:41 by ylamouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	*g_message = NULL;

static void	startup_message(char *pid)
{
	ft_putstr_fd("\e[0;34m===============================\
	=============================================\n", 1);
	ft_putstr_fd("	███╗   ███╗██╗███╗   ██╗██╗████████╗ ██\
	███╗ ██╗     ██╗  ██╗\n", 1);
	ft_putstr_fd("	████╗ ████║██║████╗  ██║██║╚══██╔══╝██\
	╔══██╗██║     ██║ ██╔╝\n", 1);
	ft_putstr_fd("	██╔████╔██║██║██╔██╗ ██║██║   ██║   ██\
	█████║██║     █████╔╝\n", 1);
	ft_putstr_fd("	██║╚██╔╝██║██║██║╚██╗██║██║   ██║   ██\
	╔══██║██║     ██╔═██╗\n", 1);
	ft_putstr_fd("	██║ ╚═╝ ██║██║██║ ╚████║██║   ██║   ██\
	║  ██║███████╗██║  ██╗\n", 1);
	ft_putstr_fd("	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝   ╚═╝\
	  ╚═╝╚══════╝╚═╝  ╚═╝\n", 1);
	ft_putstr_fd("==========================================\
	==================================\n", 1);
	ft_putstr_fd("\e[0;36m		     ✩ ░▒▓▆▅▃▂▁ PID : ", 1);
	ft_putstr_fd(pid, 1);
	ft_putstr_fd(" ▁▂▃▅▆▓▒░ ✩\x1b[0m\n\n", 1);
}

static void	print_message(void)
{
	if (g_message)
	{
		ft_putstr_fd(g_message, 1);
		free(g_message);
	}
	ft_putchar_fd('\n', 1);
	g_message = NULL;
}

static void	append_char(int c)
{
	char		*new_str;

	if (!g_message)
	{
		g_message = malloc(sizeof(char *) * 1);
		if (!g_message)
			return ;
		g_message[0] = '\0';
	}
	new_str = NULL;
	new_str = malloc(sizeof(char *) * 2);
	if (!new_str)
		return ;
	new_str[0] = c;
	new_str[1] = '\0';
	g_message = ft_strjoin(g_message, new_str);
}

static void	ft_signal_receiver(int signum, siginfo_t *info, void *context)
{
	static int	c = 0;
	static int	bit = 7;

	(void)info;
	(void)context;
	if (signum == SIGUSR1)
		c += 1 << bit;
	else if (signum == SIGUSR2)
		c += 0 << bit;
	bit--;
	if (bit == -1)
	{
		if (c == '\0')
			print_message();
		else
			append_char(c);	
		bit = 7;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	char				*pid;

	sa.sa_sigaction = ft_signal_receiver;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	pid = ft_itoa(getpid());
	startup_message(pid);
	free(pid);
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
}
