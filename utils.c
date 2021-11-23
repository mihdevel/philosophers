/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 13:57:27 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/28 12:32:32 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "psilo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && *str++)
		i++;
	return (i);
}

int	free_all(t_data *data)
{
	free(data->phils);
	free(data->forks);
	return (0);
}

int	free_and_exit(t_data *data, char *msg)
{
	if (data)
		free_all(data);
	write(1, "Error: ", 7);
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	return (1);
}

int	my_usleep(unsigned long long time)
{
	struct timeval	start;
	struct timeval	new;

	if (gettimeofday(&start, NULL) == -1)
		return (1);
	while (21)
	{
		usleep(21);
		if (gettimeofday(&new, NULL))
			return (1);
		if ((unsigned long long)((new.tv_sec - start.tv_sec) * 1000000
			+ new.tv_usec - start.tv_usec) > (unsigned long long)time)
			break ;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	den;

	i = 0;
	res = 0;
	den = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		den = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] > 47 && str[i] < 58 && str[i] != '\0')
	{
		res = res * 10;
		res = res + str[i++] - '0';
	}
	if (den == 1)
		res *= -1;
	return (res);
}
