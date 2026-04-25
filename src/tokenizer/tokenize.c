/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:44:46 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/25 23:13:28 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

static void	free_res(char **res, int pos_res)
{
	int	i;

	i = 0;
	while (i < pos_res)
		free(res[i++]);
	free(res);
}

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
				i++;
				c = s[i];
				while (s[i] != c && s[i])
					i++;
				i++;
			}
			else
			{
				while (!ft_isspace(s[i]) && s[i])
					i++;
			}
			i--;
		}
		i++;
	}
	return (count);
}

static char	*res_fill(char **res, int pos_res, char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]) && str[i] != '\0')
		i++;
	str = &str[i];
	i = 0;
	if (str[i] == '\"')
	{
		i++;
		while (str[i] != '\"' && str[i] != '\0')
			i++;
		if (str[i] == '\"')
			i++;
	}
	else if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'' && str[i] != '\0')
			i++;
		if (str[i] == '\'')
			i++;
	}
	else
	{
		while (!ft_isspace(str[i]) && str[i] != '\0')
			i++;
	}
	res[pos_res] = ft_substr(str, 0, i);
	if (!res[pos_res])
	{
		free_res(res, pos_res);
		return (NULL);
	}
	if (str[i] == '\'' || str[i] == '\"')
		i++;
	return (&str[i]);
}

static char	**get_content(char const *s)
{
	char	**res;
	char	*str;
	int		pos_res;
	int		nb_words;

	pos_res = 0;
	str = (char *)s;
	nb_words = countwords(s);
	printf("countword: %d\n", nb_words);
	res = ft_calloc((nb_words + 1), sizeof(char *));
	if (!res || !s)
		return (NULL);
	while (pos_res < nb_words)
	{
		str = res_fill(res, pos_res, str);
		if (!str)
			return (NULL);
		pos_res++;
	}
	res[pos_res] = NULL;
	return (res);
}

void	tokenize(char *prompt)
{
	char	**token_content;
	int		i;

	i = 0;
	token_content = get_content(prompt);
	while (token_content[i])
	{
		printf("%s\n", token_content[i]);
		i++;
	}
}
