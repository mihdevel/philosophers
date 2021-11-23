/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psilo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 13:16:48 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/28 12:32:43 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PSILO_H
#define PSILO_H

#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

# define MSG_DIED "%ld	%d philosopher died"

typedef pthread_mutex_t t_mutex;

typedef struct s_phil
{
	int				num;
	t_mutex			*l_fork;
	t_mutex			*r_fork;
	t_mutex			*mut_print;
	pthread_t		thread;
	long unsigned	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long unsigned	t_start;
	long unsigned	pr_start;
	int				is_life;
	int				num_eating;
}					t_phil;

typedef struct s_data
{
	int				num_of_phils;
	t_mutex			*forks;
	t_mutex			*mut_print;
	t_phil			*phils;
	int		 		time_to_die;
	int 			time_to_eat;
	int	 			time_to_sleep;
	int 			how_many_to_eat;
	int 			ac;
	long unsigned	t_start;
}				t_data;

int				init_phils(t_data *data);
void			*life_phil(void *data);
int				free_all(t_data *data);
int				free_and_exit(t_data *data, char *msg);
int				ft_strlen(char *str);
long unsigned	get_time(void);
int				ft_atoi(const char *str);
int 			monitor(t_data *data);
int				my_usleep(unsigned long long time);

#endif //PSILO_H