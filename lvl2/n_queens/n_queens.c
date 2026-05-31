#include <stdlib.h>
#include <unistd.h>

static void	putnbr(int n)
{
	char	c;

	if (n >= 10)
		putnbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

static int	is_safe(int *pos, int col, int row)
{
	int	prev;
	int	prev_row;

	prev = 0;
	while (prev < col)
	{
		prev_row = pos[prev];
		if (prev_row == row || prev_row - prev == row - col
			|| prev_row + prev == row + col)
			return (0);
		prev++;
	}
	return (1);
}

static void	solve(int *pos, int col, int n)
{
	int	row;
	int	i;

	if (col == n)
	{
		i = 0;
		while (i < n)
		{
			if (i > 0)
				write(1, " ", 1);
			putnbr(pos[i++]);
		}
		write(1, "\n", 1);
		return ;
	}
	row = 0;
	while (row < n)
	{
		if (is_safe(pos, col, row))
		{
			pos[col] = row;
			solve(pos, col + 1, n);
		}
		row++;
	}
}

int	main(int argc, char **argv)
{
	int	*pos;
	int	n;

	if (argc != 2 || argv[1][0] == '-')
		return (1);
	n = atoi(argv[1]);
	pos = (int *)malloc(sizeof(int) * n);
	if (!pos)
		return (1);
	solve(pos, 0, n);
	free(pos);
	return (0);
}
