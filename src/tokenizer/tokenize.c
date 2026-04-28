/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:44:46 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/28 18:39:38 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

/*Pour l'expander il faudrait une fonction get_name et une autre get_index_matching_name*/

static int	max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

static void    get_type(t_token *lst)
{
	if (!lst)
		return ;
	while (lst && lst->next)
	{
		if (ft_strncmp(lst->content, "|\0", 2) == 0)
			lst->token_type = PIPE;
		else if (ft_strncmp(lst->content, "<\0", 2) == 0)
			lst->token_type = REDIR_IN;
		else if (ft_strncmp(lst->content, ">\0", 2) == 0)
			lst->token_type = REDIR_OUT;
		else if (ft_strncmp(lst->content, "<<\0", 3) == 0)
			lst->token_type = HEREDOC;
		else if (ft_strncmp(lst->content, ">>\0", 3) == 0)
			lst->token_type = REDIR_OUT_APP_MODE;
		else
			lst->token_type = WORD;
		lst = lst->next;
	}
}

//Retourne s'il y a eu un changement d'etat ou non
static int	change_state(char c, t_state *state)
{
	if (c == '\'' && *state == GENERAL)
	{
		*state = SIMPLE_QUOTE;
		return (1);
	}
	else if (c == '\"' && *state == GENERAL)
	{
		*state = DOUBLE_QUOTE;
		return (1);
	}
	else if (c == '\'' && *state == SIMPLE_QUOTE)
	{
		*state = GENERAL;
		return (1);
	}
	else if (c == '\"' && *state == DOUBLE_QUOTE)
	{
		*state = GENERAL;
		return (1);
	}
	return (0);
}

//j est a l'emplacement du =
static int	get_length_from_envp(char *name, int len_name, char **envp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=' && envp[i][j])
			j++;
		if (ft_strncmp(name, envp[i], max(len_name, j)) == 0)
		{
			printf("%s\n", envp[i]);
			k = j;
			while(envp[i][k])
				k++;
			return (k - j - 1);
		}
		i++;
	}
	return (0);
}

//Recupere la longueur de la chaine qui va etre expand
static int	get_length_expand(char *str, int start, char **envp)
{
	char	*expand_name;
	int	i;
	int	len;
	int	len_name;
	
	i = start + 1;
	while (str[i] && str[i] != '$' && !ft_isspace(str[i]) && !ft_isquote(str[i]))
		i++;
	expand_name = ft_substr(str, start + 1, i - start - 1);
	len_name = ft_strlen(expand_name);
	len = get_length_from_envp(expand_name, len_name, envp);
	free(expand_name);
	return (len);
}

//Recupere la longueur de la nouvelle chaine pour pouvoir malloc de la bonne taille
static int	get_new_content_length(char *content, char **envp)
{
	int	i;
	int	len;
	t_state	state;

	i = 0;
	len = 0;
	state = GENERAL;
	while (content[i])
	{
		if (change_state(content[i], &state))
			i++;
		else if (state != SIMPLE_QUOTE && content[i] == '$')
		{
			len += get_length_expand(content, i, envp);
			i++;
			while (content[i] && content[i] != '$' && !ft_isspace(content[i]) && !ft_isquote(content[i]))
				i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static char	*get_expand(char *str, char **envp)
{
	int	i;
	int	j;
	char	*expand_name;

	i = 0;
	while (str[i] && str[i] != '$' && !ft_isspace(str[i]) && !ft_isquote(str[i]))
		i++;
	expand_name = ft_substr(str, 0, i);
	i = 0;
	while (envp[i])
	{
		j = 0;
		while ()
		i++;
	}
	free(expand_name);
}

static int	get_new_content(t_token *token, int len, char **envp)
{
	int	i;
	int	start;
	char	*new;
	char	*old;
	char	*temp;
	t_state	state;

	i = 0;
	start = 0;
	old = token->content;
	state = GENERAL;
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return ;
	while (old[i])
	{
		if (change_state(old[i], &state))
		{
			temp = ft_substr(old, start, i - start - 1);
			new = ft_strjoin(new, temp);
			free(temp);
			i++;
			start = i;
		}
		else if (state != SIMPLE_QUOTE && old[i] == '$')
		{
			temp = ft_substr(old, start, i - start - 1);
			new = ft_strjoin(new, temp);
			free(temp);
			temp = get_expand(&old[i + 1], envp);
			new = ft_strjoin(new, temp);
			free(temp);
			while (old[i] && old[i] != '$' && !ft_isspace(old[i]) && !ft_isquote(old[i]))
				i++;
			start = i;
		}
		else
			i++;
	}

}
//Recupere le contenu brut des tokens et remplace le contenu par une autre chaine dans laquelle les guillemets et les expand ont ete geres
static void	manage_quote_and_expand(t_token *lst, char **envp)
{
	int	i;
	t_state	state;
	int	len;
	char	*new_content;

	if (!lst)
		return ;
	while (lst && lst->next)
	{
		len = get_new_content_length(lst->content, envp);
		printf("LEN = %d\n", len);
		if (!get_new_content(lst, len, envp))
			return ;
		lst = lst->next;
	}
}

void	tokenize(char *prompt, char **envp)
{
	t_token		*list;
	char		*str;

	list = get_content(prompt);
	manage_quote_and_expand(list, envp);
	get_type(list);
	while (list && list->next)
	{
		if (list->token_type == PIPE)
			 str = "PIPE";
		else if (list->token_type == REDIR_IN)
			str = "REDIR_IN";
		else if (list->token_type == REDIR_OUT)
			str = "REDIR_OUT";
		else if (list->token_type == HEREDOC)
			str = "HEREDOC";
		else if (list->token_type == REDIR_OUT_APP_MODE)
			str = "REDIR_OUT_APP_MODE";
		else if (list->token_type == WORD)
			str = "WORD";
		printf("%s %s\n", list->content, str);
		list = list->next;
	}
}
