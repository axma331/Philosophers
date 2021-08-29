/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_input_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feschall <feschall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 13:32:12 by feschall          #+#    #+#             */
/*   Updated: 2021/08/29 07:19:20 by feschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_digit(char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] == '+' && (ft_isdigit(argv[i][j + 1])))
				continue ;
			if (!(ft_isdigit(argv[i][j])))
				return (2);
		}
	}
	return (0);
}

int	argumint_paser(int argc, char *argv[])
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	if (check_digit(argv))
		return (2);
	i = 0;
	while (argv[++i])
	{
		if (ft_atoi(argv[1]) > 200 || ft_strlen(argv[1]) > 3)
			return (3);
		if (ft_atoi(argv[i]) > 10000 || ft_strlen(argv[i]) > 5)
			return (4);
	}
	if (argc == 6 && ft_atoi(argv[5]) == 0)
		return (5);
	return (0);
}

int	print_error(int errno)
{
	if (errno == 1)
		printf("\033[31mIncorrect count of input arguments!\033[0m\n");
	else if (errno == 2)
		printf("\033[31mIncorrect value of input arguments!\033[0m\n");
	else if (errno == 3)
		printf("\033[31mPhilo value is too large!\033[0m\n");
	else if (errno == 4)
		printf("\033[31mThe argument value is too large!\033[0m\n");
	else if (errno == 5)
		printf("\033[31mNothing to eat!\033[0m\n");
	if (errno > 0)
		return (1);
	return (0);
}

int	init_commom_param(t_data *common, char *argv[])
{
	common->num_of_philos = ft_atoi(argv[1]);
	common->time_to_die = ft_atoi(argv[2]);
	common->time_to_eat = ft_atoi(argv[3]);
	common->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		common->num_of_meals = ft_atoi(argv[5]);
	else
		common->num_of_meals = UNLIMITED;
	if (pthread_mutex_init(&common->mtx_print, NULL))
		return (1);
	return (0);
}

t_life	*init_phillo_data(t_data *common)
{
	t_life	*philo;
	int		num;

	philo = ft_calloc(common->num_of_philos, sizeof(t_life));
	if (!philo)
		return (NULL);
	num = -1;
	while (++num < common->num_of_philos)
	{
		philo[num].id = num + 1;
		if (num % 2 != 0)
			philo[num].priority = true;
		if (num == common->num_of_philos - 1)
			philo[num].mtx.r_fork = &philo[0].mtx.l_fork;
		else
			philo[num].mtx.r_fork = &philo[num + 1].mtx.l_fork;
		if (pthread_mutex_init(&philo[num].mtx.l_fork, NULL) != 0)
			return (NULL);
		if (pthread_mutex_init(&philo[num].mtx.dead, NULL) != 0)
			return (NULL);
		philo[num].cmn = common;
	}
	return (philo);
}
