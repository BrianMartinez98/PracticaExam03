#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int bytes_read = 0;
	static int buffer_pos = 0;
	char *line;
	int len = 7000;
	int i = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	line = malloc(sizeof(char) * len);
	if (!line)
		return NULL;
	while(1)
	{
		if (buffer_pos >= bytes_read)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (bytes_read == 0)
				break ;
			if (bytes_read == -1)
			{
				free(line);
				return NULL;
			}
		}
		line[i++] = buffer[buffer_pos++];
		if (line[i - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int main(void)
{
  int fd = open("test.txt", O_RDONLY);
  char *line = get_next_line(fd);
  if (fd < 0)
    return (1);
  while (line)
  {
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
  }
  close(fd);
}