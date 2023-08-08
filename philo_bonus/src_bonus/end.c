/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:20:12 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/08 16:43:38 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_kill(t_general *gen)
{
	int	i;
	int	status;

	i = 0;
	while (i < gen->philos_count)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) > 0)
		{
			i = 0;
			while (i < gen->philos_count)
			{
				kill(gen->philos[i].pid, SIGTERM);
				i++;
			}
			break ;
		}
		i++;
	}
}

void	sema_close_free(t_general *gen)
{
	sem_close(gen->philos->sem_eat);
	sem_close(gen->philos->sem_last_eat);
	sem_close(gen->philos->sem_write);
	sem_close(gen->philos->sem_fork);
	sem_unlink(SEM_EAT);
	sem_unlink(LAST_EAT);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORK);
	free(gen->philos);
}
