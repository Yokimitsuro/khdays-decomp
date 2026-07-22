/* Loads the archive tables of the default ROM archive. */
extern void *FS_LoadArchiveTables();
extern char data_02046334;

void *FS_TryLoadTable(void *mem, unsigned int size) {
    return FS_LoadArchiveTables(&data_02046334, mem, size);
}
