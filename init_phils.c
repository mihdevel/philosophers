/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_phils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:19:19 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/27 18:01:42 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "psilo.h"

static int	create_phils(t_data *data)
{
	int		i;

	data->phils = (t_phil *)malloc((sizeof(t_phil) * (data->num_of_phils)));
	if (!data->phils)
		return (free_and_exit(data, "malloc`s."));
	memset((void *)data->phils, 0, (sizeof(t_phil) * (data->num_of_phils)));
	i = -1;
	while (++i < data->num_of_phils)
		data->phils[i].num = i + 1;
	return (0);
}

static void	write_data_phils(t_data *data)
{
	int		i;

	data->mut_print = (t_mutex *)malloc(sizeof(t_mutex) * 1);
	if (pthread_mutex_init((data->mut_print), NULL))
		return ;
	i = -1;
	while (++i < data->num_of_phils)
	{
		data->phils[i].num_eating = 0;
		data->phils[i].is_life = 1;
		data->phils[i].time_to_die = data->time_to_die;
		data->phils[i].time_to_eat = data->time_to_eat;
		data->phils[i].time_to_sleep = data->time_to_sleep;
		data->phils[i].mut_print = data->mut_print;
		data->phils[i].pr_start = data->t_start;
	}
}

static int	create_forks(t_data *data)
{
	int	i;

	data->forks = (t_mutex *)malloc(sizeof(t_mutex) * data->num_of_phils);
	i = -1;
	while (++i < data->num_of_phils)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (free_and_exit(data, "mutex`s init."));
	}
	return (0);
}

void	dist_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_phils)
	{
		data->phils[i].l_fork = &(data->forks[i]);
		if (i == (data->num_of_phils - 1))
			data->phils[i].r_fork = &(data->forks[0]);
		else
			data->phils[i].r_fork = &(data->forks[i + 1]);
	}
}

int	init_phils(t_data *data)
{
	if (create_phils(data))
		return (1);
	write_data_phils(data);
	if (create_forks(data))
		return (1);
	dist_forks(data);
	return (0);
}
