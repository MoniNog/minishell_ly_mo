/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_search_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:07:29 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 20:48:34 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env	*search_env_name(t_env *env, char *name)
{
	t_env	*current;
	t_env	**return_env;

	current = env;
	while (current != NULL && ft_strncmp(current->name, name, ft_strlen(name)
			+ 1) != 0)
		current = current->next;
	if (current == NULL)
		return (NULL);
	return_env = &current;
	return (*return_env);
}

char	*search_env_value(t_env *env, char *name)
{
	t_env	*var;

	var = search_env_name(env, name);
	if (!var || !var->value)
		return (NULL);
	return (var->value);
}
