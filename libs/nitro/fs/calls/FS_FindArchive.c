extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern unsigned int FSi_GetPackedName(const char *name, int len);
extern char *data_02046308;

/* Looks up a mounted archive by its (packed) four-character name. */
void *FS_FindArchive(const char *name, int len) {
    unsigned int packed = FSi_GetPackedName(name, len);
    int enabled = OS_DisableInterrupts();
    char *arc = *(char **)&data_02046308;
    while (arc != 0 && *(unsigned int *)arc != packed) {
        arc = *(char **)(arc + 4);
    }
    OS_RestoreInterrupts(enabled);
    return arc;
}
