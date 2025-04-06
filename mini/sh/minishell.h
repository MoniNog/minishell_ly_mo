/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:41:45 by lylrandr          #+#    #+#             */
/*   Updated: 2025/04/05 18:18:56 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft.h"
# include <signal.h>
# include <termios.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stddef.h>
# include <stdbool.h>

#  define TRUE 1
#  define FALSE 0

// signals.c
__sighandler_t handler_sigint(void);
void init_signals(void);
void restore_terminal(void);

typedef enum s_token_type
{
	T_CMD,
	T_CMD_ARG,
	T_ARG,
	T_FILE,
	T_OP,
	T_PIPE,
	T_WORD
}			t_token_type;



typedef struct s_input
{
	char			*token;
	t_token_type	type;
	struct s_input	*next;
	struct s_input	*prev;
	struct s_data	*data;
}					t_input;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_input		*input;// ligne de commande
	t_env		*env;// tableau envp
	char		**copy_env;
	int			exit_status;
}				t_data;

// FONCTIONS LYLAH
// fonctions parsing
char	**fill_tab(char *input, char **array);
void	if_n_op(char *input, char **array, int *k, int *i);
void	if_operator(char *input, char **array, int *k, int i);
int		word_len(char *input);
char	**first_parsing(char *input);
char	**second_parsing(char **array);
void	first_word(char **input, char **env);
char	**parse_input(char *input);
char	**fill_second_tab(char **array, char **tab_token);
int		handle_non_operator(char **tab_token, char *array, int *index);
void	handle_operator(char **tab_token, char **array, int *index, int i);
void	if_quotes(char *input, char **array, int *k, int *i);
int		while_quotes(char *input, int i);
char	**malloc_second_parsing(int len);
int		is_open_quotes(char *input);
void	is_env_var(t_input *input);
char	*handle_quoted_token(char *quoted_str);
void	print_token_list(t_input *head);
char	*handle_double_quote(char *str, int *i);
char	*handle_env_variable(char *str, int *i);
char	*extract_plain_text(char *str, int *i);
char	*expand_token_string(const char *src);
char	*extract_var_name(const char *str, int *i);


// fonctions token

int				is_cmd(char *token, char **env);
t_input			*tokenize(char **input);
t_token_type	get_token_type(t_input *token, char *input);
void			is_cmd_arg(t_input *token);
//int			num_var(t_input *token);
void			parse_and_expand_token(t_input *token);
char			*handle_single_quote(char *str, int *i);

//fonctions exit code

void	get_exit_code(void);

// fonctions path
char	**ft_split_path(char *fullpath);
char	*ft_find_executable(char **path, char *cmd);
char	*ft_get_path(char *fullpath, char *cmd);
char	*ft_get_env_path(char **env);

//fonctions main [ ] a renommer
void	print_token_type(t_input *token);
void	print_all_token_types(t_input *head);
void	print_tokens(char **tokens);

// FONCTIONS EXEC + MONI

///built-in
void	b_cd(t_data *data, t_input *arg);
void	b_echo(t_input *input);
void	b_env(t_data *data);
void	b_exit(t_data *data);
void	b_export(t_data *data);
void	b_pwd(void);
void	b_unset(t_data *data);

int	kind_of_token(t_data *data, t_input *input);


// init_environment // b_export
void    free_lle(t_data *data);
void    print_lle(t_data *data);
t_env   *create_lle(char **envp);
void    swap_words(char **a, char **b);
int     compare_words(char *w1, char *w2);
void    sort_words(char **words, int len);
void    print_copy_env(t_data *data);
void    create_env_copy_array(t_data *data);
int     get_array_length(char **array);
bool    is_valid_env_var_syntax(char *s);
void    b_export(t_data *data);
void    init_env(t_data *data, char **envp);
void	add_env_var(t_data *data, char *input);
t_env	*exist_already_in_env(t_env *env, char *name_var);


// // init_arg
// void init_input(t_input *input);

// utils.c
void	cleanup_memory(char *line, char **splited_line);
char	*ft_strdup_equal(const char *src);
size_t	ft_strcat(char *dest, const char *src);
int		ft_strncmp_end(char *s1, char *s2, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strcpy(char *dest, const char *src);
t_input	*cat_token(t_input *token, char *value, int len);

// signals.c
__sighandler_t	handler_sigint(void);
void	init_signals(void);
void	restore_terminal(void);

//UTILS/lle
void	lle_add_back(t_env **env, t_env *new1);
void	lle_add_front(t_env **env, t_env *new1);
void	lle_clear(t_env **env, void (*del)(void *));
void	lle_del_one(t_env *env, void (*del)(void *));
void	lle_iter(t_env *env, void (*f)(void *));
t_env	*lle_last(t_env *env);
t_env	*lle_map(t_env *env, void *(*f)(void *), void (*del)(void *));
t_env	*lle_new(void *content);
int		lle_size(t_env *env);
// content devient name par defaut, a adapter si beosin










#endif
