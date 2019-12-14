#include "string_.h"


int strcmp ( const char *s1, const char *s2 )
{
    for( ; *s1 == *s2; ++s1, ++s2 )
        if ( *s2 == '\0' )
            return 0;
    return (unsigned char) *s1 - (unsigned char) *s2;
}
