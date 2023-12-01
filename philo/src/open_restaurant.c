/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_restaurant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:20:44 by tnakajo           #+#    #+#             */
/*   Updated: 2023/11/27 21:50:31 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	open_restaurant(t_philo *ph)
{
	int				i;

	i = -1;
	ph->fork->nof = ph->nop;
	ph->fork->nofiu = 0;
	ph->nofp = 0;
	pthread_mutex_lock(&ph->status_mutex);
	while (++i < ph->nop)
	{
		ph->status[i].eat_times = 0;
		if ((i == 0 || (i % 2 == 0 && i + 1 != ph->nop)) && ph->nop != 1)
			serve_food(ph, i);
		else
			printf("%i %i is thinking\n", ph->time, i + 1);
	}
	while (42)
	{
		pthread_mutex_unlock(&ph->status_mutex);
		usleep(42);
		ph->time = get_time() - ph->init_time;
		pthread_mutex_lock(&ph->status_mutex);
		if (what_philo_do(ph, -1))
			return ;
	}
}

int	what_philo_do(t_philo *ph, int i)
{
	while (++i < ph->nop)
	{
		if (ph->status[i].status == 'e' && ph->time >= ph->status[i].time)
			ph->status[i].status = 'S';
		else if (ph->status[i].status == 's' && ph->time >= ph->status[i].time)
			ph->status[i].status = 'T';
		else if (ph->status[i].status == 't' && ph->status[i].life <= ph->time)
			ph->status[i].status = 'D';
		else if (ph->status[i].status == 't' && ph->nop != 1)
		{
			if (i == 0 && ph->status[ph->nop - 1].status != 'e' \
				&& ph->status[i + 1].status != 'e')
				ph->status[i].status = 'E';
			else if (i + 1 == ph->nop && ph->status[0].status != 'e' \
				&& ph->status[i - 1].status != 'e')
				ph->status[i].status = 'E';
			else if (i + 1 != ph->nop && ph->status[i + 1].status != 'e' \
				&& i != 0 && ph->status[i - 1].status != 'e')
				ph->status[i].status = 'E';
		}
		if (print_status(ph, i))
			return (1);
	}
	return (0);
}

int	print_status(t_philo *ph, int i)
{
	if (ph->status[i].status == 'D')
	{
		printf("%u %i died\n", ph->time, i + 1);
		pthread_mutex_unlock(&ph->status_mutex);
		return (1);
	}
	if (ph->status[i].status == 'S')
	{
		printf("%u %i is sleeping\n", ph->time, i + 1);
		ph->status[i].status = 's';
		ph->status[i].time = ph->tts + ph->time;
		ph->fork->nofiu = ph->fork->nofiu - 2;
	}
	else if (ph->status[i].status == 'T')
	{
		printf("%u %i is thinking\n", ph->time, i + 1);
		ph->status[i].status = 't';
	}
	if (ph->status[i].status == 'E')
		if (serve_food(ph, i))
			return (1);
	return (0);
}

int	serve_food(t_philo *ph, int i)
{
	ph->status[i].status = 'e';
	take_two_forks(ph, i);
	printf("%u %i is eating\n", ph->time, i + 1);
	ph->status[i].time = ph->tte + ph->time;
	ph->status[i].life = ph->ttd + ph->time;
	ph->status[i].eat_times++;
	if (ph->status[i].eat_times == ph->nom)
		ph->nofp++;
	if (ph->nofp == ph->nop)
	{
		pthread_mutex_unlock(&ph->status_mutex);
		return (1);
	}
	return (0);
}

void	take_two_forks(t_philo *ph, int i)
{
	int	j;

	j = 0;
	while (j < 2)
	{
		if (ph->fork->nofiu < ph->fork->nof)
			printf("%u %i has taken a fork\n", ph->time, i + 1);
		else
			printf("%u %i is looking a fork\n", ph->time, i + 1);
		ph->fork->nofiu++;
		j++;
	}
}
