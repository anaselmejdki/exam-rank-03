#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

static char *ft_strjoin(char *s1, char s2)
{
    char *result;
    int i;

    if (!s1)
    {
        result = malloc(2);
        if (!result)
            return NULL;
        result[0] = s2;
        result[1] = '\0';
        return result;
    }

    i = 0;
    while (s1[i])
        i++;
    result = malloc(i + 2);
    if (!result)
        return NULL;
    i = 0;
    while (s1[i])
    {
        result[i] = s1[i];
        i++;
    }
    result[i] = s2;
    result[i + 1] = '\0';
    free(s1);
    return result;
}

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    static int buffer_pos = 0;
    static int bytes_read = 0;
    char *line = NULL;
    char c;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while (1)
    {
        if (buffer_pos >= bytes_read)
        {
            buffer_pos = 0;
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read <= 0)
                break;
        }

        c = buffer[buffer_pos++];
        line = ft_strjoin(line, c);
        if (!line)
            return NULL;
        if (c == '\n')
            break;
    }

    return (line && *line) ? line : NULL;
}
