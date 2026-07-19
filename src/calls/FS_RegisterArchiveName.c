extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void *FS_FindArchive(const char *name, int len);
extern unsigned int FSi_GetPackedName(const char *name, int len);
extern char data_02046308;

/* Adds an archive to the mount list under the given name. Fails if the name is already taken. */
int FS_RegisterArchiveName(char *arc, const char *name, int len) {
    int ok = 0;
    int enabled = OS_DisableInterrupts();
    char *cur;
    char *next;
    if (FS_FindArchive(name, len) == 0) {
        cur = *(char **)&data_02046308;
        if (cur == 0) {
            *(char **)&data_02046308 = arc;
            *(char **)((char *)&data_02046308 + 4) = arc;
            *(int *)((char *)&data_02046308 + 0xc) = 0;
            *(short *)((char *)&data_02046308 + 0xa) = 0;
            *(short *)((char *)&data_02046308 + 8) = 0;
        } else {
            next = *(char **)(cur + 4);
            while (next != 0) {
                cur = next;
                next = *(char **)(next + 4);
            }
            *(char **)(cur + 4) = arc;
            *(char **)(arc + 8) = cur;
        }
        *(unsigned int *)arc = FSi_GetPackedName(name, len);
        *(int *)(arc + 0x1c) |= 1;
        ok = 1;
    }
    OS_RestoreInterrupts(enabled);
    return ok;
}
