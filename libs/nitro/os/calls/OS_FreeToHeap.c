extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void *DLExtract(void *list, void *node);
extern void *DLInsert(void *list, void *node);
extern char *data_02044590[];

/* Returns a block to its heap: unlink it from the allocated list and merge it into the free list. */
void OS_FreeToHeap(int arena, int heap, void *ptr) {
    char *info;
    char *cell;
    int enabled = OS_DisableInterrupts();
    info = data_02044590[arena];
    if (heap < 0) {
        heap = *(int *)info;
    }
    cell = *(char **)(info + 0x10) + heap * 12;
    ptr = (char *)ptr - 0x20;
    *(void **)(cell + 8) = DLExtract(*(void **)(cell + 8), ptr);
    *(void **)(cell + 4) = DLInsert(*(void **)(cell + 4), ptr);
    OS_RestoreInterrupts(enabled);
}
