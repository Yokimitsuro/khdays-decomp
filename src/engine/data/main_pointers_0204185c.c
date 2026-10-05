/* main .rodata pointer tables, 0x0204185c-0x02041880.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern void FSi_CloseFileCommand(void);
extern void FSi_FindPathCommand(void);
extern void FSi_GetPathCommand(void);
extern void FSi_OpenFileDirectCommand(void);
extern void FSi_OpenFileFastCommand(void);
extern void FSi_ReadDirCommand(void);
extern void FSi_ReadFileCommand(void);
extern void FSi_SeekDirCommand(void);
extern void FSi_WriteFileCommand(void);

void *const data_0204185c[9] = {

    &FSi_ReadFileCommand,

    &FSi_WriteFileCommand,

    &FSi_SeekDirCommand,

    &FSi_ReadDirCommand,

    &FSi_FindPathCommand,

    &FSi_GetPathCommand,

    &FSi_OpenFileFastCommand,

    &FSi_OpenFileDirectCommand,

    (void *)FSi_CloseFileCommand,

};
