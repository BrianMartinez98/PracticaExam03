#include <stdio.h>

static int	fix_count(char *s)
{
	int	open;
	int	close;
	int	i;

	open = 0;
	close = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	return (open + close);
}

static void	rip(char *s, int target, int removed, int pos)
{
	int	i;
	int	c;

	if (removed == target && fix_count(s) == 0)
	{
		puts(s);
		return ;
	}
	i = pos;
	while (s[i])
	{
		if (s[i] == '(' || s[i] == ')')
		{
			c = s[i];
			s[i] = ' ';
			rip(s, target, removed + 1, i + 1);
			s[i] = c;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	target;

	if (argc != 2)
		return (1);
	target = fix_count(argv[1]);
	rip(argv[1], target, 0, 0);
	return (0);
}
