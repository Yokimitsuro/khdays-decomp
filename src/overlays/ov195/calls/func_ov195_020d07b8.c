/* obj is walked forward with a BYTE cast (`(int *)((char *)obj + 0x18)`), not int
 * arithmetic: reading the owner and stepping in one go is what gives the ROM's
 * post-indexed `ldr r0,[r4],#0x18`. Same form as ov247_020d281c.
 * `v = obj[3] = f(...)` in that order stores the raw r0; declaration order `r` then `q`
 * gives the ROM's stack layout. */
struct vec { int x, y, z; };
struct quat { int x, y, z, w; };
extern int  func_0203d040();
extern void func_0202f188();
extern void func_0202ed60();
extern void func_0202ef54();
extern void func_0203c9d0();
extern struct quat data_02042264;
extern struct vec data_02041dc8;

void func_ov195_020d07b8(int *self) {
    int *obj = (int *)self[1];
    struct quat r;
    struct quat q;
    int v;
    int owner;

    v = obj[3] = func_0203d040(obj[3], obj[4], obj[5], 0);
    func_0202f188(&r, &data_02042264, v);
    func_0202ed60(&q, &data_02042264, *obj + 0x124);
    func_0202ef54(&q, &q, &r);
    func_0203c9d0(*obj + 0xa0, &q);
    if (obj[0xd] > 0) {
        obj[0xd] = obj[0xd] - *(int *)(self[0] + 0x2c);
    }
    owner = *obj;
    obj = (int *)((char *)obj + 0x18);
    *(struct vec *)(owner + 0xf0) = *(struct vec *)obj;
    *(struct vec *)obj = data_02041dc8;
}
