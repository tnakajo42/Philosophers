/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:58:30 by tnakajo           #+#    #+#             */
/*   Updated: 2023/12/06 18:10:10 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo		*ph;
	int			i;

	i = -1;
	ph = (t_philo *)malloc(sizeof(t_philo));
	if (ph == NULL || (ac < 5 || ac > 6))
		return (printf("Failed to allocate memory or arguments error\n"));
	if (!init_philo(ph, av, -1))
	{
		while (++i < ph->nop)
		{
			pthread_mutex_init(&ph->status[i].status_mutex, NULL);
			pthread_create(&ph->status[i].threads, NULL, \
				ft_thread, &ph->status[i]);
			pthread_mutex_init(&ph->fork[i].status_mutex, NULL);
			pthread_mutex_lock(&ph->fork[i].status_mutex);
			pthread_create(&ph->fork[i].fork_threads, NULL, \
				ft_thread, &ph->status[i]);
		}
		open_restaurant(ph, -1, -1);
	}
	free(ph->status);
	free(ph->fork);
	free(ph);
	return (0);
}
/* Below program is not needed ...!!
	i = -1;
	while (++i < ph->nop)
	{
		pthread_mutex_destroy(&ph->status[i].status_mutex);
		pthread_mutex_destroy(&ph->fork[i].status_mutex);
	}
*/

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
	philo->init_time = get_time();
	philo->time = 0;
	while (++i < philo->nop)
	{
		philo->status[i].p_no = i + 1;
		if ((i == 0 || (i % 2 == 0 && i + 1 != philo->nop)) && philo->nop != 1)
			philo->status[i].status = 'E';
		else
			philo->status[i].status = 'T';
	}
	return (0);
}

void	*ft_thread(void *arg)
{
	t_status	*ph;

	ph = (t_status *) arg;
	if (ph->status == 'T')
	{
		printf("%u %u is thinking\n", ph->init_time, ph->p_no);
		ph->status = 't';
	}
	else if (ph->status == 'S')
	{
		printf("%u %i is sleeping\n", ph->init_time, ph->p_no);
		ph->status = 's';
	}
	else if (ph->status == 'E')
	{
		ph->status = 'e';
		printf("%u %i has taken a fork\n", ph->time, ph->p_no);
		printf("%u %i has taken a fork\n", ph->time, ph->p_no);
		printf("%u %i is eating\n", ph->init_time, ph->p_no);
	}
	usleep(1);
	return (NULL);
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
