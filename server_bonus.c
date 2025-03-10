/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:50:11 by zait-err          #+#    #+#             */
/*   Updated: 2025/03/10 03:31:24 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	reset_client(int *bit, char *character, int *client_pid, int new_pid)
{
	*bit = 0;
	*character = 0;
	*client_pid = new_pid;
}

void	handle_signal(int sig, siginfo_t *info, void *more_info)
{
	static int	bit;
	static char	character;
	static int	client_pid;
	static int	len;

	(void)more_info;
	if (!client_pid)
		client_pid = info->si_pid;
	if (client_pid != info->si_pid)
		reset_client(&bit, &character, &client_pid, info->si_pid);
	if (sig == SIGUSR1)
		bit = 0;
	else
		bit = 1;
	character = (character << 1) | (bit & 1);
	len++;
	if (len == 8)
	{
		if (character == '\0')
			kill(client_pid, SIGUSR1);
		ft_printf("%c", character);
		len = 0;
		character = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	(void)av;
	if (ac != 1)
	{
		printf("Usage: ./server\n");
		return (1);
	}
	printf("PID : %d\n", getpid());
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
