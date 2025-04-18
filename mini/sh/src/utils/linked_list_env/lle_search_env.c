/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_search_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:07:29 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/18 20:03:58 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief Searches for an environment variable by name in a linked list.
/// @param env Pointer to the head of the linked list of environment variables.
/// @param name The name of the environment variable to search for.
/// @return A pointer to the t_env node containing the variable, or NULL if not found.
t_env	**search_env_name(t_env *env, char *name)
{
	t_env	*current;
	t_env	**return_env;

	current = env;
	while (current != NULL && ft_strcmp(current->name, name) != 0)
		current = current->next;

	return_env = &current;
	return (return_env);
}