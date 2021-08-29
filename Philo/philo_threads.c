/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feschall <feschall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 18:06:14 by feschall          #+#    #+#             */
/*   Updated: 2021/08/29 07:27:58 by feschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_life *philo, t_data *common)
{
	int	num;

	num = -1;
	common->start_time = actual_time(MS);
	while (++num < common->num_of_philos)
	{
		philo[num].last_meals_time = common->start_time;
		if (pthread_create(&philo[num].tid, NULL, \
				(void *)&lifetime, (void *)&philo[num]))
			return (1);
	}
	num = -1;
	while (++num < common->num_of_philos)
		if (pthread_detach(philo[num].tid))
			return (1);
	return (0);
}

void	*lifetime(t_life *philo)
{
	while (true)
	{
		if (takes_forks(philo))
			return (NULL);
		if (pthread_mutex_lock(&philo->mtx.dead) != 0)
			return (NULL);
		philo->last_meals_time = actual_time(MS);
		if (print_msg(philo, " eating\n"))
			return (NULL);
		philo->meal_count++;
		if (pthread_mutex_unlock(&philo->mtx.dead) != 0)
			return (NULL);
		ft_usleep(philo->last_meals_time, philo->cmn->time_to_eat);
		if (puts_forks(philo))
			return (NULL);
		if (print_msg(philo, " sleeping\n"))
			return (NULL);
		ft_usleep(philo->last_meals_time + philo->cmn->time_to_eat, \
											philo->cmn->time_to_sleep);
		if (print_msg(philo, " thinking\n"))
			return (NULL);
		downtime (100);
	}
	return (NULL);
}

int	takes_forks(t_life *philo)
{
	if (philo->priority == true)
	{
		if (pthread_mutex_lock(philo->mtx.r_fork) != 0)
			return (1);
		if (print_msg(philo, " takes right forks\n"))
			return (1);
		if (pthread_mutex_lock(&philo->mtx.l_fork) != 0)
			return (1);
		if (print_msg(philo, " takes left forks\n"))
			return (1);
	}
	else
	{
		if (pthread_mutex_lock(&philo->mtx.l_fork) != 0)
			return (1);
		if (print_msg(philo, " takes left forks\n"))
			return (1);
		if (pthread_mutex_lock(philo->mtx.r_fork) != 0)
			return (1);
		if (print_msg(philo, " takes right forks\n"))
			return (1);
	}
	return (0);
}

int	puts_forks(t_life *philo)
{
	if (philo->priority == true)
	{
		if (pthread_mutex_unlock(&philo->mtx.l_fork) != 0)
			return (1);
		if (pthread_mutex_unlock(philo->mtx.r_fork) != 0)
			return (1);
	}
	else
	{
		if (pthread_mutex_unlock(philo->mtx.r_fork) != 0)
			return (1);
		if (pthread_mutex_unlock(&philo->mtx.l_fork) != 0)
			return (1);
	}
	return (0);
}

void	downtime(long waiting_time)
{
	long	waiting_start_time;

	waiting_start_time = actual_time(US);
	while (actual_time(US) - waiting_start_time < waiting_time)
		usleep(10);
}
