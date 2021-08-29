/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feschall <feschall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:34:47 by feschall          #+#    #+#             */
/*   Updated: 2021/08/29 06:49:28 by feschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	print_msg(t_life *philo, char *msg)
{
	if (pthread_mutex_lock(&philo->cmn->mtx_print) != 0)
		return (1);
	ft_putnbr_fd((actual_time(MS) - philo->cmn->start_time), 1);
	write(1, "	Philo # ", 9);
	ft_putnbr_fd(philo->id, 1);
	write(1, msg, ft_strlen(msg));
	if (pthread_mutex_unlock(&philo->cmn->mtx_print) != 0)
		return (1);
	return (0);
}

long	actual_time(int converter)
{
	struct timeval	t;
	long			time;

	gettimeofday(&t, NULL);
	time = t.tv_sec * converter + t.tv_usec / (US / converter);
	return (time);
}

void	ft_usleep(long sleep_start_time, long sleep_time)
{
	while (actual_time(MS) < sleep_start_time + sleep_time)
		usleep(50);
}
