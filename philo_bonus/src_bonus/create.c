/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:39:46 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/07 16:03:32 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
}