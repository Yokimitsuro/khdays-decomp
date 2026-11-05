/* Loads the archive tables of the default ROM archive. */
extern void *FS_LoadArchiveTables();
extern char fsi_arc_rom;

void *FS_TryLoadTable(void *mem, unsigned int size) {
    return FS_LoadArchiveTables(&fsi_arc_rom, mem, size);
}
