/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feschall <feschall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:34:47 by feschall          #+#    #+#             */
/*   Updated: 2021/08/27 10:33:43 by feschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_putchar_fd(char c, int fd)
{
	unsigned int	ch;

	ch = c;
	write(fd, &ch, 1);
}

void	ft_putnbr_fd(long long int n, int fd)
{
	unsigned long long int	num;

	if (n < 0)
		ft_putchar_fd('-', fd);
	if (n < 0)
		num = -n;
	else
		num = n;
	if (num >= 10)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putnbr_fd(num % 10, fd);
	}
	else
		ft_putchar_fd(num + '0', fd);
}

long	actual_time(int converter)
{
	struct timeval	t;
	long			time;

	gettimeofday(&t, NULL);
	time = t.tv_sec * converter + t.tv_usec / (US / converter);
	return (time);
}

void	downtime(long waiting_time)
{
	long	waiting_start_time;

	waiting_start_time = actual_time(US);
	while (actual_time(US) - waiting_start_time < waiting_time)
		usleep(10);
}

void	ft_usleep(long sleep_start_time, long sleep_time)
{
	while (actual_time(MS) < sleep_start_time + sleep_time)
		usleep(50);
}

// void	ft_usleep(long sleep_start_time, long sleep_time)
// {
// 	while (actual_time(MS) - sleep_start_time < sleep_time)
// 		usleep(50);
// }