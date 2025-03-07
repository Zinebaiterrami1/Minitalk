/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:12:38 by zait-err          #+#    #+#             */
/*   Updated: 2025/03/07 16:21:50 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    receiver(int signal)
{
    static int    a;
    static char    msg;

    if (signal == SIGUSR1)
        msg = (msg << 1) | 1;
    else if (signal == SIGUSR2)
        msg = (msg << 1);
    a++;
    if (a == 8)
    {
        write(1, &msg, 1);
        a = 0;
        msg = 0;
    }
}

int main(int ac, char **av) 
{
  
  (void)av;
  if(ac != 1)
  {
    printf("Usage: ./server\n");
    return (1);
  }
  printf("PID : %d\n", getpid());
  signal(SIGUSR1, receiver);
	signal(SIGUSR2, receiver);
  while (1)
        pause();  // Wait for a signal

  return 0;
}