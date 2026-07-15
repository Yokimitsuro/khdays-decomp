/* c634 handler: run the guard func_ov225_020d127c; if <0, dispatch null. Compute the aim
 * angle obj[0x16] = atan2(dir), where dir = VEC_Subtract(obj+0x38, obj[2]). If the target's
 * busy flag (*obj->f0+0x384 +0xad) is clear: try func_ov225_020d0d04; on failure dispatch
 * null, otherwise latch owner+0x1c7=2 and dispatch null. If the flag is set, hand the angle
 * to func_ov225_020d22f0. */
struct vec { int x, y, z; };
extern int func_ov225_020d127c(int self, int a);
extern void func_0203c634(int self, int index, void *cb);
extern void VEC_Subtract(int *a, int *b, struct vec *out);
extern int func_020050b4(int dx, int dz);
extern int func_ov225_020d0d04(int self, int r);
extern void func_ov225_020d22f0(int self, int arg);
void func_ov225_020d2730(int self) {
    int *obj = *(int **)(self + 4);
    struct vec buf;
    int r = func_ov225_020d127c(self, 0);
    if (r < 0) {
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    VEC_Subtract(obj + 0xe, (int *)obj[2], &buf);
    obj[0x16] = func_020050b4(buf.x, buf.z);
    if (*(unsigned char *)(*(int *)(*obj + 0x384) + 0xad) == 0) {
        if (func_ov225_020d0d04(self, r) != 0) {
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }
        *(char *)(*obj + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    func_ov225_020d22f0(self, obj[0x16]);
}
