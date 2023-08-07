/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:20:14 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/06 20:15:52 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <signal.h>
# include <semaphore.h>

# define SEM_WRITE "/sem_write"
# define LAST_EAT "/sem_last_eat"
# define SEM_EAT "/sem_eat"
# define SEM_FORK "/sem_fork"

typedef struct s_philo
{
	pid_t		pid;
	int			id;
	int			last_eat;
	int			time_eat;
	int			time_sleep;
	int			count_must_eat;
	pthread_t	philo;
	sem_t		*sem_eat;
	sem_t		*sem_last_eat;
	sem_t		*sem_write;
	sem_t		*sem_fork;
}t_philo;

typedef struct s_general
{
	int				max_eat;
	int				time_die;
	int				philos_count;
	t_philo			*philos;
}t_general;

int		main(int argc, char **argv);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
long	ft_atoi(const char *str);
void	general_init(t_general	*gen, char **str);
void	pilos_init(t_philo	*philo, char **str, int philos_count);
void	sema_init(t_philo	*philo, int philos_count);

#endif