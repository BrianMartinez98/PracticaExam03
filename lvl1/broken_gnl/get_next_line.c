#include "get_next_line.h"

static size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

static char	*ft_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&s[i]);
	return (NULL);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((const char *)src)[i];
		i++;
	}
	return (dst);
}

static void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == src || n == 0)
		return (dst);
	if (dst > src)
	{
		i = n;
		while (i > 0)
		{
			i--;
			((char *)dst)[i] = ((const char *)src)[i];
		}
	}
	else
		ft_memcpy(dst, src, n);
	return (dst);
}

static int	append_mem(char **line, char *buf, size_t n)
{
	char	*new_line;
	size_t	old_len;

	old_len = ft_strlen(*line);
	new_line = (char *)malloc(old_len + n + 1);
	if (!new_line)
		return (0);
	if (*line)
		ft_memcpy(new_line, *line, old_len);
	ft_memcpy(new_line + old_len, buf, n);
	new_line[old_len + n] = '\0';
	free(*line);
	*line = new_line;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		newline = ft_strchr(buf, '\n');
		if (newline)
		{
			if (!append_mem(&line, buf, newline - buf + 1))
				return (free(line), NULL);
			ft_memmove(buf, newline + 1, ft_strlen(newline + 1) + 1);
			return (line);
		}
		if (!append_mem(&line, buf, ft_strlen(buf)))
			return (NULL);
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (free(line), buf[0] = '\0', NULL);
		buf[bytes] = '\0';
		if (bytes == 0)
		{
			if (line && *line)
				return (line);
			free(line);
			return (NULL);
		}
	}
}
