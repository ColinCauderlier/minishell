/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:44:46 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/04 17:21:58 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static size_t	countwords_inword(char const *s, size_t i)
{
	char	c;

	while (s[i] && !ft_isspace(s[i]) && s[i] != '|')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			i++;
			while (s[i] && s[i] != c)
				i++;
		}
		i++;
	}
	return (i);
}

static size_t	countwords(char const *s)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '|')
		{
			count++;
			i++;
			continue ;
		}
		if (!ft_isspace(s[i]))
		{
			count++;
			i = countwords_inword(s, i);
			i--;
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
	while (str[i] && !ft_isspace(str[i]) && str[i] != '|')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
				i++;
		}
		i++;
	}
	if (i == 0 && str[i] == '|')
		i++;
	res[pos_res].content = ft_substr(str, 0, i);
	if (!res[pos_res].content)
		return (free_res(res, pos_res), NULL);
	return (&str[i]);
}

// Un split modifie, free les tokens en cas de probleme
t_token	*get_content(char *str)
{
	t_token	*res;
	int		pos_res;
	int		nb_words;

	pos_res = 0;
	if (!str)
		return (NULL);
	nb_words = countwords(str);
	if (nb_words == 0)
		return (NULL);
	res = ft_calloc((nb_words + 1), sizeof(t_token));
	if (!res)
		return (NULL);
	while (pos_res < nb_words)
	{
		str = res_fill(res, pos_res, str);
		if (!str)
			return (free_res(res, pos_res), NULL);
		res[pos_res].next = &res[pos_res + 1];
		pos_res++;
	}
	res[pos_res].content = NULL;
	res[pos_res].next = NULL;
	return (res);
}
