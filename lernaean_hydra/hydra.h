/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hydra.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 13:50:31 by biremong          #+#    #+#             */
/*   Updated: 2017/02/18 13:59:53 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HYDRA_H

# define HYDRA_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <errno.h>
# include <stdio.h>
# include <signal.h>

int				ft_pong(int new_sfd);
void			ft_accept_and_serve(int sfd);
int				ft_init_server(struct addrinfo *res, int *sfd);
struct addrinfo	*ft_get_addrinfo_s(char *port_str);
void			ft_reap_zombies(void);
void			ft_sigchld_handler(int s);
struct addrinfo	*ft_get_addrinfo_c(char *ip_str, char *port_str);
int				ft_init_connection(struct addrinfo *res, int *sfd);
int				ft_ping(int sfd);

#endif
