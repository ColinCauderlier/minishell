/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:53:35 by ccauderl          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/04/24 11:45:05 by ccauderl         ###   ########.fr       */
=======
/*   Updated: 2026/04/24 15:09:18 by lucinguy         ###   ########.fr       */
>>>>>>> aeb1928e3e868750c19b7e7ce9a3d8138436dddf
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

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
