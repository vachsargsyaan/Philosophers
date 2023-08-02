/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endshpil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:45:56 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/02 15:43:46 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pilo_live(t_general	*gen)
{
	int	i;

	i = 0;
	while (i < gen->philos_count)
	{
		pthread_mutex_lock(&gen->philos[i].mutex_last_eat);
		if (get_time() - gen->philos[i].last_eat > gen->time_die)
		{
			pthread_mutex_lock(gen->philos[i].mutex_write);
			printf("[%d] : [%lld] Died\n", gen->philos[i].id, get_time());
			pthread_mutex_unlock(gen->philos[i].mutex_write);
			pthread_mutex_lock(gen->philos[i].mutex_die);
			gen->die = 1;
			pthread_mutex_unlock(gen->philos[i].mutex_die);
			pthread_mutex_unlock(&gen->philos[i].mutex_last_eat);
			return (1);
		}
		pthread_mutex_unlock(&gen->philos[i].mutex_last_eat);
		i++;
	}
	return (0);
}
