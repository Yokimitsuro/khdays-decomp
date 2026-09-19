/* func_ov253_020d1b80 -- aim setup: takes the scene camera's look direction (+0x20 minus
 * +0x14), keeps its length at +8 and builds the +0xc rotation to face it from data_02042258;
 * the +4 item's +0x74 position is kept at +0x20, the rotation's forward scaled by the length
 * gives an aim point kept at least 1.0 above the +0x24 height, which is sent as event 4 to the
 * owner's +0x74 handler when present; the +0x1c timer clears and slots 1 / 2 take 020d1d28 /
 * 020d1cf0. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov022_02083f0c(void);
extern int func_ov002_0204cb68(int handle);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_0202ed60(void *rotation, const Vec3 *from, const Vec3 *to);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int OS_IsThreadAvailable_0x020c9848();
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042258;
extern void func_ov253_020d1d28(void);
extern void func_ov253_020d1cf0(void);

void func_ov253_020d1b80(int *node) {
    int *state = (int *)node[1];
    Vec3 dir;
    Vec3 aim;
    Vec3 fwd;
    int cam;
    int obj;
    int arg;

    cam = func_ov002_0204cb68(func_ov022_02083f0c());
    VEC_Subtract((Vec3 *)(cam + 0x20), (Vec3 *)(cam + 0x14), &dir);
    state[2] = func_01ff8d18(&dir, &dir);
    func_0202ed60((void *)(state + 3), &data_02042258, &dir);
    *(Vec3 *)(state + 8) = *(Vec3 *)(state[1] + 0x74);
    func_0202f384(&fwd, (void *)(state + 3), &data_02042258);
    func_01ffa724(state[2], &fwd, &aim);
    VEC_Add(&aim, (Vec3 *)(state + 8), &aim);
    if (aim.y < state[9] + 0x1000) {
        aim.y = state[9] + 0x1000;
    }
    if (*(int *)(OS_IsThreadAvailable_0x020c9848() + 0x74) != 0) {
        obj = OS_IsThreadAvailable_0x020c9848();
        arg = func_ov022_02083f0c();
        (*(void (**)(int, int, Vec3 *))(obj + 0x74))(arg, 4, (Vec3 *)(state + 8));
    }
    state[7] = 0;
    func_0203c634(node, 1, func_ov253_020d1d28);
    func_0203c634(node, 2, func_ov253_020d1cf0);
}
