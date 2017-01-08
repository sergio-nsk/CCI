/*
 URLify: Write a method to replace all spaces in a string with '%20'. You may assume that the string
 has sufficient space at the end to hold the additional characters, and that you are given the "true"
 length of the string. (Note: If implementing in Java, please use a character array so that you can
 perform this operation in place.)
 EXAMPLE
 Input:
  "Mr John Smith", 13
 Output:
  "Mr%20John%20Smith"
*/

#include <stdio.h>
#include <string.h>

char *encodeSpaces(char *url, size_t capacity, size_t len)
{
    char *from = url;
    int cnt = 0;
    for ( ; *from; ++from)
        if (*from == ' ')
            ++cnt;

    if (cnt == 0)
        return url;

    // from -> \0
    char *to = from + cnt * 2;
    if (to >= url + capacity)
        return NULL;    // Not enouth capacity

    for ( ; to > from; --from)
    {
        if (*from == ' ')
        {
            *to-- = '0';
            *to-- = '2';
            *to-- = '%';
        }
        else
            *to-- = *from;
    }

    return url;
}

void test(char *url, size_t capacity, const char *raw)
{
    strcpy(url, raw);
    printf("\"%s\" --> ", url);
    url = encodeSpaces(url, capacity, strlen(url));
    if (url)
        printf("\"%s\"\n", url);
    else
        printf("Failed - more space required\n");
}

int main(int argc, char **argv)
{
    char url[120] = { 0 };
    test(url, sizeof(url), "Mr John Smith");
    test(url, sizeof(url), "a b c d e f g h i j k l m n o p q r s t u v x w z");
    test(url, 97, "a b c d e f g h i j k l m n o p q r s t u v x w z");
    test(url, sizeof(url), "a     ");
    test(url, sizeof(url), "     ");
    test(url, sizeof(url), "     b");
    test(url, sizeof(url), "a     b");
    return 0;
}