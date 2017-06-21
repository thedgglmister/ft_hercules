/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lernaean_hydra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 18:57:22 by biremong          #+#    #+#             */
/*   Updated: 2017/02/18 14:01:20 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hydra.h"

void	ft_sigchld_handler(int s)
{
	s++;
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
}

void	ft_reap_zombies(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = ft_sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
}
