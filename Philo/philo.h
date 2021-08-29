/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feschall <feschall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 13:32:41 by feschall          #+#    #+#             */
/*   Updated: 2021/08/29 07:30:07 by feschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define	CLRRS	"\033[0m"
# define	CLRRD	"\033[31m"
# define	CLRGR	"\033[32m"
# define	CLREL	"\033[33m"

# define	US			1000000
# define	MS			1000
# define	UNLIMITED	-1

typedef struct s_data
{
	int				num_of_philos;
	int				num_of_meals;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pthread_mutex_t	mtx_print;
}					t_data;

typedef struct s_forks
{
	pthread_mutex_t	dead;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
}					t_forks;

typedef struct s_life
{
	int				id;
	int				priority;
	int				meal_count;
	long			last_meals_time;
	pthread_t		tid;
	t_forks			mtx;
	t_data			*cmn;
}					t_life;

int		argumint_paser(int argc, char *argv[]);
int		check_digit(char *argv[]);
int		print_error(int errno);
int		print_msg(t_life *philo, char *activ);
int		init_commom_param(t_data *common, char *argv[]);
int		init_threads(t_life *philo, t_data *common);
int		check_life(t_life *philo, t_data *common);
int		check_death(t_life *philo, t_data *common, long at, int i);
int		check_full(t_data *common, int finished_eating);
int		takes_forks(t_life *philo);
int		puts_forks(t_life *philo);
long	actual_time(int converter);
void	downtime(long waiting_time);
void	ft_usleep(long sleep_start_time, long sleep_time);
void	free_and_destroy(t_life *philo);
void	*lifetime(t_life *philo);
t_life	*init_phillo_data(t_data *common);

int		ft_isdigit(int c);
int		ft_atoi(const char *s);
int		ft_strlen(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(long long int n, int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

#endif
