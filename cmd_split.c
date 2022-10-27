
#include "minishell.h"

static size_t	ft_countc(char const *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != '<' && s[i] != '\0' && )
			i++;
	}
	return (count);
}

static void	*ft_mallocerror(char **tab, size_t i)
{
	while (i-- > 0)
		free(tab[i]);
	free(tab);
	return (NULL);
}

static const char	*ft_filltab(char **tab, const char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (*s && *s == c)
		s++;
	while (s[i] && s[i] != c)
		i++;
	*tab = (char *)malloc(sizeof(char) * (i + 1));
	if (!tab)
		return (NULL);
	j = 0;
	while (j < i)
	{
		(*tab)[j] = s[j];
		j++;
	}
	(*tab)[j] = '\0';
	return (&s[j]);
}

char	**cmd_split(char const *s)
{
	char	**tab;
	size_t	i;
	size_t	nbr_of_str;

	if (!s)
		return (NULL);
	nbr_of_str = ft_countc(s);
	tab = (char **)malloc(sizeof(char *) * (nbr_of_str + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < nbrofc)
	{
		s = ft_filltab(&tab[i], s, c);
		if (!tab[i])
			return (ft_mallocerror(tab, i));
		i++;
	}
	tab[i] = NULL;
	return (tab);
}