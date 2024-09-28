/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:15:35 by gonische          #+#    #+#             */
/*   Updated: 2024/09/29 00:14:37 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_parsing.h"

/**
 * alloc_token - Allocates memory for a token structure and 
 * initializes it with the given type and value.
 * 
 * @param type: The type of the token.
 * @param value: The value associated with the token.
 * 
 * This function uses ft_calloc to allocate memory for a 
 * new token. If the allocation fails, it prints an error 
 * message. The token's type and value are initialized.
 * 
 * @return t_token*: Pointer to the newly allocated token or NULL.
 */
t_token	*alloc_token(t_token_type type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (ft_printf("Calloc error\n"), NULL); // TODO: handle error
	token->type = type;
	token->value = value;
	return (token);
}

/**
 * add_token - Adds a token to the end of a token list.
 * 
 * @param list: A pointer to the head of the token list.
 * @param token: The token to add to the list.
 * 
 * If the list is empty, the token is set as the new head. 
 * Otherwise, it traverses the list and adds the token to 
 * the end.
 */
void	add_token(t_token **list, t_token *token)
{
	t_token	*head;

	if (!token)
		return ;
	if (!list || !*list)
		*list = token;
	else
	{
		head = *list;
		while (head->next)
			head = head->next;
		head->next = token;
	}
}

static t_token	*tokenize(char buffer[])
{
	t_token	*new_token;
	char	*token_value;

	token_value = ft_strdup(&buffer[0]);
	new_token = alloc_token(str_to_token_type(&buffer[0]), token_value);
	return (new_token);
}

t_token	*tokenizer(char *input, t_list *env, t_error *error)
{
	t_token	*tokens;
	char	buffer[ARG_BUFF_SIZE];
	int		buff_index;

	tokens = NULL;
	while (*input && *error == NO_ERROR)
	{
		buff_index = 0;
		if (is_space(*input))
			input += skip_spaces(input);
		else if (is_operator(input))
			input += parse_operator(input, buffer, &buff_index);
		else
			input += parse_word(input, buffer, &buff_index, env, error);
		if (buff_index > 0 && *error == NO_ERROR)
			add_token(&tokens, tokenize(buffer));
	}
	return (tokens);
}

// =========================== DEBUG ONLY =========================== //
/**
 * print_tokens - Prints all tokens in a token list.
 * 
 * @param tokens: The head of the token list to print.
 * 
 * The function iterates through the token list and prints 
 * each token's value using ft_printf.
 */
void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->value)
			ft_printf("%s\n", tokens->value);
		tokens = tokens->next;
	}
}
