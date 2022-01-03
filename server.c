/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 20:29:51 by asalek            #+#    #+#             */
/*   Updated: 2021/12/29 20:29:53 by asalek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	my_handler(int mysig, siginfo_t *info, void *context)
{
	static int	i;
	static char	c;
	static int	pid;

	(void)context; // i cast it to void cause i will not use it at all
	if (pid != info->si_pid) //if the sedner client id doesn't match the client id stored earlier
	{
		c = 0;
		i = 0;
		pid = 0;
	}
	mysig -= SIGUSR1; //is mysig == sigusr1 results 0 else results will be 1 if mysig == sigusr2
	c = c << 1 | mysig;// shifting the character to the left by 1 and using OR operator
	i++;
	if (i == 8)
	{
		if (c == '\0')
			kill(info->si_pid, SIGUSR1); // if message recieved send a signal to the client process to print message_recieved message
		ft_putchar(c);
		i = 0;
		c = 0;
		pid = 0;
	}
	pid = info->si_pid; // store the client process id
}

int	main(void)
{
	struct sigaction	sig; // calling the sigaction struct in signal.h
	int					sig_return;

	sig.sa_sigaction = &my_handler;
	sig.sa_flags = SA_SIGINFO; //stored the client process id in sa_flags 
	sig_return = sigaction(SIGUSR1, &sig, NULL);
	if (sig_return == -1)
		exit(1);
	sig_return = sigaction(SIGUSR2, &sig, NULL);
	if (sig_return == -1)
		exit(1);
	ft_putstr("Server ID -> ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	while (1)
		sleep(1);
}
