/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:53:35 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/16 16:31:13 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <termios.h>

/********LOCAL_INCLUDES*********/
# include "functions.h"
# include "structure.h"

/********READLINE*********/
# include <readline/history.h>
# include <readline/readline.h>

/**********WAIT***********/
# include <sys/wait.h>

/**********ERROR***********/
# include <errno.h>

/*********SIGNALS**********/
# include <signal.h>

/**********LIBFT***********/

# include "../libft/ft_printf/ft_printf.h"
# include "../libft/gnl/get_next_line.h"
# include "../libft/libft.h"

#endif
