/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:55:15 by ihajji            #+#    #+#             */
/*   Updated: 2025/03/07 23:55:15 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_free_vector(char **vector)
{
	int	i;

	i = 0;
	while (vector[i])
		free(vector[i++]);
	free(vector);
	return (NULL);
}
