/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 20:29:59 by asalek            #+#    #+#             */
/*   Updated: 2021/12/29 20:30:00 by asalek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	message_recieved(int a)
{
	(void)a;
	ft_putstr("***********************************************\n");
	ft_putstr("* 👨‍💻*--------👾 Message Recevied 👾--------*👨‍💻 *\n");
	ft_putstr("* 👨‍💻*--------👾        💪🏻        👾--------*👨‍💻 *\n");
	ft_putstr("* 👨‍💻*--------👾 Message Recevied 👾--------*👨‍💻 *\n");
	ft_putstr("***********************************************\n");
}

static void	send_byte_to_server(char byte, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (byte >> i & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(400); // for avoiding the lag i use usleep with 400 micro second
		i--;
	}
}

int	main(int ac, char *av[])
{
	char	*str;
	pid_t	pid;

	signal(SIGUSR1, message_recieved); // to detect if the message has been sent. if yes message_recieved get print on client screen
	if (ac != 3)
	{
		ft_putstr("Client takes two Args:\n◦ The PID.\n◦ String to send.");
		exit(1);
	}
	pid = ft_atoi(av[1]);
	str = av[2];
	while (*str)
	{
		send_byte_to_server(*str, pid);
		str++;
	}
	send_byte_to_server(0, pid);
	return (0);
}
