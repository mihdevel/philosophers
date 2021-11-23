/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_phil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 09:51:47 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/28 12:32:37 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "psilo.h"

static void	mutex_print(t_phil *ph, char *msg)
{
	pthread_mutex_lock(ph->mut_print);
	printf(msg, get_time() - ph->pr_start, ph->num);
	pthread_mutex_unlock(ph->mut_print);
}

void	eat(t_phil *ph)
{
	pthread_mutex_lock(ph->r_fork);
	mutex_print(ph, "%ld\t%d philosopher has taken a right fork.\n");
	pthread_mutex_lock(ph->l_fork);
	mutex_print(ph, "%ld\t%d philosopher has taken a left fork.\n");
	mutex_print(ph, "%ld\t%d philosopher is eating.\n");
	ph->num_eating++;
	ph->t_start = get_time();
	my_usleep(ph->time_to_eat * 1000);
	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(ph->r_fork);
}

void	think(t_phil *ph)
{
	mutex_print(ph, "%ld\t%d philosopher is thinking.\n");
}

void	ph_sleep(t_phil *ph)
{
	mutex_print(ph, "%ld\t%d philosopher is sleeping.\n");
	my_usleep(ph->time_to_sleep * 1000);
}

void	*life_phil(void *data)
{
	t_phil	*ph;

	ph = (t_phil *)data;
	ph->t_start = get_time();
	while (ph->is_life == 1)
	{
		think(ph);
		eat(ph);
		ph_sleep(ph);
	}
	return (NULL);
}
