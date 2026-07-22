/* func_ov107_020c2b50 -- find the child of `obj` whose id (the halfword at +2 of the entry) is
 * `id`; returns the ENTRY, not the list node, which is why the ROM's `ldr r0,[r0]` overwrites the
 * node pointer it was just handed. Returns 0 when the list runs out. */
extern int func_01fffd70(void *list);
extern int func_01fffd8c(void *list);

int func_ov107_020c2b50(int obj, unsigned short id) {
    int *node;
    int e;
    node = (int *)func_01fffd70((void *)(obj + 0x44));
    while (node != 0) {
        e = node[0];
        if (*(unsigned short *)(e + 2) == id) {
            return e;
        }
        node = (int *)func_01fffd8c((void *)(obj + 0x44));
    }
    return 0;
}
