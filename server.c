/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:11:13 by guferrei          #+#    #+#             */
/*   Updated: 2021/09/10 15:39:44 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#define _POSIX_SOURCE

void	ft_putnbr(unsigned int n)
{
	char			str[11];
	char			*ptr;
	int				c;

	c = 0;
	ptr = &str[0];
	while (n > 9)
	{
		*(ptr + c) = (n % 10) + 48;
		n = n / 10;
		c++;
	}
	*(ptr + c) = n + 48;
	while (c >= 0)
	{
		write(1, &*(ptr + c), 1);
		c--;
	}
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static unsigned int	z;
	static unsigned int	c;

	(void)context;
	if (z > 7)
	{
		z = 0;
		c = 0;
	}
	if (sig == SIGUSR2)
		c += 1 << z;
	kill(info->si_pid, SIGUSR1);
	z++;
	if (z == 8)
	{
		if (c == 0)
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR2);
		}
		else
			write(1, &c, 1);
	}
}

int	main(void)
{
	struct sigaction	act;
	pid_t				pid;

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &act, NULL);
	sigaction(SIGUSR1, &act, NULL);
	pid = getpid();
	ft_putnbr((unsigned int)pid);
	write(1, "\n", 1);
	while (true)
	{
	}
}
