/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:47:30 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/28 15:23:28 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structure.h"

/********TOKENIZER*********/
void	tokenize(char *prompt, char **envp);
t_token	*get_content(char *s);
int		ft_isspace(char c);
int		ft_isquote(char c);
void	free_res(t_token *res, int pos_res);

/********BUILT*IN**********/
void	pwd(void);

#endif
