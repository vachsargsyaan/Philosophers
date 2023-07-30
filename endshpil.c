/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endshpil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:45:56 by vacsargs          #+#    #+#             */
/*   Updated: 2023/07/30 20:17:58 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pilo_live(t_general	*gen)
{
	int	i;

	i = 0;
	while (i < gen->philos_count)
	{
		pthread_mutex_lock(&(gen->philos[i].mutex_last_eat));
		if (get_time() - gen->philos[i].last_eat > gen->time_die)
		{
			pthread_mutex_lock(&(gen->mutex_die));
			gen->die = 1;
			pthread_mutex_unlock(&(gen->mutex_die));
			pthread_mutex_lock(&gen->mutex_write);
			printf("[%d] : [%lu] He is died\n", gen->philos[i].id, get_time());
			return (0);
		}
		i++;
		pthread_mutex_lock(&(gen->philos[i].mutex_last_eat));	
	}
	return (1);
}