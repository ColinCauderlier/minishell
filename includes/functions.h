/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:47:30 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/19 18:56:59 by ccauderl         ###   ########.fr       */
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
int		is_redir_symbol(char c);
int		is_expand_lim(char c);
void	free_res(t_token *res, int pos_res);
void	free_all_tokens(t_shell *shell);
int		expand(char *old, int *i, char **new, t_shell *shell);
int		change_state(char c, t_state *state);
int		get_new_content(t_token *list, t_shell *shell);
void	free_split(char **splitted);
void	print_tokens(t_shell *shell);

/**********EXEX***********/
int		exec(t_shell *shell);
int		init_exec(t_shell *shell);
void	free_exec(t_shell *shell);
void	free_all_error(t_shell *shell, char **path, int exit_code);
int		is_redir_wo_word(t_token *tkn);
char	*find_path(char *command, char **envp);
int		check_syntax_shell(t_shell *shell);
void	close_all_pipes(t_shell *shell);
void	free_all_pipes(t_shell *shell);
void	free_commands(t_shell *shell);
void	execute_command(t_shell *shell, int i);
void	first_cmd(t_shell *shell);
void	last_cmd(t_shell *shell, int i);
void	middle_cmd(t_shell *shell, int i);
int		check_builtin(char **command);
int		exec_builtin(t_shell *shell, char **command, int id);
char	**get_commands(t_token *tokens);
int		get_nb_pipes(t_shell *shell);

/**********ENVP***********/
void	init_envp(t_shell *shell, char **env);
void	update_envp(t_shell *shell, char *var_name, char *var_value);
void	ft_sort_strings(int num, char **s);
void	free_envp(t_shell *shell);

/********BUILT*IN**********/
int		pwd(void);
int		cd(char *path, t_shell *shell);
int		env(t_shell *shell);

#endif
