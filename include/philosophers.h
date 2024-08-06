/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:51:22 by wkeiser           #+#    #+#             */
/*   Updated: 2024/07/02 14:51:25 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define SUCCESS 0
# define ERROR 1

# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	struct s_info	*info;
	pthread_t		t1;
	int				id;
	int				eat_count;
	int				dont_eat;
	int				priority;
	u_int64_t		last_meal_time;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	eat_count_mutex;
	pthread_mutex_t	last_meal_time_mutex;
}					t_philo;

typedef struct s_info
{
	pthread_t		*th;
	int				philo_num;
	int				must_eat;
	int				dead;
	int				d2;
	int				too_bad_no_death;
	int				finish_count;
	int				flag;
	int				init_count_forks;
	t_philo			*philos;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	finish_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	write;
}					t_info;

// action
void				eat(t_philo *philo);
void				think(t_philo *philo);
void				exec_philosophers(t_info info);
void				sleep_philo(t_philo *philo);
void				*work(void *philo_ptr);

// set
int					set_param(t_info *info, int argc, char **argv);
t_philo				*set_philosopher(int num, t_info info);
int					initialize_philos(t_info *info);
void				start_simulation(int argc, char **argv, t_info *info);
int					pthread_wfd_init(t_info *info);
void				set_philosopher_param(t_philo *philo, t_info *info, int i);
void				*monitor(void *info_ptr);
int					monitor_count(t_philo *philo);
int					monitor_finish(t_philo philo);

// print
void				print(t_philo *philo, char *action);
void				error_print(int error);

// utils
unsigned long		get_time(void);
void				pick_up_forks(t_philo *philo);
void				put_down_forks(t_philo *philo);
void				print(t_philo *philo, char *action);

// clear and checkings
void				handle_error(const char *message, t_info *info);
void				pthread_mutex_destroy_safe(pthread_mutex_t *mutex);
void				clear_data(t_info *info);
void				check_pthread_error(int ret, const char *msg);
void				clearing(t_info *info);
int					range_nb_check(long nb);
int					size_check(long nb);
int					num_check(char *str);
int					check_nb_philo(long nb);
int					all_philos_satisfied(t_info *info);
int					error_check(int argc, char **argv);
int					check_death_and_timeout(t_philo *philo);
int					check_all_satisfied(t_philo *philo);
void				set_dead_and_break(t_philo *philo);

// other
long				ft_atol(const char *str);

#endif