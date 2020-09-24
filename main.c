/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 20:29:25 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/23 19:08:43 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int	main()
{
	int		more;
	char	*line;

	line = 00;
	while ((more = get_next_line(&line) > 0))
	{
		printf("%s\n", line);
		free(line);
		line = 00;
	}
	printf("%s", line);
	free(line);
	line = 00;	
	return (0);
}
