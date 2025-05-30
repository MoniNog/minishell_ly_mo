/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:39:34 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/22 13:29:37 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**first_parsing(t_data *data, char *input)
{
	int		len;

	len = count_tokens(input);
	data->array = malloc(sizeof(char *) * (len + 1));
	if (!data->array)
	{
		perror("first_parsing");
		return (NULL);
	}
	data->array[len] = NULL;
	return (fill_tab(data, input));
}

int	word_len(char *input)
{
	int		i;
	int		in_quote;
	char	quote_char;

	i = 0;
	in_quote = 0;
	quote_char = 0;
	while (input[i])
	{
		if (quotes(input, &i, &in_quote, &quote_char))
			continue ;
		if (!in_quote && (input[i] == ' ' || input[i] == '|' || input[i] == '<'
				|| input[i] == '>'))
			break ;
		i++;
	}
	return (i);
}

void	if_operator(char *input, char **array, int *k, int i)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (input[*k + len] == '|' || input[*k + len] == '<' || input[*k
			+ len] == '>')
		len++;
	array[i] = malloc(sizeof(char) * (len + 1));
	if (!array[i])
		return ;
	while (input[*k] == '|' || input[*k] == '<' || input[*k] == '>')
	{
		array[i][j] = input[*k];
		j++;
		(*k)++;
	}
	array[i][j] = '\0';
}

void	if_n_op(t_data *data, char *input, int *k, int *i)
{
	int		k_j[2];
	int		in_quote;
	char	quote_char;

	k_j[0] = *k;
	k_j[1] = 0;
	in_quote = 0;
	quote_char = 0;
	while (input[k_j[0]] && !(input[k_j[0]] == ' ' && !in_quote)
		&& !(input[k_j[0]] == '|' && !in_quote)
		&& !(input[k_j[0]] == '<' && !in_quote)
		&& !(input[k_j[0]] == '>' && !in_quote))
	{
		if (input[k_j[0]] == '$')
			expand_env_var_into_array(data, input, &data->array[*i], k_j);
		else if (quotes(input, &k_j[0], &in_quote, &quote_char))
			continue ;
		else
			copy_single_char(input, data->array, k_j, *i);
	}
	data->array[*i][k_j[1]] = '\0';
	*k = k_j[0];
}

char	**fill_tab(t_data *data, char *input)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	data->array[i] = NULL;
	while (input[k])
	{
		while (input[k] == ' ')
			k++;
		if (!input[k])
			break ;
		if (input[k] == '\'' || input[k] == '"')
			if_quotes(input, data->array, &k, &i);
		else if (input[k] == '|' || input[k] == '<' || input[k] == '>')
			if_operator(input, data->array, &k, i);
		else if (!handle_normal_word(data, input, &k, i))
			return (NULL);
		i++;
	}
	data->array[i] = NULL;
	return (data->array);
}
