/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:17:21 by jroseiro          #+#    #+#             */
/*   Updated: 2024/10/29 21:03:00 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../e_execute.h"

// TODO:

/*
** a "checker":
**
** is_valid_identifier - Checks if name is a valid environment variable name
** Same rules as export: [a-zA-Z_][a-zA-Z0-9_]*
*/

/*
** A function to do the actual removing / 'unseting'
**
** remove_env_var - Removes variable from environment list if found
** Returns EXIT_SUCCESS even if variable wasn't found (bash behavior)
*/

/*
** A mini 'main' function to manage it all:
**
** builtin_unset - Implements the unset command
** Removes variables from environment
** Returns 0 on success, 1 if any argument is invalid
*/