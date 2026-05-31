#include <stdlib.h>
#include <unistd.h>

static int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static void	sort_chars(char *s)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	while (s[i])
	{
		j = i + 1;
		while (s[j])
		{
			if (s[i] > s[j])
			{
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	permute(char *s, char *result, int *used, int depth, int len)
{
	int	i;

	if (depth == len)
	{
		write(1, result, len);
		write(1, "\n", 1);
		return ;
	}
	i = 0;
	while (i < len)
	{
		if (!used[i])
		{
			used[i] = 1;
			result[depth] = s[i];
			permute(s, result, used, depth + 1, len);
			used[i] = 0;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*result;
	int		*used;
	int		len;

	if (argc != 2)
		return (1);
	len = ft_strlen(argv[1]);
	result = (char *)malloc(len + 1);
	used = (int *)calloc(len, sizeof(int));
	if (!result || !used)
		return (free(result), free(used), 1);
	sort_chars(argv[1]);
	permute(argv[1], result, used, 0, len);
	free(result);
	free(used);
	return (0);
}
