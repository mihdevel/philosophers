/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 10:56:03 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/27 20:54:00 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "psilo.h"

long unsigned	get_time(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

int	check_args(t_data *data)
{
	if (data->num_of_phils == 0 || data->time_to_die == 0
		|| data->time_to_eat == 0 || data->time_to_sleep == 0)
		return (1);
	return (0);
}

static int	init_argv(t_data *data, int ac, char **av)
{
	data->ac = ac;
	data->num_of_phils = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->how_many_to_eat = ft_atoi(av[5]);
		if (data->how_many_to_eat == 0)
			return (1);
	}
	return (check_args(data));
}

int	start_phils(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_phils)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&(data->phils[i].thread), NULL, life_phil,
					(void *) &(data->phils[i])))
				return (free_and_exit(data, "thread creation."));
		}
	}
	usleep(10000);
	i = -1;
	while (++i < data->num_of_phils)
	{
		if (i % 2 == 1)
		{
			if (pthread_create(&(data->phils[i].thread), NULL, life_phil,
					(void *) &(data->phils[i])))
				return (free_and_exit(data, "thread creation."));
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	data.forks = NULL;
	data.phils = NULL;
	if (ac != 5 && ac != 6)
		return (free_and_exit(&data, "the quantity of arguments is incorrect"));
	data.t_start = get_time();
	if (init_argv(&data, ac, av))
		return (free_and_exit(&data, "the invalid argument."));
	if (init_phils(&data))
		return (1);
	if (start_phils(&data))
		return (1);
	usleep(1000);
	if (monitor(&data))
		return (free_all(&data));
}
