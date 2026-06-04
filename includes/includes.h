/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:53:35 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/04 17:20:48 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>

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
