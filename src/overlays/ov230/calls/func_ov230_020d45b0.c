/* c634 handler: push the owner's local offset vector (owner+0x494) to it twice via
 * func_ov107_020c0b90 (modes 9 then 3), clear obj[0x13] and the two flag bytes at
 * obj+0x61/+0x62, and dispatch via func_0203c634. */
struct vec { int x, y, z; };
extern void func_ov107_020c0b90(int owner, int mode, struct vec v, int flag);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov230_020d464c(void);
void func_ov230_020d45b0(int self) {
    int *obj = *(int **)(self + 4);
    func_ov107_020c0b90(*obj, 9, *(struct vec *)(*obj + 0x494), 0);
    func_ov107_020c0b90(*obj, 3, *(struct vec *)(*obj + 0x494), 0);
    obj[0x13] = 0;
    *(char *)((char *)obj + 0x61) = 0;
    *(char *)((char *)obj + 0x62) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov230_020d464c);
}
