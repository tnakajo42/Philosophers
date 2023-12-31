/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:20:50 by tnakajo           #+#    #+#             */
/*   Updated: 2023/11/28 19:31:55 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <string.h>    // for memset
# include <stdio.h>     // for printf
# include <stdlib.h>    // for malloc, free, exit
# include <unistd.h>    // for write, usleep, fork
# include <sys/time.h>  // for gettimeofday, waitpid
# include <pthread.h>   // for pthread
# include <signal.h>    // kill
# include <semaphore.h> // for semaphores (sem_open, sem_close, sem_unlink)
# include <fcntl.h>     // for O_CREAT

/**
 * MUTEX	-> SEMAPHORE
 * blocking mechanism		-> signaling mechanism
 * pthread_mutex_init()		-> sem_open()
 * pthread_mutex_lock()		-> sem_wait()
 * pthread_mutex_unlock()	-> sem_post()
 * pthread_mutex_destroy()	-> sem_close() + sem_unlink()
*/

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
 * 	time: philo's time to do next action 
 * 	life: philo's time to die
 * 	eat_times: philo's times to eat at the restaurant
*/
typedef struct s_status
{
	unsigned int	p_no;
	char			status;
	unsigned int	time;
	unsigned int	life;
	int				eat_times;
}				t_status;

/**
 * 	nof : number of forks
 * 	nofu: number of forks in use
*/
typedef struct s_fork
{
	int				nof;
	int				nofiu;
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
	sem_t			*sem;
	pthread_mutex_t	main_process;
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

/* open restaurant bonus*/
void	open_restaurant_bonus(t_philo *ph);
int		serve_food(t_philo *ph, int i);
int		what_philo_do(t_philo *ph, int i);
int		print_status(t_philo *ph, int i);
void	take_two_forks_from_middle_of_the_table(t_philo *ph, int i);

#endif
