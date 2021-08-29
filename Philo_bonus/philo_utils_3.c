/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feschall <feschall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:34:47 by feschall          #+#    #+#             */
/*   Updated: 2021/08/27 10:32:39 by feschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

static int	count(int n)
{
	int			i;
	long int	j;

	i = 1;
	j = n;
	if (j < 0)
	{
		j = -j;
		i++;
	}
	while (j > 9)
	{
		j = j / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	num;
	int			i;

	i = 0;
	str = (char *)malloc(sizeof(char) * count(n) + 1);
	if (!str)
		return (0);
	if (n < 0)
		str[0] = '-';
	num = n;
	if (num < 0)
		num = -num;
	str[count(n) - i++] = '\0';
	while (num > 9)
	{
		str[count(n) - i] = (num % 10) + '0';
		num = num / 10;
		i++;
	}
	str[count(n) - i] = (num % 10) + '0';
	return (str);
}

int	ft_atoi(const char *s)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (s[i] && (('\t' <= s[i] && s[i] <= '\r') || s[i] == ' '))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] && ('0' <= s[i] && s[i] <= '9'))
	{
		num = 10 * num + (s[i] - '0') * sign;
		i++;
	}
	return (num);
}
