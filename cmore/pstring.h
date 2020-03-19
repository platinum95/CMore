#ifndef CMORE_PSTRING_H
#define CMORE_PSTRING_H

// Search null-terminated _inString for (null-terminated) _pattern, and set _outString to point 
// within _inString if found. Return 1 if string found, 0 otherwise.
// At some point, proper regex-ish support may be added, but for now _pattern should be just
// a normal sub-string to be found (and is case sensitive)
int pomStringFind( char *_inString, const char *_pattern, char ** _outString );


#endif // CMORE_PSTRING_H