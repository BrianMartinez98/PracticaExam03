#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static void	copy_bytes(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

static void	print_filtered(char *buffer, char *target)
{
	int	i;
	int	j;
	int	len;

	len = strlen(target);
	i = 0;
	while (buffer[i])
	{
		j = 0;
		while (target[j] && buffer[i + j] && buffer[i + j] == target[j])
			j++;
		if (j == len)
		{
			j = 0;
			while (j++ < len)
				printf("*");
			i += len;
		}
		else
			printf("%c", buffer[i++]);
	}
}

int	main(int argc, char **argv)
{
	char	tmp[BUFFER_SIZE];
	char	*content;
	char	*new_content;
	int		total;
	int		bytes;

	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	content = NULL;
	total = 0;
	bytes = read(0, tmp, BUFFER_SIZE);
	while (bytes > 0)
	{
		new_content = (char *)realloc(content, total + bytes + 1);
		if (!new_content)
			return (free(content), perror("Error"), 1);
		content = new_content;
		copy_bytes(content + total, tmp, bytes);
		total += bytes;
		content[total] = '\0';
		bytes = read(0, tmp, BUFFER_SIZE);
	}
	if (bytes < 0)
		return (free(content), perror("Error"), 1);
	if (content)
		print_filtered(content, argv[1]);
	free(content);
	return (0);
}
