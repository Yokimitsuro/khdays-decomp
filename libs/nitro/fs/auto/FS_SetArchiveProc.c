/* Installs the archive hook, or clears both halves when either is missing. */
void FS_SetArchiveProc(char *arc, void *proc, unsigned int flags) {
    if (flags == 0) {
        proc = 0;
    } else if (proc == 0) {
        flags = 0;
    }
    *(void **)(arc + 0x54) = proc;
    *(unsigned int *)(arc + 0x58) = flags;
}
