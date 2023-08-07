/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:20:12 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/07 19:45:59 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_kill(t_general *gen)
{
	int i;
	int status;

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