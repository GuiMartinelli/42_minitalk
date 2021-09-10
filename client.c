/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:15:44 by guferrei          #+#    #+#             */
/*   Updated: 2021/09/10 15:40:34 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int	ft_atoi(const char *ptr)
{
	int			s;
	long int	n;

	s = 1;
	n = 0;
	while (*ptr >= 48 && *ptr <= 57)
	{
		n = n * 10;
		n = n + ((int)*ptr - 48);
		ptr++;
	}
	return (n * s);
}

void	handle_client(int sig)
{
	if (sig == SIGUSR2)
		exit(0);
}

int	char_to_bin(int pid, unsigned int c)
{
	int		x;

	x = 0;
	while (x < 8)
	{
		if (c % 2 == 0 || c == 0)
		{
			kill(pid, SIGUSR1);
			sleep(2);
		}
		else
		{
			kill(pid, SIGUSR2);
			sleep(2);
		}
		c /= 2;
		x++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int				pid;
	unsigned int	c;

	pid = ft_atoi(argv[1]);
	if (argc != 3)
		return (1);
	while (*argv[2])
	{
		c = *argv[2];
		signal(SIGUSR1, handle_client);
		char_to_bin(pid, c);
		argv[2]++;
	}
	signal(SIGUSR2, handle_client);
	char_to_bin(pid, '\0');
}
