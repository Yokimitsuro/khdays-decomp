/*
 * func_ov210_020d31d8 -- x3 (ov210/211/282). AI-state tick: advance a lunge, then commit or wait.
 * Timer state[0xb] += owner_delta. Copy the working vec state[0x15..0x17] down to state[5..7]
 * (field-to-field) and ease state[0x16] -= 0x80. If the timer is still <= 0x800 and the facing bit0
 * at *state+0x17a is clear, keep waiting. Otherwise snap state[5..7] to the const vec data_02041dc8,
 * fire attack 0x17 (020c9264) and hand off to the 020d326c state.
 */
struct vec3 { int x, y, z; };
struct S210 { char pad[0x14]; struct vec3 a; char pad2[0x34]; struct vec3 b; };
struct b17a { unsigned char b0 : 1; };
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov210_020d326c(void);
extern struct vec3 data_02041dc8;

void func_ov210_020d31d8(int *self) {
    int *state = (int *)self[1];

    state[0xb] += *(int *)(*self + 0x2c);
    ((struct S210 *)state)->a = ((struct S210 *)state)->b;
    state[0x16] -= 0x80;
    if (state[0xb] <= 0x800) {
        if (((struct b17a *)(*state + 0x17a))->b0 == 0) {
            return;
        }
    }
    ((struct S210 *)state)->a = data_02041dc8;
    func_ov107_020c9264(*state, 0x17, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov210_020d326c);
}
