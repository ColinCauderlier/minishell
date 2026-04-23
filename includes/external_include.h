/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_include.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:53:35 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/20 18:06:09 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXTERNAL_INCLUDE_H
# define EXTERNAL_INCLUDE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

/********READLINE*********/
# include <readline/readline.h>
# include <readline/history.h>

/**********WAIT***********/
# include <sys/wait.h>

/**********ERROR***********/
# include <errno.h>

#endif
