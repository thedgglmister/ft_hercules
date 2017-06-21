/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lernaean_hydra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 18:57:22 by biremong          #+#    #+#             */
/*   Updated: 2017/02/18 13:58:53 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hydra.h"

struct addrinfo	*ft_get_addrinfo_c(char *ip_str, char *port_str)
{
	int				ret;
	struct addrinfo	hints;
	struct addrinfo	*results;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
\
	if ((ret = getaddrinfo(ip_str, port_str, &hints, &results)) != 0)
	{
		ft_putendl_fd(gai_strerror(ret), 2);
		exit(1);
	}
\
	return (results);
}

int				ft_init_connection(struct addrinfo *res, int *sfd)
{
	while (res)
	{
		*sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (*sfd == -1)
		{
			perror("socket");
			res = res->ai_next;
			continue ;
		}
		if (connect(*sfd, res->ai_addr, res->ai_addrlen) == -1)
		{
			perror("connect");
			close(*sfd);
			res = res->ai_next;
			continue ;
		}
		ft_putendl("CONNECTED...");
		return (0);
	}
	return (1);
}

int				ft_ping(int sfd)
{
	char *buf;

	ft_gnl(0, &buf);
	ft_putendl_fd(buf, sfd);
	if (ft_strequ(buf, "quit"))
	{
		free(buf);
		return (0);
	}
	free(buf);
	ft_gnl(sfd, &buf);
	ft_putendl(buf);
	free(buf);
	return (1);
}

int				main(int ac, char **av)
{
	int				sfd;
	struct addrinfo	*results;

	ac--;
	av++;
	if (ac < 2)
	{
		ft_putendl_fd("error: no hostname and/or port specified", 2);
		exit(1);
	}
	results = ft_get_addrinfo_c(av[0], av[1]);
	if (ft_init_connection(results, &sfd) != 0)
	{
		ft_putendl_fd("error: connection failed", 2);
		exit(1);
	}
	freeaddrinfo(results);
	while (ft_ping(sfd))
		;
	close(sfd);
}
