/* c634 handler: copy obj[8..10] into obj[5..7], charge the timer obj[0x17] by self->f0->f2c.
 * While still below obj[0x18]+0x800, re-arm via func_ov223_020d09cc with mode 2/4 (by the
 * obj[0x1e] flag). Once past it, notify func_ov107_020c9264 with mode 0xa/0xe, and when the
 * flag is clear push a shared constant vec (data_02041dc8), then dispatch via func_0203c634. */
struct vec { int x, y, z; };
extern void func_ov107_020c9264(int owner, int mode, int b);
extern void func_ov107_020c0b90(int owner, int mode, struct vec v, int flag);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov223_020d09cc(int *obj, int mode, int b);
extern struct vec data_02041dc8;
extern void func_ov223_020d2ea8(void);
void func_ov223_020d2dd8(int self) {
    int *obj = *(int **)(self + 4);
    int t, flag;
    *(struct vec *)(obj + 5) = *(struct vec *)(obj + 8);
    t = (obj[0x17] += *(int *)(*(int *)self + 0x2c));
    flag = obj[0x1e];
    if (t >= obj[0x18] + 0x800) {
        func_ov107_020c9264(*obj, flag != 0 ? 0xa : 0xe, 0);
        if (obj[0x1e] == 0) {
            func_ov107_020c0b90(*obj, 4, data_02041dc8, 1);
        }
        func_0203c634(self, *(signed char *)(self + 0x20), &func_ov223_020d2ea8);
        return;
    }
    func_ov223_020d09cc(obj, flag != 0 ? 2 : 4, 0);
}
