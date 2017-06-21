/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lernaean_hydra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 18:57:22 by biremong          #+#    #+#             */
/*   Updated: 2017/02/18 13:55:30 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hydra.h"

int				ft_pong(int new_sfd)
{
	char *buf;

	ft_gnl(new_sfd, &buf);
	if (ft_strequ(buf, "ping"))
		ft_putendl_fd("pong pong!", new_sfd);
	else if (ft_strequ(buf, "quit"))
		return (0);
	else
		ft_putendl_fd("no ping, no pong!", new_sfd);
	free(buf);
	return (1);
}

void			ft_accept_and_serve(int sfd)
{
	int						new_sfd;
	struct sockaddr_storage	client_addr;
	socklen_t				storage_len;

	storage_len = sizeof(client_addr);
	while (1)
	{
		new_sfd = accept(sfd, (struct sockaddr*)&client_addr, &storage_len);
		if (new_sfd == -1)
		{
			perror("accept");
			continue ;
		}
		if (!fork())
		{
			close(sfd);
			while (ft_pong(new_sfd))
				;
			close(new_sfd);
			exit(0);
		}
		close(new_sfd);
	}
}

int				ft_init_server(struct addrinfo *res, int *sfd)
{
	int yes;

	yes = 1;
	while (res)
	{
		*sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (*sfd == -1)
		{
			perror("socket");
			res = res->ai_next;
			continue ;
		}
		if (setsockopt(*sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1
			|| bind(*sfd, res->ai_addr, res->ai_addrlen) == -1
			|| listen(*sfd, 42) == -1)
		{
			perror("bind/listen/setsockopt");
			close(*sfd);
			res = res->ai_next;
			continue ;
		}
		ft_putendl("LISTENING...");
		return (0);
	}
	return (1);
}

struct addrinfo	*ft_get_addrinfo_s(char *port_str)
{
	int				ret;
	struct addrinfo	hints;
	struct addrinfo	*results;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
\
	if ((ret = getaddrinfo(NULL, port_str, &hints, &results)) != 0)
	{
		ft_putendl_fd(gai_strerror(ret), 2);
		exit(1);
	}
\
	return (results);
}

int				main(int ac, char **av)
{
	int				sfd;
	struct addrinfo	*results;

	ac--;
	av++;
	if (ac < 1)
	{
		ft_putendl_fd("error: no port specified", 2);
		exit(1);
	}
	ft_reap_zombies();
	results = ft_get_addrinfo_s(av[0]);
	if (ft_init_server(results, &sfd) != 0)
	{
		ft_putendl_fd("error: server failed", 2);
		exit(1);
	}
	freeaddrinfo(results);
	ft_accept_and_serve(sfd);
	return (0);
}
