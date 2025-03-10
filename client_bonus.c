/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 04:20:51 by zait-err          #+#    #+#             */
/*   Updated: 2025/03/10 04:04:15 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	int			i;
	long int	result;
	int			sign;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = sign * -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

void	send_bits(int pid, unsigned char octet)
{
	int	i;
	int	bit;
	int	shift;
	int	res;

	i = 7;
	while (i >= 0)
	{
		shift = 1 << i;
		bit = octet & shift;
		if (bit == 0)
			res = kill(pid, SIGUSR1);
		else
			res = kill(pid, SIGUSR2);
		if (res == -1)
		{
			ft_printf("Failed while sending the message!\n");
			exit(1);
		}
		usleep(20000);
		i--;
	}
}

void	send_message(int server_pid, char *message)
{
	while (*message)
	{
		send_bits(server_pid, *message);
		message++;
	}
	send_bits(server_pid, '\0');
}

void	check_receive(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("message wsel!\n");
}

int	main(int ac, char **av)
{
	int		server_pid;
	char	*message;

	if (ac != 3)
	{
		write(1, "Usage: ./client <server_pid> <message>\n", 40);
		return (1);
	}
	signal(SIGUSR1, check_receive);
	signal(SIGUSR2, check_receive);
	server_pid = ft_atoi(av[1]);
	message = av[2];
	if (server_pid <= 0 || server_pid > 4194304)
	{
		ft_printf("Invalid PID\n");
		exit(1);
	}
	send_message(server_pid, message);
}
