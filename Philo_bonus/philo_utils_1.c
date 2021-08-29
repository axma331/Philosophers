/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feschall <feschall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:34:47 by feschall          #+#    #+#             */
/*   Updated: 2021/08/27 11:07:39 by feschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(count * size);
	if (mem != NULL)
		ft_bzero(mem, size * count);
	return (mem);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	n;

	i = 0;
	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		str = (char *)malloc(sizeof(char) * (len + 1));
		if (!str)
			return (0);
		i = 0;
		n = 0;
		while (s1[n])
			str[i++] = s1[n++];
		n = 0;
		while (s2[n])
			str[i++] = s2[n++];
		str[i] = '\0';
		return (str);
	}
	return (0);
}

void	print_msg(t_life *philo, char *msg)
{
	sem_wait(philo->cmn->print);
	ft_putnbr_fd((actual_time(MS) - philo->cmn->start_time), 1);
	write(1, "	Philo # ", 9);
	ft_putnbr_fd(philo->id, 1);
	write(1, msg, ft_strlen(msg));
	sem_post(philo->cmn->print);
}

void	*check_death(t_life *philo)
{
	long	at;

	while (true)
	{
		downtime(50);
		sem_wait(philo->death);
		at = actual_time(MS);
		if (at - philo->last_meals_time > philo->cmn->time_to_die)
		{
			sem_wait(philo->cmn->print);
			ft_putnbr_fd(actual_time(MS) - philo->cmn->start_time, 1);
			write(1, CLREL, 5);
			write(1, "	Philo # ", 9);
			ft_putnbr_fd(philo->id, 1);
			write(1, " died at ", 9);
			ft_putnbr_fd(at - philo->last_meals_time, 1);
			write(1, " ms of life", 11);
			write(1, CLRRD, 5);
			write(1, "| End of simulation!\n", 21);
			write(1, CLRRS, 4);
			exit (DEAD);
		}
		sem_post(philo->death);
	}
	return (NULL);
}
