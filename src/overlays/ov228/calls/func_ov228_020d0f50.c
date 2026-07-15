/* c634 handler: notify func_ov107_020c9264(owner,0x10,0), push a shared constant vec
 * (data_02041dc8, mode 0xb) then the owner's local-offset vec (owner+0x494, mode 4) via
 * func_ov107_020c0b90, clear obj+0x62, and dispatch into func_ov228_020d0ff0. */
struct vec { int x, y, z; };
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_ov107_020c0b90(int owner, int mode, struct vec v, int flag);
extern void func_0203c634(int self, int index, void *cb);
extern struct vec data_02041dc8;
extern void func_ov228_020d0ff0(void);
void func_ov228_020d0f50(int self) {
    int *obj = *(int **)(self + 4);
    func_ov107_020c9264(*obj, 0x10, 0);
    func_ov107_020c0b90(*obj, 0xb, data_02041dc8, 0);
    func_ov107_020c0b90(*obj, 4, *(struct vec *)(*obj + 0x494), 0);
    *(char *)((char *)obj + 0x62) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov228_020d0ff0);
}
