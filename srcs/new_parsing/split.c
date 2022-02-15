
static int	ft_is_c(char c, char d)
{
	if (c == d)
		return (0);
	else
		return (1);
}

static int	ft_len(const char *s, char c)
{
	unsigned int	i;
	unsigned int	compt;

	i = 0;
	compt = 0;
	while (ft_is_c(s[i], c) == 0)
		i++;
	while (ft_is_c(s[i], c) != 0 && s[i])
	{
		i++;
		compt++;
	}
	return (compt);
}

static int	ft_elements(const char *s, char c)
{
	unsigned int	i;
	unsigned int	compt;

	i = 0;
	compt = 0;
	while (s[i])
	{
		while (ft_is_c(s[i], c) == 0)
			i++;
		if (ft_is_c(s[i], c) != 0 && s[i])
			compt++;
		while (ft_is_c(s[i], c) != 0 && s[i])
			i++;
	}
	return (compt);
}

char	**ft_split(char const *s, char c)
{
	char			**result;
	int				i;
	unsigned int	j;
	unsigned int	k;

	result = malloc(sizeof(char *) * (ft_elements(s, c) + 1));
	if (!(result))
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_elements(s, c))
	{
		k = 0;
		result[i] = malloc(ft_len(&s[j], c) + 1);
		if (!(result[i]))
			return (NULL);
		while (ft_is_c(s[j], c) == 0)
			j++;
		while (ft_is_c(s[j], c) != 0 && s[j] != '\0')
			result[i][k++] = s[j++];
		result[i][k] = '\0';
		i++;
	}
	result[i] = 0;
	return (result);
}