/*
 * func_ov282_020d0f68 -- x3 (ov210/211/282). AI-state tick: pick a melee reaction toward the target.
 * state = *(int**)(self+4). With a target (state[8]!=0): dir = target(+0x190) - *state(+0xb0);
 * forward = transform(*state+0xa0, data_02042258). dot = dir . forward. Read facing bit0 at
 * *state+0x17a. Four-way pick, each leaf spelled out (the ROM shares no tail):
 *   dot > 0 (in front):  bit0 -> attack 2, else attack 4; heading = atan2(dir.x, dir.z)
 *   dot <= 0 (behind):   bit0 -> attack 3, else attack 5; heading = atan2(dir.x, dir.z) + 0x3244 (pi)
 * state[9]=state[10]=heading, hand off to 020d10e8. No target (state[8]==0, out-of-line tail): fire
 * attack 2 and hand off to 020d10e8.
 */
struct vec { int x, y, z; };
struct b17a { unsigned char b0 : 1; };
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_0202f384(void *dst, void *src, void *m);
extern int  VEC_DotProduct(void *a, void *b);
extern void func_ov107_020c9264(int a, int b, int c);
extern int  func_020050b4(int x, int z);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov282_020d10f4(void);
extern int  data_02042258;

void func_ov282_020d0f68(int self) {
    int *state = *(int **)(self + 4);
    struct vec w;
    struct vec v;
    int a;

    if (state[8] != 0) {
        VEC_Subtract((void *)(state[8] + 0x190), (void *)(*state + 0xb0), &v);
        func_0202f384(&w, (void *)(*state + 0xa0), &data_02042258);
        if (VEC_DotProduct(&v, &w) > 0) {
            if (((struct b17a *)(*state + 0x17a))->b0) {
                func_ov107_020c9264(*state, 2, 0);
                a = func_020050b4(v.x, v.z);
                state[10] = a;
                state[9] = a;
                func_0203c634(self, *(signed char *)(self + 0x20), (int)&func_ov282_020d10f4);
                return;
            }
            func_ov107_020c9264(*state, 4, 0);
            a = func_020050b4(v.x, v.z);
            state[10] = a;
            state[9] = a;
            func_0203c634(self, *(signed char *)(self + 0x20), (int)&func_ov282_020d10f4);
            return;
        }
        if (((struct b17a *)(*state + 0x17a))->b0) {
            func_ov107_020c9264(*state, 3, 0);
            a = func_020050b4(v.x, v.z) + 0x3244;
            state[10] = a;
            state[9] = a;
            func_0203c634(self, *(signed char *)(self + 0x20), (int)&func_ov282_020d10f4);
            return;
        }
        func_ov107_020c9264(*state, 5, 0);
        a = func_020050b4(v.x, v.z) + 0x3244;
        state[10] = a;
        state[9] = a;
        func_0203c634(self, *(signed char *)(self + 0x20), (int)&func_ov282_020d10f4);
        return;
    }
    func_ov107_020c9264(*state, 2, 0);
    func_0203c634(self, *(signed char *)(self + 0x20), (int)&func_ov282_020d10f4);
}
