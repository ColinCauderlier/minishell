/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:44:46 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/27 13:01:38 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static size_t	countwords(char const *s)
{
	size_t	count;
	size_t	i;
	char	c;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
		{
			count++;
			if (s[i] == '\'' || s[i] == '\"')
			{
				c = s[i++];
				while (s[i] != c && s[i])
					i++;
			}
			else
			{
				while (!ft_isspace(s[i]) && s[i])
					i++;
				i--;
			}
		}
		i++;
	}
	return (count);
}

static char	*res_fill(t_token *res, int pos_res, char *str)
{
	int		i;
	char	c;

	i = 0;
	while (ft_isspace(str[i]) && str[i] != '\0')
		i++;
	str = &str[i];
	i = 0;
	if (str[i] == '\"' || str[i] == '\'')
	{
		c = str[i++];
		while (str[i] != c && str[i] != '\0')
			i++;
		res[pos_res].content = ft_substr(str, 1, i - 1);
		if (c == '\'')
			res[pos_res].token_state = SIMPLE_QUOTE;
		else
			res[pos_res].token_state = DOUBLE_QUOTE;
		if (str[i] == c)
			i++;
	}
	else
	{
		while (!ft_isspace(str[i]) && str[i] != '\0')
			i++;
		res[pos_res].content = ft_substr(str, 0, i);
		res[pos_res].token_state = GENERAL;
	}
	if (!res[pos_res].content)
		return (free_res(res, pos_res), NULL);
	if (str[i] == '\'' || str[i] == '\"')
		i++;
	return (&str[i]);
}

t_token	*get_content(char const *s)
{
	t_token	*res;
	char	*str;
	int		pos_res;
	int		nb_words;

	pos_res = 0;
	if (!s)
			return (NULL);
	str = (char *)s;
	nb_words = countwords(s);
	res = malloc((nb_words + 1) * sizeof(t_token));
	if (!res)
		return (NULL);
	while (pos_res < nb_words)
	{
		str = res_fill(res, pos_res, str);
		if (!str)
			return (free(res), NULL);
		res[pos_res].next = &res[pos_res + 1];
		pos_res++;
	}
	res[pos_res].content = NULL;
	res[pos_res].next = NULL;
	return (res);
}
