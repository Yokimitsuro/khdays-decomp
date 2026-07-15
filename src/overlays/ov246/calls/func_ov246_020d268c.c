/* Spawn a registry entry (func_0203c5c0, size 0x34, cbs ce190/ce234) into *entry, stash the
 * 4 spawn args in entry[0..3], copy the owner's two facing vectors (owner->f398+0x14 and
 * owner+0xb0, the latter bumped +0x300 on Y) into entry[4..6]/[7..9], and transform each
 * against its target (func_0203ca30 into param_2+4 / param_3+4). Returns the spawn result. */
struct vec { int x, y, z; };
extern int func_0203c5c0(int list, int a, int b, void *cb2, void *cb1, int **out);
extern void func_0203ca30(int dst, int *src);
extern void func_ov246_020d29fc(void);
extern void func_ov246_020d2958(void);
int func_ov246_020d268c(int param_1, int param_2, int param_3, int param_4) {
    int *entry;
    int r = func_0203c5c0(*(int *)(param_1 + 0x3c), 100, 0x34,
                          &func_ov246_020d2958, &func_ov246_020d29fc, &entry);
    entry[0] = param_1;
    entry[1] = param_2;
    entry[2] = param_3;
    entry[3] = param_4;
    *(struct vec *)(entry + 4) = *(struct vec *)(*(int *)(*entry + 0x398) + 0x14);
    func_0203ca30(entry[1] + 4, entry + 4);
    *(struct vec *)(entry + 7) = *(struct vec *)(*entry + 0xb0);
    entry[8] += 0x300;
    func_0203ca30(entry[2] + 4, entry + 7);
    return r;
}
