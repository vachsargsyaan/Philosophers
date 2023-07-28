/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:40:27 by vacsargs          #+#    #+#             */
/*   Updated: 2023/07/28 19:17:54 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int pilo_die(t_philo *philo)
{
	int i;
	
	pthread_mutex_lock(philo->mutex_die);
	i = *(philo->die);
	pthread_mutex_unlock(philo->mutex_die);
	return (i);
}
void	check_all_live(t_philo	*philo, char *str)
{
	pthread_mutex_lock(philo->mutex_write);
	if (pilo_die(philo) == 0)
		printf("[%d] : %s", philo->id, str);	
	pthread_mutex_unlock(philo->mutex_write);
	
}

void	*routine(void (*a))
{
	t_philo	*philo;

	philo = (t_philo *)a;
	if (philo->id % 2 == 1)
		usleep(1000);
	pthread_mutex_lock(philo->mutex_left);
	check_all_live(philo,"He picked up a fork from the left\n");
	pthread_mutex_lock(philo->mutex_right);
	check_all_live(philo,"He picked up a fork from the right\n");
	check_all_live(philo,"He started to eat\n");
	pthread_mutex_lock(&philo->mutex_last_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->mutex_last_eat);
	usleep(1000);
	pthread_mutex_unlock(philo->mutex_left);
	pthread_mutex_unlock(philo->mutex_right);
	return (0);
}

void	ft_create(t_general	*gen)
{
	int	i;

	i = 0;
	while (i < gen->philos_count)
	{
		pthread_create(&gen->philos[i].philo, NULL,
			&routine, (void*)(&gen->philos[i]));
		i++;
	}
	i = 0;
	while (i < gen->philos_count)
	{
		pthread_join((gen->philos[i].philo), NULL);
		i++;
	}
}