extern int func_ov002_0207285c(int slot);
extern void func_ov002_02077df0(void *node);
extern char data_ov002_0207fa28;

/* Ticks every queued object that still has a pending request, then marks the queue dirty. */
void func_ov002_02077e68(void) {
    int i;
    int off = 0;
    char *node;
    char *next;
    for (i = 0; i < 0x18; i++) {
        if (func_ov002_0207285c(i) >= 0) {
            node = *(char **)(*(char **)((char *)&data_ov002_0207fa28 + 4) + off + 0xc4);
            while (node != 0) {
                next = *(char **)node;
                if (*(int *)(node + 0x28) != 0) {
                    func_ov002_02077df0(node);
                }
                node = next;
            }
        }
        off += 0x184;
    }
    *(int *)(*(char **)((char *)&data_ov002_0207fa28 + 4) + 0x58) = 1;
}

/* PARK 2026-07-19: 76/76 bytes, MISMA rotacion exacta que `func_ov002_02078f60`
 * (i / off / next -> el ROM usa r6/r5/r4, mwcc r4/r6/r5). Ver la entrada de familia en
 * deferred-ties.md: "bucle de slots con offset de stride grande". NO probar formas nuevas de una
 * en una -- si alguien encuentra la buena, valen las tres a la vez. */
