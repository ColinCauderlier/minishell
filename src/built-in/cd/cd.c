/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:15:43 by lucinguy          #+#    #+#             */
/*   Updated: 2026/06/04 17:21:08 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

int	cd(char *path, t_shell *shell)
{
	char	*target;
	int		print_path;
	int		ret;

	target = get_target_path(path, shell, &print_path);
	if (!target)
		return (print_cd_error(path), 1);
	ret = perform_cd_update(shell, target, print_path);
	free(target);
	return (ret);
}
