/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semInit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:28:03 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/06 20:15:39 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	general_init(t_general	*gen, char **str)
{
	int		i;
	t_philo	philo;

	i = 0;
	gen->philos_count = ft_atoi(str[1]);
	gen->time_die = ft_atoi(str[2]);
	if (str[5])
		gen->max_eat = ft_atoi(str[5]);
	else
		gen->max_eat = -1;
	gen->philos = (t_philo *)malloc(sizeof(t_philo) * gen->philos_count);
	pilos_init(&philo, str, gen->philos_count);
	while (i < gen->philos_count)
	{
		gen->philos[i].id = i + 1;
		gen->philos[i] = philo;
		i++;
	}
}

void	pilos_init(t_philo	*philo, char **str, int philos_count)
{
	philo->count_must_eat = 0;
	philo->last_eat = 0;
	philo->time_eat = ft_atoi(str[3]);
	philo->time_sleep = ft_atoi(str[4]);
	sema_init(philo, philos_count);
}

void	sema_init(t_philo	*philo, int philos_count)
{
	sem_unlink(SEM_EAT);
	sem_unlink(LAST_EAT);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORK);
	philo->sem_eat = sem_open(SEM_EAT, O_CREAT, S_IRWXU, 1);
	philo->sem_last_eat = sem_open(LAST_EAT, O_CREAT, S_IRWXU, 1);
	philo->sem_write = sem_open(SEM_WRITE, O_CREAT, S_IRWXU, 1);
	philo->sem_fork = sem_open(SEM_FORK, O_CREAT, S_IRWXU, philos_count);
	if (philo->sem_eat == SEM_FAILED || philo->sem_last_eat == SEM_FAILED
		|| philo->sem_write == SEM_FAILED || philo->sem_fork == SEM_FAILED)
	{
		perror("sem_open()");
		exit (EXIT_FAILURE);
	}
}
