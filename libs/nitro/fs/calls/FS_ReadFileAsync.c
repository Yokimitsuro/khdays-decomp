/* Asynchronous read: FSi_ReadFileCore(file, dst, len, 1). */
extern void *FSi_ReadFileCore();

void *FS_ReadFileAsync(void *file, void *dst, int len) {
    return FSi_ReadFileCore(file, dst, len, 1);
}
