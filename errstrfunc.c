#include "shell.h"

/**
 *e_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void e_puts(char *string)
{
    int s = 0;

    if (!string)
        return;
    while (string[s] != '\0')
    {
        e_putchar(string[s]);
        s++;
    }
}

/**
 * e_putchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int e_putchar(char c)
{
    static int x;
    static char buff[WRITE_BUF_SIZE];

    if (c == BUF_FL || x >= WRITE_BUF_SIZE)
    {
        write(2, buff, x);
        x = 0;
    }
    if (c != BUF_FL)
        buff[x++] = c;
    return (1);
}

/**
 * put_fd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_fd(char b, int fd)
{
    static int z;
    static char buff[WRITE_BUF_SIZE];

    if (b == BUF_FL || z >= WRITE_BUF_SIZE)
    {
        write(fd, buff, z);
        z = 0;
    }
    if (b!= BUF_FL)
        buff[z++] = b;
    return (1);
}

/**
 *puts_fd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 * Return: the number of chars put
 */
int puts_fd(char *string, int fd)
{
    int y = 0;

    if (!string)
        return (0);
    while (*string)
    {
        y += put_fd(*string++, fd);
    }
    return (y);
}