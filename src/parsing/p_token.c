/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:15:35 by gonische          #+#    #+#             */
/*   Updated: 2024/09/20 18:37:12 by gonische         ###   ########.fr       */
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

/**
 * dup_token - Duplicates a token and returns a new token with 
 * the same type and value.
 * 
 * @param token: The token to duplicate.
 * 
 * This function allocates memory for a new token, copies its 
 * type and value from the original token, and returns a pointer 
 * to the new token.
 * 
 * @return t_token*: Pointer to the duplicated token.
 */
t_token	*dup_token(t_token *token)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	new_token->next = NULL;
	if (token->value)
		new_token->value = ft_strdup(token->value);
	else
		new_token->value = NULL;
	new_token->type = token->type;
	return (new_token);
}

/**
 * is_redirection - Checks if the given token is a redirection token.
 * 
 * @param token: The token to check.
 * 
 * The function returns true if the token type indicates 
 * a redirection (e.g., T_IN, T_OUT, T_HEREDOC, T_APPEND).
 * 
 * @return bool: true if redirection, false otherwise.
 */
bool	is_redirection(t_token *token)
{
	if (!token)
		return (false);
	return ((token->type == T_IN)
			|| (token->type == T_OUT)
			|| (token->type == T_HEREDOC)
			|| (token->type == T_APPEND));
}

/**
 * is_cmd_separator - Checks if the token is a command separator.
 * 
 * @param token: The token to check.
 * 
 * The function returns true if the token type represents a 
 * command separator like T_PIPE, T_AND, or T_OR.
 * 
 * @return bool: true if separator, false otherwise.
 */
bool	is_cmd_spearator(t_token *token)
{
	if (!token)
		return (false);
	return (token->type == T_PIPE
			|| token->type == T_AND
			|| token->type == T_OR);	
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
