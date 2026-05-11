/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:47:30 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/11 17:19:39 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structure.h"

/********TOKENIZER*********/
int			tokenize(char *prompt, t_shell *shell);
t_token		*get_content(char *s);
int			ft_isspace(char c);
int			ft_isquote(char c);
int			is_expand_lim(char c);
void		free_res(t_token *res, int pos_res);
void		free_all_tokens(t_shell *shell);
char		*get_expand(char *str, t_shell *shell);
char		*get_type(t_token token);
int			change_state(char c, t_state *state);
int			get_new_content(t_token *list, t_shell *shell);
void		free_split(char **splitted);

/**********EXEX***********/
int			exec(t_shell *shell);
char		*find_path(char *command, char **envp);

/**********ENVP***********/
void		init_envp(t_shell *shell, char **env);

/********BUILT*IN**********/
int			pwd(void);
int			cd(char *path, t_shell *shell);

#endif
