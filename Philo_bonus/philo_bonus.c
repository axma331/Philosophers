/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feschall <feschall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 13:32:30 by feschall          #+#    #+#             */
/*   Updated: 2021/08/29 07:16:50 by feschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_commom_param(t_life *philo, t_data *common, char *argv[])
{
	ft_bzero(common, sizeof(t_data));
	ft_bzero(philo, sizeof(t_life));
	common->num_of_philos = ft_atoi(argv[1]);
	common->time_to_die = ft_atoi(argv[2]);
	common->time_to_eat = ft_atoi(argv[3]);
	common->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		common->num_of_meals = ft_atoi(argv[5]);
	else
		common->num_of_meals = UNLIMITED;
	common->pid = (pid_t *)ft_calloc(common->num_of_philos + 1, sizeof(pid_t));
	if (!common->pid)
		return (6);
	common->deaths = (sem_t **)ft_calloc(common->num_of_philos + 1, \
															sizeof(sem_t *));
	if (!common->deaths)
		return (7);
	common->deaths_names = (char **)ft_calloc(common->num_of_philos + 1, \
															sizeof(char *));
	if (!common->deaths_names)
		return (8);
	if (init_sem(common))
		return (9);
	philo->cmn = common;
	return (0);
}

int	init_sem(t_data *common)
{
	if (create_deaths_names(common))
		return (1);
	sem_unlink(FORK);
	common->fork = sem_open(FORK, O_CREAT | O_EXCL, 660, common->num_of_philos);
	if (common->fork == NULL)
		return (1);
	sem_unlink(PRIORITY);
	common->priority = sem_open(PRIORITY, O_CREAT | O_EXCL, 660, 1);
	if (common->priority == NULL)
		return (1);
	sem_unlink(PRINT);
	common->print = sem_open(PRINT, O_CREAT | O_EXCL, 660, 1);
	if (common->print == NULL)
		return (1);
	sem_unlink(START);
	common->start = sem_open(START, O_CREAT | O_EXCL, 660, 0);
	if (common->start == NULL)
		return (1);
	return (0);
}

int	create_deaths_names(t_data *common)
{
	int		num;
	char	*name;

	num = common->num_of_philos;
	while (num--)
	{
		name = ft_itoa(num);
		common->deaths_names[num] = ft_strjoin(DEATH, name);
		sem_unlink(common->deaths_names[num]);
		common->deaths[num] = sem_open(common->deaths_names[num], \
													O_CREAT | O_EXCL, 660, 1);
		free (name);
		if (common->deaths[num] == NULL)
			return (1);
	}
	return (0);
}

void	close_and_destroy(t_data *common)
{
	int	num;

	num = common->num_of_philos;
	while (num--)
		kill(common->pid[num], SIGKILL);
	num = common->num_of_philos;
	while (num--)
	{
		sem_close(common->deaths[num]);
		sem_unlink(common->deaths_names[num]);
	}
	sem_close(common->fork);
	sem_unlink(FORK);
	sem_close(common->priority);
	sem_unlink(PRIORITY);
	sem_close(common->print);
	sem_unlink(PRINT);
	sem_close(common->start);
	sem_unlink(START);
	while (common->num_of_philos--)
		free(common->deaths_names[common->num_of_philos]);
	free(common->deaths);
	free(common->pid);
	exit (0);
}

int	main(int argc, char *argv[])
{
	t_data	common;
	t_life	philo;
	int		ret;

	ret = argumint_paser(argc, argv);
	if (print_error_end_free (ret, &common))
		return (ret);
	ret = init_commom_param(&philo, &common, argv);
	if (print_error_end_free (ret, &common))
		return (ret);
	create_phillo(&philo, &common);
	return (0);
}
