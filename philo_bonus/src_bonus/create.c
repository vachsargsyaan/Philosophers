/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:39:46 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/07 19:43:38 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printo(t_philo	*philo, char *str)
{
	sem_wait(philo->sem_write);
	printf("[%d] : [%lld]  %s", philo->id, get_time(), str);
	sem_post(philo->sem_write);
}

void	*philo_die(t_general *gen)
{
	while (1)
	{
		sem_wait(gen->philos->sem_last_eat);
		if (get_time() - gen->philos->last_eat > gen->time_die)
		{
			sem_wait(gen->philos->sem_write);
			printf("[%d] : [%lld] Died\n", gen->philos->id, get_time());
			sem_post(gen->philos->sem_last_eat);
			exit (EXIT_FAILURE);
		}
		sem_post(gen->philos->sem_last_eat);
		sem_wait(gen->philos->sem_eat);
		if (gen->philos->count_must_eat == gen->max_eat
			&& gen->max_eat != -1)
		{
			sem_post(gen->philos->sem_eat);
			break ;
		}
		sem_post(gen->philos->sem_eat);
	}
	return (NULL);
}

void	forkss(t_general *gen, int i)
{
	pthread_create(&gen->philos[i].philo, NULL,
		(t_phtread_help)philo_die, (&gen));
	if (gen->philos[i].id % 2 == 0)
		ft_usleep(gen->philos->time_eat, gen->philos);
	while (1)
	{
		fork_print(&gen->philos[i]);
		if (gen->philos->count_must_eat == gen->max_eat
			&& gen->max_eat != -1)
		{
			sem_post(gen->philos->sem_eat);
			break ;
		}
		sem_post(gen->philos->sem_eat);
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
