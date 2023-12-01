/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:58:30 by tnakajo           #+#    #+#             */
/*   Updated: 2023/12/01 22:53:14 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_philo		*philo;
	pthread_t	main_pid;
	int			main_pthread;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		return (printf("Failed to allocate memory for philo\n"));
	main_pthread = pthread_create(&main_pid, NULL, ft_thread, NULL);
	sem_unlink("/status_sem");
	philo->sem = sem_open("/status_sem", O_CREAT, 0660, 1);
	if (main_pthread != 0 || philo->sem == SEM_FAILED || (ac < 5 || ac > 6))
	{
		free (philo);
		return (printf("error creating thread or semaphore init\n"));
	}
	pthread_join(main_pid, NULL);
	init_philo(philo, av, -1);
	free(philo->status);
	free(philo->fork);
	free(philo);
	return (0);
}

void	*ft_thread(void *arg)
{
	usleep(10000);
	return (arg);
}

int	init_philo(t_philo *philo, char **av, int i)
{
	philo->nop = ph_atoi(av[1]);
	philo->ttd = ph_atoi(av[2]);
	philo->tte = ph_atoi(av[3]);
	philo->tts = ph_atoi(av[4]);
	if (av[5])
		philo->nom = ph_atoi(av[5]);
	else
		philo->nom = -1;
	philo->status = (t_status *)malloc(philo->nop * sizeof(t_status));
	philo->fork = (t_fork *)malloc(philo->nop * sizeof(t_fork));
	if (philo->status == NULL || philo->fork == NULL) 
		return (printf("malloc error...!!\n"));
	if (!philo->nop || !philo->ttd || !philo->tte || !philo->tts || !philo->nom)
		return (printf("arguments seem not correct\n"));
	while (++i < philo->nop)
	{
		philo->status[i].p_no = i + 1;
		philo->status[i].status = 't';
		philo->status[i].time = philo->ttd;
		philo->status[i].life = philo->ttd;
	}
	philo->init_time = get_time();
	philo->time = get_time() - philo->init_time;
	open_restaurant_bonus(philo);
	return (0);
}

int	ph_atoi(const char *str)
{
	int						i;
	long long unsigned int	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (result > 2147483647)
		return (0);
	return (result);
}

time_t	get_time(void)
{
	t_timeval	tv;

	if (gettimeofday((struct timeval *)&tv, NULL))
	{
		printf("gettimeofday() Failure\n");
		return (1);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
