/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 11:18:07 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/28 12:32:26 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "psilo.h"

static int	is_life(t_phil *ph)
{
	if (get_time() - ph->t_start >= ph->time_to_die)
	{
		ph->is_life = 0;
		return (0);
	}
	return (1);
}

int	monitor(t_data *data)
{
	int		i;
	int		flag;

	while (1)
	{
		i = -1;
		flag = 0;
		while (++i < data->num_of_phils)
		{
			if (!flag && data->phils[i].num_eating < data->how_many_to_eat)
				flag = 1;
			if (is_life(&data->phils[i]) == 0)
			{
				pthread_mutex_lock(data->mut_print);
				printf(MSG_DIED, get_time() - data->t_start, i + 1);
				return (1);
			}
		}
		if (data->ac == 6 && !flag)
		{
			pthread_mutex_lock(data->mut_print);
			return (1);
		}
		usleep(3000);
	}
}
