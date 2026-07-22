/* Bump-allocates `size` bytes with `align` alignment out of the low end of the arena. */
extern char *OS_GetArenaLo(int arena);
extern char *OS_GetArenaHi(int arena);
extern void OS_SetArenaLo(int arena, char *lo);

void *OS_AllocFromArenaLo(int arena, unsigned int size, unsigned int align) {
    char *lo = OS_GetArenaLo(arena);
    char *start;
    char *end;
    if (lo == 0) {
        return 0;
    }
    start = (char *)(~(align - 1) & (unsigned int)(lo + align - 1));
    end = (char *)(~(align - 1) & (unsigned int)(start + size + align - 1));
    if (end > OS_GetArenaHi(arena)) {
        return 0;
    }
    OS_SetArenaLo(arena, end);
    return start;
}
