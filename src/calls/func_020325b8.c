/* func_020325b8 -- set entry velocity/scale field and re-commit, MAIN.
 * For entry idx in the 0x8c-byte table at base, stores -(scale<<11) into field +0xc
 * (a fixed-point downward magnitude), then calls func_02031e50 to recompute/commit the
 * entry (passing base, entry+4, &base[1], entry). */
extern void func_02031e50(int *a, int *b, int *c, int d);
void func_020325b8(int *base, int idx, int scale) {
    char *e4;
    if (idx < 0) {
        return;
    }
    e4 = (char *)(base + 1) + idx * 0x8c;
    *(int *)((char *)base + idx * 0x8c + 0xc) = scale * -0x800;
    func_02031e50(base, (int *)e4, base + 1, (int)base + idx * 0x8c);
}
