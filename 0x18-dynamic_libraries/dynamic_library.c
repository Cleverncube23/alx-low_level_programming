#include "main.h"
#include <stddef.h>
#include <unistd.h>

int _putchar(char c) {
    return write(1, &c, 1);
}

int _islower(int c) {
    return (c >= 'a' && c <= 'z');
}

int _isalpha(int c) {
    return ((_islower(c)) || (_isupper(c)));
}

int _abs(int n) {
    return (n >= 0) ? n : -n;
}

int _isupper(int c) {
    return (c >= 'A' && c <= 'Z');
}

int _isdigit(int c) {
    return (c >= '0' && c <= '9');
}

int _strlen(char *s) {
    int len = 0;
    while (*s++)
        len++;
    return len;
}

void _puts(char *s) {
    while (*s) {
        _putchar(*s++);
    }
    _putchar('\n');
}

char *_strcpy(char *dest, char *src) {
    char *ptr = dest;
    while (*src != '\0') {
        *dest++ = *src++;
    }
    *dest = '\0';
    return ptr;
}

int _atoi(char *s) {
    int num = 0;
    int sign = 1;
    if (*s == '-') {
        sign = -1;
        s++;
    }
    while (*s) {
        if (*s >= '0' && *s <= '9') {
            num = num * 10 + (*s - '0');
        }
        s++;
    }
    return sign * num;
}

char *_strcat(char *dest, char *src) {
    char *ptr = dest + _strlen(dest);
    while (*src != '\0') {
        *ptr++ = *src++;
    }
    *ptr = '\0';
    return dest;
}

char *_strncat(char *dest, char *src, int n) {
    char *ptr = dest + _strlen(dest);
    while (*src != '\0' && n--) {
        *ptr++ = *src++;
    }
    *ptr = '\0';
    return dest;
}

char *_strncpy(char *dest, char *src, int n) {
    char *ptr = dest;
    while (*src != '\0' && n--) {
        *dest++ = *src++;
    }
    while (n--) {
        *dest++ = '\0';
    }
    return ptr;
}

int _strcmp(char *s1, char *s2) {
    while (*s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

char *_memset(char *s, char b, unsigned int n) {
    char *ptr = s;
    while (n--) {
        *s++ = b;
    }
    return ptr;
}

char *_memcpy(char *dest, char *src, unsigned int n) {
    char *ptr = dest;
    while (n--) {
        *dest++ = *src++;
    }
    return ptr;
}

char *_strchr(char *s, char c) {
    while (*s != '\0' && *s != c) {
        s++;
    }
    if (*s == c) {
        return s;
    }
    return NULL;
}

unsigned int _strspn(char *s, char *accept) {
    unsigned int count = 0;
    char *ptr;

    while (*s) {
        for (ptr = accept; *ptr; ptr++) {
            if (*s == *ptr) {
                break;
            }
        }
        if (!*ptr) {
            break;
        }
        s++;
        count++;
    }

    return count;
}

char *_strpbrk(char *s, char *accept) {
    while (*s) {
        char *ptr = accept;
        while (*ptr) {
            if (*s == *ptr) {
                return s;
            }
            ptr++;
        }
        s++;
    }
    return NULL;
}

char *_strstr(char *haystack, char *needle) {
    char *hptr = haystack;
    char *nptr;

    if (*needle == '\0') {
        return haystack;
    }

    while (*hptr) {
        nptr = needle;
        hptr = haystack;

        while (*hptr && *nptr && *hptr == *nptr) {
            hptr++;
            nptr++;
        }

        if (!*nptr) {
            return haystack;
        }

        haystack++;
    }

    return NULL;
}

