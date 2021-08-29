/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feschall <feschall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 13:32:41 by feschall          #+#    #+#             */
/*   Updated: 2021/08/29 07:32:56 by feschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <stdbool.h>

# define	CLRRS	"\033[0m"
# define	CLRRD	"\033[31m"
# define	CLRGR	"\033[32m"
# define	CLREL	"\033[33m"

# define	US			1000000
# define	MS			1000
# define	UNLIMITED	-1
# define	DEAD		1
# define	FULL		2
# define	OTHER		3

# define	PRIORITY	"/priority"
# define	PRINT		"/print"
# define	DEATH		"/dead"
# define	FORK		"/fork"
# define	START		"/start"

typedef struct s_data
{
	int				num_of_philos;
	int				num_of_meals;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pid_t			*pid;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*start;
	sem_t			*priority;
	sem_t			**deaths;
	char			**deaths_names;
}					t_data;

typedef struct s_life
{
	long			last_meals_time;
	int				meal_count;
	int				id;
	bool			full;
	sem_t			*death;
	pthread_t		tid;
	t_data			*cmn;
}					t_life;

int		argumint_paser(int argc, char *argv[]);
int		check_digit(char *argv[]);
int		print_error_end_free(int errno, t_data *common);
int		init_commom_param(t_life *philo, t_data *common, char *argv[]);
int		create_deaths_names(t_data *common);
int		init_sem(t_data *common);
long	actual_time(int converter);
void	downtime(long waiting_time);
void	ft_usleep(long sleep_start_time, long sleep_time);
void	create_phillo(t_life	*philo, t_data *common);
void	check_result(t_data *common);
void	check_full(t_data *common, int finished_eating);
void	lifetime(t_life *philo);
void	init_threads(t_life *philo);
void	*check_death(t_life *philo);
void	close_and_destroy(t_data *common);
void	print_msg(t_life *philo, char *activ);

int		ft_isdigit(int c);
int		ft_strlen(const char *str);
int		ft_atoi(const char *s);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(long long int n, int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

#endif
