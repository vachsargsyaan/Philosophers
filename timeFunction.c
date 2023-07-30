/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeFunction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:30:22 by vacsargs          #+#    #+#             */
/*   Updated: 2023/07/30 20:17:31 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	static unsigned long long	start;
	static int					count = 0;
	struct timeval				as;

	gettimeofday(&as, NULL);
	if (count == 0)
	{
		start = (as.tv_sec * 1000 + as.tv_usec / 1000);
		count++;
	}
	return ((as.tv_sec * 1000 + as.tv_usec / 1000) - start);
}

void	ft_usleep(unsigned long sleap, t_philo	*philo)
{
	unsigned long	value;

	value = get_time();
	while (!pilo_die(philo))
	{
		if (get_time() - value <= sleap)
			usleep(50);
		else
			break ;
	}
}
