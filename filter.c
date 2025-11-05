
#define BUFFER_SIZE 42

void ft_filter(char *buffer, const char *target)
{
    int i = 0;
    int t_len = strlen(target);

    while (buffer[i])
    {
        int j = 0;
        while (buffer[i + j] && target[j] && target[j] == buffer[i + j])
            j++
        if (j == t_len)
    }
}

int main()
{
    char *buff;
    char *res;
    char *temp[BUFFER_SIZE];
    int bytes_read;
    int total_read = 0;

    while(bytes_read = read(0, temp, BUFFER_SIZE) > 0)
    {
        buff = realloc(res, (total_read + bytes_read + 1));
        if (!buff)
        {
            free(res);
            perror("realloc");
            return (1);
        }
        res = buff;
        memmove((res + total_read), temp, bytes_read);
        total_read = total_read + bytes_read;
        res[total_read] = '\0';
    }


}