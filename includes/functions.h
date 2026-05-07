/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:47:30 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/07 16:25:07 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structure.h"

/********TOKENIZER*********/
int		tokenize(char *prompt, t_shell *shell);
t_token	*get_content(char *s);
int		ft_isspace(char c);
int		ft_isquote(char c);
int		is_expand_lim(char c);
void	free_res(t_token *res, int pos_res);
void	free_all_tokens(t_shell *shell);
char	*get_expand(char *str, t_envp *envp);
char	*get_type(t_token token);
int		change_state(char c, t_state *state);
int		get_new_content(t_shell *shell);
void	free_split(char **splitted);

/**********EXEC***********/
int		exec(t_shell *shell);
char	*find_path(char *command, char **envp);

/**********ENVP***********/
t_envp	*create_envp_node(char *key, char *value);
void	envp_add_back(t_envp **lst, t_envp *new);
int		parse_env_var(char *env_var, char **key, char **value);
void	free_envp_list(t_envp **envp);
int		append_envp_entry(t_shell *shell, char *key, char *value);

void	init_envp(t_shell *shell, char **envp);

/********BUILT*IN**********/
int		pwd(void);
int		cd(char *path);

#endif
