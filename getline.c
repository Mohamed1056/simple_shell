#include "shell.h"

/**
 * input_buff 
 * @info: parameter struct
 * @buff: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buff(info_t *information, char **buff, size_t *len)
{
    ssize_t read = 0;
    size_t len_p = 0;

    if (!*len)
    {

        free(*buff);
        *buff = NULL;
        signal(SIGINT, sigintHandler);
#if USEGETLINE
        read = getline(buff, &len_p, stdin);
#else
        read = get_l(information, buff, &len_p);
#endif
        if (read > 0)
        {
            if ((*buff)[read - 1] == '\n')
            {
                (*buff)[read - 1] = '\0'; /* remove trailing newline */
                read--;
            }
            information->linecount_flag = 1;
            Remove_Comments(*buff);
            BuildHlist(information, *buff, information->histcount++);

            {
                *len = read;
                information->cmd_buf = buff;
            }
        }
    }
    return (read);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes
 */
ssize_t get_input(info_t *info)
{
    static char *buff;
    static size_t i, j, len;
    ssize_t read = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FL);
    read = input_buff(info, &buff, &len);
    if (read == -1) /* EOF */
        return (-1);
    if (len) /* we have commands left in the chain buffer */
    {
        j = i;        /* init new iterator to current buf position */
        p = buff + i; /* get pointer for return */

        check_chain(info, buff, &j, i, len);
        while (j < len) /* iterate to semicolon or end */
        {
            if (is_chain(info, buff, &j))
                break;
            j++;
        }

        i = j + 1;    /* increment past nulled ';'' */
        if (i >= len) /* reached end of buffer? */
        {
            i = len = 0; /* reset position and length */
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p;          /* pass back pointer to current command position */
        return (str_len(p)); /* return length of current command */
    }

    *buf_p = buff;
    return (read); /* return length of buff */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: raaed
 */
ssize_t readbuff(info_t *info, char *buff, size_t *i)
{
    ssize_t read = 0;

    if (*i)
        return (0);
    r = read(info->readfd, buff, READ_BUF_SIZE);
    if (read >= 0)
        *i = r;
    return (read);
}

/**
 * get_l - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_l(info_t *information, char **ptr, size_t *length)
{
    static char buff[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t read = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    read = readbuff(info, buff, &len);
    if (read == -1 || (read == 0 && len == 0))
        return (-1);

    c = str_chr(buff + i, '\n');
    k = c ? 1 + (unsigned int)(c - buff) : len;
    new_p = re_allocate(p, s, s ? s + k : k + 1);
    if (!new_p)
        return (p ? free(p), -1 : -1);

    if (s)
        strn_cat(new_p, buff + i, k - i);
    else
       strn_copy(new_p, buff + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return (s);
}

/**
 * siginHandle
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FL);
}
