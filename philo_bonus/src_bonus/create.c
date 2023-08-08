/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:39:46 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/08 18:02:37 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printo(t_philo	*philo, char *str)
{
	sem_wait(philo->sem_write);
	printf("[%d] : [%lld]  %s", philo->id, get_time(), str);
	sem_post(philo->sem_write);
}

void	*philo_die(void (*gen1))
{
	t_philo	*philos;

	philos = (t_philo *)(gen1);
	while (1)
	{
		sem_wait(philos->sem_last_eat);
		if (get_time() - philos->last_eat > philos->time_die)
		{
			sem_wait(philos->sem_write);
			printf("[%d] : [%lld] Died\n", philos->id, get_time());
			sem_post(philos->sem_last_eat);
			exit (1);
		}
		sem_post(philos->sem_last_eat);
		sem_wait(philos->sem_eat);
		if (philos->count_must_eat == philos->max_eat
			&& philos->max_eat != -1)
		{
			sem_post(philos->sem_eat);
			exit(0);
		}
		sem_post(philos->sem_eat);
	}
	return (NULL);
}

void	forkss(t_general *gen, int i)
{
	pthread_create(&gen->philos[i].philo, NULL,
		&philo_die, (void *)(&gen->philos[i]));
	if (gen->philos[i].id % 2 == 0)
		ft_usleep(gen->philos->time_eat, gen->philos);
	while (1)
	{
		fork_print(&gen->philos[i]);
		printo(&gen->philos[i], "He is sleeping\n");
		ft_usleep(gen->philos[i].time_sleep, gen->philos);
		printo(&gen->philos[i], "He is thinking\n");
	}
}

void	fork_print(t_philo *philo)
{
	sem_wait(philo->sem_fork);
	printo(philo, "He picked up a fork\n");
	sem_wait(philo->sem_fork);
	printo(philo, "He picked up a fork\n");
	printo(philo, "He started to eat\n");
	sem_wait(philo->sem_last_eat);
	philo->last_eat = get_time();
	sem_post(philo->sem_last_eat);
	ft_usleep(philo->time_eat, philo);
	sem_wait(philo->sem_eat);
	philo->count_must_eat++;
	sem_post(philo->sem_eat);
	sem_post(philo->sem_fork);
	sem_post(philo->sem_fork);
}

void	start_fork(t_general *gen)
{
	int	i;

	i = 0;
	while (i < gen->philos_count)
	{
		gen->philos[i].id = i + 1;
		gen->philos[i].pid = fork();
		if (gen->philos[i].pid < 0)
		{
			perror("fork ");
			exit (EXIT_FAILURE);
		}
		if (gen->philos[i].pid == 0)
			forkss(gen, i);
		i++;
	}
	philo_kill(gen);
}
