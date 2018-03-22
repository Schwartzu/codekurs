#ifndef TEXTIO_H_INCLUDED
#define TEXTIO_H_INCLUDED

/**
        The read_text function opens the file located at the given filename and
        reads all characters until the end of the file (i.e. until EOF appears).
        New line indicators ('\n'), space characters (' '), and terminating
        characters ('\0') are skipped.

        The read_text function returns the address of a dynamically allocated char
        array consisting of the input file's characters. In case of read errors,
        NULL is returned.
*/
char *read_text(const char *file);

/**
 	The write_text function writes the characters given in the array pointed 
	to by _text_ to a file named _file_.

 	The write_text function returns 1 if the operation was successful, and 0
 	if the write operation failed.
*/
int write_text(const char *text, const char *file);

#endif
