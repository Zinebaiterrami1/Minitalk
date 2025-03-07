/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:12:36 by zait-err          #+#    #+#             */
/*   Updated: 2025/03/07 16:03:35 by zait-err         ###   ########.fr       */
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
		i ++;
	}
	return (result * sign);
}
void send_bits(int pid, unsigned char octet)
{
	int bit;
	int shift;
	int i;

	i = 7;
	while(i >= 0)
	{
		shift = 1 << i;
		bit = octet & shift;
		
		if(bit == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		sleep(100);
		i--;
	}
	
}

void 	send_message(int server_pid, char *message)
{
	while(*message)
	{
		send_bits(server_pid, *message);
		message++;
	}
	send_bits(server_pid, '\0');
}

int main(int ac, char **av)
{
    int server_pid;
    char     *message;
    
    if(ac != 3)
    {	
        write(1, "Usage: ./client <server_pid> <message>\n", 40);
		return (1);
    }
	server_pid = ft_atoi(av[1]);
	message = av[2];
	send_message(server_pid, message);
}
