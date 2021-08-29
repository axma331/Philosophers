/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_proces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feschall <feschall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 18:06:14 by feschall          #+#    #+#             */
/*   Updated: 2021/08/27 11:07:11 by feschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_phillo(t_life *philo, t_data *common)
{
	int		num;

	num = -1;
	common->start_time = actual_time(MS);
	philo->last_meals_time = common->start_time;
	while (++num < common->num_of_philos)
	{
		philo->id = num + 1;
		philo->death = common->deaths[num];
		common->pid[num] = fork();
		if (common->pid[num] == -1)
			close_and_destroy(common);
		if (common->pid[num] == 0)
			lifetime(philo);
	}
	sem_post(common->start);
	check_result(common);
}

void	check_result(t_data *common)
{
	int		status;
	int		finished_eating;

	status = 0;
	finished_eating = 0;
	while (true)
	{
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (status == DEAD)
			close_and_destroy(common);
		else if (status == FULL)
			check_full(common, ++finished_eating);
	}
}

void	check_full(t_data *common, int finished_eating)
{
	if (finished_eating == common->num_of_philos)
	{
		sem_wait (common->print);
		ft_putnbr_fd(actual_time(MS) - common->start_time, 1);
		write(1, CLREL, 5);
		write(1, "	Philos are FULL	", 17);
		write(1, CLRGR, 5);
		write(1, "| End of simulation!\n", 21);
		write(1, CLRRS, 4);
		close_and_destroy(common);
	}
}

void	init_threads(t_life *philo)
{
	sem_wait(philo->cmn->start);
	sem_post(philo->cmn->start);
	philo->last_meals_time = actual_time(MS);
	if (pthread_create(&philo->tid, NULL, (void *)&check_death, \
												(void *)philo) != 0)
		exit (OTHER);
}

void	lifetime(t_life *philo)
{
	init_threads(philo);
	while (true)
	{
		sem_wait(philo->cmn->priority);
		sem_wait(philo->cmn->fork);
		print_msg(philo, " takes left forks\n");
		sem_wait(philo->cmn->fork);
		sem_post(philo->cmn->priority);
		print_msg(philo, " takes right forks\n");
		sem_wait(philo->death);
		philo->last_meals_time = actual_time(MS);
		sem_post(philo->death);
		print_msg(philo, " eating\n");
		philo->meal_count++;
		ft_usleep(philo->last_meals_time, philo->cmn->time_to_eat);
		sem_post(philo->cmn->fork);
		sem_post(philo->cmn->fork);
		if (philo->cmn->num_of_meals != UNLIMITED && \
				philo->meal_count == philo->cmn->num_of_meals)
			exit (FULL);
		print_msg(philo, " sleeping\n");
		ft_usleep(philo->last_meals_time + philo->cmn->time_to_eat, \
											philo->cmn->time_to_sleep);
		print_msg(philo, " thinking\n");
	}
}
