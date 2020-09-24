/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 19:32:03 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/23 19:01:06 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	char	used[255];
	int		i;
	int		j;

	if (argc == 3)
	{
		i = 0;
		while (i < 255)
			used[i++] = 0;
		i = argc;
		while (--i > 0)
		{
			j = -1;
			while (argv[i][++j])
			{
				if ((!used[(unsigned char)argv[i][j]]) && (i == 2))
					used[(unsigned char)argv[i][j]] = 1;
				if ((used[(unsigned char)argv[i][j]]) && (i == 1))
				{
					write(1, &argv[i][j], 1);
					used[(unsigned char)argv[i][j]] = 0;
				}
			}
		}
	}
	write(1, "\n", 1);
	return (0);
}
