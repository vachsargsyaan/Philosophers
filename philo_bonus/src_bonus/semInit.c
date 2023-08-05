/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semInit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:28:03 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/05 18:15:43 by vacsargs         ###   ########.fr       */
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
	sema_init(philo, str, philos_count);
}
void sema_init(t_philo	*philo, char **str, int philos_count)
{
	(void)philo;
	(void)str;
	(void)philos_count;
}