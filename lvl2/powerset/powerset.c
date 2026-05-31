#include <stdio.h>
#include <stdlib.h>

static int	check_int(char **argv, int argc)
{
	int	i;
	int	j;

	j = 1;
	while (j < argc)
	{
		i = 0;
		if (argv[j][i] == '-' || argv[j][i] == '+')
			i++;
		if (!argv[j][i])
			return (0);
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

static void	print_subset(int *subset, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("%d", subset[i]);
		if (i != size - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

static void	solve(int *nums, int size, int target, int *subset,
		int index, int sub_size, int sum)
{
	if (index == size)
	{
		if (sum == target)
			print_subset(subset, sub_size);
		return ;
	}
	subset[sub_size] = nums[index];
	solve(nums, size, target, subset, index + 1, sub_size + 1,
		sum + nums[index]);
	solve(nums, size, target, subset, index + 1, sub_size, sum);
}

int	main(int argc, char **argv)
{
	int	*nums;
	int	*subset;
	int	target;
	int	i;

	if (argc < 2 || !check_int(argv, argc))
		return (1);
	target = atoi(argv[1]);
	nums = (int *)malloc(sizeof(int) * (argc - 2));
	subset = (int *)malloc(sizeof(int) * (argc - 2));
	if ((!nums || !subset) && argc > 2)
		return (free(nums), free(subset), 1);
	i = 0;
	while (i < argc - 2)
	{
		nums[i] = atoi(argv[i + 2]);
		i++;
	}
	solve(nums, argc - 2, target, subset, 0, 0, 0);
	free(nums);
	free(subset);
	return (0);
}
