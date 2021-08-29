/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_input_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feschall <feschall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 13:32:12 by feschall          #+#    #+#             */
/*   Updated: 2021/08/24 17:28:54 by feschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		if (ft_atoi(argv[i]) > 1000000 || ft_strlen(argv[i]) > 7)
			return (4);
	}
	if (argc == 6 && ft_atoi(argv[5]) == 0)
		return (5);
	return (0);
}

int	print_error_end_free(int errno, t_data *common)
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
	else if (5 < errno && errno < 9)
	{
		printf("\033[31mMemory allocation error!\033[0m\n");
		if (errno == 7)
			free(common->pid);
		if (errno == 8)
			free(common->deaths);
	}
	else if (errno == 9)
		printf("\033[31mThe semaphore is not initialized!\033[0m\n");
	if (errno > 0)
		return (1);
	return (0);
}
