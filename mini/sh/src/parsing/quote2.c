/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:13:05 by lylrandr          #+#    #+#             */
/*   Updated: 2025/04/08 16:32:41 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Supprime les '"' ou '\'' qui entourent un token et retourne le contenu sans les quotes
char	*handle_quoted_token(char *quoted_str)
{
	int	len;
	int	j;
	int	i;
	char	*result;

	len = ft_strlen(quoted_str);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (quoted_str[i])
	{
		if (quoted_str[i] == quoted_str[0])
		{
			i++;
			continue;
		}
		result[j++] = quoted_str[i++];
	}
	result[j] = '\0';
	return (result);
}

char	**malloc_second_parsing(int len)
{
	char	**tab_token;

	tab_token = malloc(sizeof(char *) * (len + 1));
	if (!tab_token)
		return (NULL);
	tab_token[len] = NULL;
	return (tab_token);
}

//Stock un token entre quotes + la suite tant qu'il n'y a pas de separateur
void	if_quotes(char *input, char **array, int *k, int *i)
{
	char	quote;
	int		start;
	int		len;
	int		j;

	quote = input[*k];
	start = *k;
	(*k)++;
	while (input[*k] && input[*k] != quote)
		(*k)++;
	if (input[*k] == quote)
		(*k)++;
	while (input[*k] && input[*k] != ' ' && input[*k] != '|' && input[*k] != '<'
		&& input[*k] != '>' && input[*k] != ';' && input[*k] != '&'
		&& input[*k] != '(' && input[*k] != ')')
		(*k)++;
	len = *k - start;
	array[*i] = malloc(sizeof(char) * (len + 1));
	if (!array[*i])
		return ;
	j = 0;
	while (j < len)
	{
		array[*i][j] = input[start + j];
		j++;
	}
	array[*i][j] = '\0';
}

//Parcours un token depuis un guillemet jusqu'a la fin du meme type de guillemet puis copie la suite
//jusqu'a un separateur
int	while_quotes(char *input, int i)
{
	if (input[i] == '\'')
	{
		i++;
		while (input[i] != '\'')
			i++;
	}
	else if (input[i] == '"')
	{
		i++;
		while (input[i] != '"')
			i++;
	}
	while (input[i + 1] != ' ' && input[i + 1] != '|' && input[i + 1] != '<'
		&& input[i + 1] != '>' && input[i + 1])
		i++;
	return (i);
}

int	is_open_quotes(char *input)
{
	int	i;
	int	in_dquote;
	int	in_squote;

	i = 0;
	in_dquote = 0;
	in_squote = 0;
	while (input[i])
	{
		if (input[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (input[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		i++;
	}
	if (in_dquote || in_squote)
		return (1);
	return (0);
}
