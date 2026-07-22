/* Rewinds a directory handle to entry `id` and re-issues the read command. */
extern void *FSi_TranslateCommand();

void *FSi_SeekDirDirect(char *file, unsigned short id) {
    *(int *)(file + 0xc) |= 4;
    *(int *)(file + 0x30) = *(int *)(file + 8);
    *(int *)(file + 0x38) = 0;
    *(unsigned short *)(file + 0x36) = 0;
    *(unsigned short *)(file + 0x34) = id;
    return FSi_TranslateCommand(file, 2);
}
