// A ver si se hacer el GNL

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int bytes_read;
    static int buff_pos;
    int i = 0;
    int len = 7000;

    if (fd == -1 || BUFFER_SIZE < 0)
        return NULL;
    char *line = malloc(sizeof(char)*len);
    if (!line)
        return NULL;
    
    while(1)
    {
        if (buff_pos >= bytes_read)
        {
            buff_pos = 0;
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read == -1)
            {
                free(line);
                return NULL;
            }
            if (bytes_read == 0)
                break;
        }
        line[i++] = buffer[buff_pos++];
        if (line[i - 1] == '\n')
            break;
    }
    line[i] = '\0';
    return line;
}

int main()
{
    int fd = open("test.txt", O_RDONLY);
    for (int i = 0; i < 9; i++)
    {
        printf("%s", get_next_line(fd));
    }
    printf("\n");
    return 0;
}