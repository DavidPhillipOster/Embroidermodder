#include "format-t09.h"
#include "emb-logging.h"
#include <stdio.h>

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readT09(EmbPattern* pattern, const char* fileName)
{
    unsigned char b[3];
    FILE* file = 0;

    if(!pattern) { embLog_error("format-t09.c readT09(), pattern argument is null\n"); return 0; }
    if(!fileName) { embLog_error("format-t09.c readT09(), fileName argument is null\n"); return 0; }

    file = fopen(fileName, "rb");
    if(!file)
    {
        embLog_error("format-t09.c readT09(), cannot open %s for reading\n", fileName);
        return 0;
    }

    fseek(file, 0x0C, SEEK_SET);

    while(fread(b, 1, 3, file) == 3)
    {
        int stitchType = NORMAL;
        int b1 = b[0];
        int b2 = b[1];
        unsigned char commandByte = b[2];
        if(commandByte == 0x00)
        {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        if (commandByte & 0x10) stitchType = STOP;
        if (commandByte & 0x20) b1 = -b1;
        if (commandByte & 0x40) b2 = -b2;

        embPattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    fclose(file);
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeT09(EmbPattern* pattern, const char* fileName)
{
    if(!pattern) { embLog_error("format-t09.c writeT09(), pattern argument is null\n"); return 0; }
    if(!fileName) { embLog_error("format-t09.c writeT09(), fileName argument is null\n"); return 0; }
    return 0; /*TODO: finish writeT09 */
}

/* kate: bom off; indent-mode cstyle; indent-width 4; replace-trailing-space-save on; */
