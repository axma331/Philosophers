/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feschall <feschall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 13:32:30 by feschall          #+#    #+#             */
/*   Updated: 2021/08/29 07:00:01 by feschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_life *philo, t_data *common, long at, int i)
{
	if (pthread_mutex_lock(&philo[i].mtx.dead) != 0)
		return (1);
	at = actual_time(MS);
	if (at - philo[i].last_meals_time > common->time_to_die)
	{
		if (pthread_mutex_lock(&common->mtx_print) != 0)
			return (1);
		ft_putnbr_fd(actual_time(MS) - common->start_time, 1);
		write(1, CLREL, 6);
		write(1, "	Philo № ", 12);
		write(1, CLREL, 6);
		ft_putnbr_fd(philo->id, 1);
		write(1, " ", 2);
		write(1, "died at ", 9);
		ft_putnbr_fd(at - philo[i].last_meals_time, 1);
		write(1, " ms of life", 12);
		write(1, CLRRD, 6);
		write(1, "| End of simulation!\n", 22);
		write(1, CLRRS, 5);
		return (1);
	}
	if (pthread_mutex_unlock(&philo[i].mtx.dead) != 0)
		return (1);
	return (0);
}

int	check_full(t_data *common, int finished_eating)
{
	if (finished_eating == common->num_of_philos)
	{
		if (pthread_mutex_lock(&common->mtx_print) != 0)
			return (1);
		ft_putnbr_fd(actual_time(MS) - common->start_time, 1);
		write(1, CLREL, 6);
		write(1, "	Philos are FULL", 17);
		write(1, "	", 2);
		write(1, CLRGR, 6);
		write(1, "| End of simulation!\n", 22);
		write(1, CLRRS, 5);
		return (1);
	}
	return (0);
}

int	check_life(t_life *philo, t_data *common)
{
	int		finished_eating;
	int		i;
	long	at;

	at = 0;
	while (1)
	{
		i = 0;
		finished_eating = 0;
		while (i < common->num_of_philos)
		{
			if (check_death(philo, common, at, i))
				return (1);
			if (philo->cmn->num_of_meals != UNLIMITED && \
					philo[i].meal_count >= philo[i].cmn->num_of_meals)
				finished_eating++;
			i++;
		}
		if (check_full(common, finished_eating))
			return (1);
	}
	return (0);
}

void	free_and_destroy(t_life *philo)
{
	int	num;

	num = -1;
	while (++num < philo->cmn->num_of_philos)
	{
		pthread_mutex_destroy(&philo[num].mtx.l_fork);
		pthread_mutex_destroy(&philo[num].mtx.dead);
	}
	pthread_mutex_destroy(&philo[num].cmn->mtx_print);
	free(philo);
}

int	main(int argc, char *argv[])
{
	t_data	common;
	t_life	*philo;

	ft_bzero(&common, sizeof(t_data));
	if (argumint_paser(argc, argv))
		if (print_error (argumint_paser(argc, argv)))
			return (argumint_paser(argc, argv));
	if (init_commom_param(&common, argv))
		return (1);
	philo = init_phillo_data(&common);
	if (!philo)
		return (1);
	if (init_threads(philo, &common))
		return (1);
	if (check_life(philo, &common))
		return (1);
	free_and_destroy(philo);
	return (0);
}
