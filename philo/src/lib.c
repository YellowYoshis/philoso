#include "philo.h"

long    ft_atol(char *nptr)
{
	long	n;
	long	result;
	int	i;

	i = 0;
	result = 0;
	n = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	while (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			n *= -1;
		i++;
		if (nptr[i] == '-' || nptr[i] == '+')
			return (0);
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		result = (result * 10) + (nptr[i] - 48);
        if (result > INT_MAX || result < INT_MIN) // a voir apres parce que Jo est chiaaaant
            return (0);
		i++;
	}
	return (result * n);
}
