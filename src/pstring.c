#include "cmore/pstring.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

int pomStringFind( char *_inString, const char *_pattern, char ** _outString ){
    const size_t inStringLen = strlen( _inString );
    const size_t patternLen = strlen( _pattern );

    // No need to check if input string is smaller than pattern
    if( inStringLen < patternLen ){
        *_outString = NULL;
        return 0;
    }
    char *cPos;
    // No need to search beyond the point where the pattern wouldn't fit anymore
    for( uint32_t i = 0; i <= inStringLen - patternLen; i++ ){
        cPos = &_inString[ i ];
        if( !strncmp( cPos, _pattern, patternLen ) ){
            *_outString = cPos;
            return 1;
        }
    }

    *_outString = NULL;
    return 0;
}