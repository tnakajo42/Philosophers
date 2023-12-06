/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:20:50 by tnakajo           #+#    #+#             */
/*   Updated: 2023/12/06 18:07:24 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>   // for memset
# include <stdio.h>    // for printf
# include <stdlib.h>   // for malloc, free
# include <unistd.h>   // for write, usleep
# include <sys/time.h> // for gettimeofday
# include <pthread.h>  // for pthread

/* struct */
/**
 * 	p_no  : philo's identigy number
 * 	status: 
 * 		T -> ready to think
 * 		t -> is thinking 
 * 		S -> ready to sleep
 * 		s -> is sleeping 
 * 		E -> ready to eat
 * 		e -> is eating
 * 		D -> ready to die
 * 	eat_times: philo's times to eat at the restaurant
 * 	time: philo's time to do next action 
 * 	life: philo's time to die
*/
typedef struct s_status
{
	unsigned int	p_no;
	char			status;
	int				eat_times;
	unsigned int	time;
	unsigned int	life;
	unsigned int	init_time;
	pthread_mutex_t	status_mutex;
	pthread_t		threads;
}				t_status;

/**
 * 	nofu: number of forks in use
*/
typedef struct s_fork
{
	int				nofiu;
	pthread_mutex_t	status_mutex;
	pthread_t		fork_threads;
}				t_fork;

/**
 * 	ttd : time to die
 * 	tte : time to eat
 * 	tts : time to sleep
 * 	nom : number of meals
 * 	nofp: number of full philo
*/
typedef struct s_philo
{
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				nom;
	int				nofp;
	t_status		*status;
	t_fork			*fork;
	unsigned int	time;
	unsigned int	init_time;
}				t_philo;

/**
 * 	tv_sec : seconds
 * 	tv_usec: microseconds
*/
typedef struct s_timeval {
	time_t		tv_sec;
	suseconds_t	tv_usec;
}				t_timeval;

/* utils */
int		init_philo(t_philo *philo, char **argv, int i);
void	*ft_thread(void *arg);
int		ph_atoi(const char *nptr);
time_t	get_time(void);
void	*ft_thread(void *arg);

/* open restaurant */
void	open_restaurant(t_philo *ph, int i, int j);
int		serve_food(t_philo *ph, int i, int j);
int		what_philo_do(t_philo *ph, int i);
int		print_status(t_philo *ph, int i, int j);
void	*fork_thread(void *arg);
void	take_two_forks(t_philo *ph, int i);

#endif
