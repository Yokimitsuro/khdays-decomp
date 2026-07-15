/* c634 handler: run the guard func_ov229_020d2f84; if it fails (<0), dispatch null. Else,
 * only when the parent's flag byte obj[1]+0xad is clear: notify func_ov107_020c9264(owner,
 * 0x11,0), push the owner's local-offset vec (owner+0x494) via func_ov107_020c0b90 mode 4,
 * clear obj+0x61 and obj[2], and dispatch via func_0203c634. */
struct vec { int x, y, z; };
extern int func_ov229_020d2f84(int self);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_ov107_020c0b90(int owner, int mode, struct vec v, int flag);
extern void func_ov229_020d4ce0(void);
void func_ov229_020d4c30(int self) {
    int *obj = *(int **)(self + 4);
    if (func_ov229_020d2f84(self) < 0) {
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    if (*(unsigned char *)(obj[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*obj, 0x11, 0);
    func_ov107_020c0b90(*obj, 4, *(struct vec *)(*obj + 0x494), 1);
    *(char *)((char *)obj + 0x61) = 0;
    obj[2] = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov229_020d4ce0);
}
