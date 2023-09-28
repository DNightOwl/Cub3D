/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbacktrim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:46:54 by laafilal          #+#    #+#             */
/*   Updated: 2021/01/05 18:47:27 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static size_t     ft_trim_back(const char *str, char const *set)
{
    size_t      i;
    size_t      c;

    i = ft_strlen(str) - 1;
    c = 0;
    while (i + 1 > 0 && str[i] != '\0')
    {
        if (!ft_strchr(set, str[i--]))
            return (c);
        c++;
    }
    return (i);
}

char                *ft_strtrim_back(char const *s1, char const *set)
{
    char        *str;
    size_t      ctb;

    if (!s1)
        return (NULL);
    if (!set || *s1 == 0 || *set == 0)
        return (ft_strdup(s1));
    ctb = ft_strlen(s1) - ft_trim_back(s1, set);
    str = ft_substr(s1, 0, ctb);
    if (!str)
        return (NULL);
    return (str);
}
