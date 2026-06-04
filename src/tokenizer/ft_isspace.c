/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 14:45:05 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/04 17:21:53 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char c)
{
	if (c == 32 || (9 < c && c < 13))
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_expand_lim(char c)
{
	if (ft_isquote(c) || ft_isspace(c) || c == '$')
		return (1);
	return (0);
}

int	is_redir_symbol(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}
