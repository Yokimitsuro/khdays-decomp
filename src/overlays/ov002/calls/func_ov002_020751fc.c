/*
 * Count the table's entries, map each one, and hand the resulting list on.
 *
 * The table is walked eight bytes at a time starting one entry in, and each entry is turned
 * into an item by 02021948; the ten items live on the stack and go to ov002_0206cd84 with the
 * count. The return is always 1.
 *
 * The walking cursor is the PARAMETER itself, not a local, and that is what the ROM requires:
 * a local pointer gets r4 and pushes the array cursor to r5, while the parameter reuses its own
 * storage, takes r5 and leaves r4 for the array. The advance is written before the count call
 * so the plus eight lands ahead of the branch-and-link with the parameter spill interleaved
 * between the two adds, which is why the original is passed to that call through a saved copy.
 */

extern int func_02021980(void *a, void *b);
extern void *func_02021948(void *a, void *entry);
extern void func_ov002_0206cd84(int count, void **items);

int func_ov002_020751fc(void *a, char *table) {
    void *items[10];
    int count;
    int i;
    char *first = table;

    table += 8;
    count = func_02021980(a, first);
    for (i = 0; i < count; i++) {
        void *x = func_02021948(a, table);
        table += 8;
        items[i] = x;
    }
    func_ov002_0206cd84(count, items);
    return 1;
}
