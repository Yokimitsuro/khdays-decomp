/* main .rodata pointer tables, 0x0204185c-0x02041880.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern void func_0200a10c(void);
extern int FSi_FindPathCommand;
extern int FSi_GetPathCommand;
extern int FSi_OpenFileDirectCommand;
extern int FSi_OpenFileFastCommand;
extern int FSi_ReadDirCommand;
extern int FSi_ReadFileCommand;
extern int FSi_SeekDirCommand;
extern int FSi_WriteFileCommand;

void *const data_0204185c[9] = {

    &FSi_ReadFileCommand,

    &FSi_WriteFileCommand,

    &FSi_SeekDirCommand,

    &FSi_ReadDirCommand,

    &FSi_FindPathCommand,

    &FSi_GetPathCommand,

    &FSi_OpenFileFastCommand,

    &FSi_OpenFileDirectCommand,

    (void *)func_0200a10c,

};
