/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:10:52 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/21 11:23:14 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	*make_name_eq_value(char *name, char *value)
{
	char	*name_eq;
	char	*name_eq_value;

	name_eq = ft_strjoin(name, "=");
	if (name_eq == NULL)
		return (NULL);
	name_eq_value = ft_strjoin(name_eq, value);
	free(name_eq);
	if (name_eq_value == NULL)
		return (NULL);
	return (name_eq_value);
}

static int	env_count_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->exported)
			i++;
		env = env->next;
	}
	return (i);
}

char	**make_envp(t_env *env)
{
	char	**envp;
	int		len;
	int		i;

	len = env_count_len(env);
	envp = ft_calloc(sizeof(char *), (len + 1));
	if (envp == NULL)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->exported && env->value)
		{
			envp[i] = make_name_eq_value(env->name, env->value);
			if (envp[i++] == NULL)
				ft_free_vector(envp);
		}
		env = env->next;
	}
	return (envp);
}
