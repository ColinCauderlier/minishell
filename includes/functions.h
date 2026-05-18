/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:47:30 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/18 16:20:02 by lucinguy         ###   ########.fr       */
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
char	*get_expand(char *str, char **envp);
char	*get_type(t_token token);
int		change_state(char c, t_state *state);
int		get_new_content(t_token *list, t_shell *shell);
void	free_split(char **splitted);

/**********EXEX***********/
int		exec(t_shell *shell);
void	free_exec(t_shell *shell);
int		is_redir_wo_word(t_token *tkn);
char	*find_path(char *command, char **envp);
int		check_syntax_shell(t_shell *shell);
void	close_all_pipes(t_shell *shell);
void	free_all_pipes(t_shell *shell);
void	free_commands(char ***commands);
void	execute_command(t_shell *shell, int i);
void	first_cmd(t_shell *shell);
void	last_cmd(t_shell *shell, int i);
void	middle_cmd(t_shell *shell, int i);

/**********ENVP***********/
void	init_envp(t_shell *shell, char **env);
void	update_envp(t_shell *shell, char *var_name, char *var_value);

/********BUILT*IN**********/
int		pwd(void);
int		cd(char *path, t_shell *shell);
int		env(t_shell *shell);

#endif
