/*
 * func_ov209_020d4964 -- x3 (ov208/209/268). AI-state tick: advance an aim and give up when spent.
 * state[0x18] = owner_delta*30/20; state[0xd] = atan2(state[0x15], state[0x17]); ease
 * state[0x16] -= (delta*30<<8 + 0x800)>>12 (a Q12 step). Copy state[0x15..0x17] down to state[5..7]
 * (field-to-field). Once state[0x16] goes negative, mark *state+0x1c7 = 0xb.
 */
struct vec3 { int x, y, z; };
struct S208 { char pad[0x14]; struct vec3 a; char pad2[0x34]; struct vec3 b; };
extern int func_020050b4(int x, int z);

void func_ov209_020d4964(int *self) {
    int *state = (int *)self[1];

    state[0x18] = *(int *)(*self + 0x2c) * 0x1e / 20;
    state[0xd] = func_020050b4(state[0x15], state[0x17]);
    state[0x16] -= (int)((((long long)(*(int *)(*self + 0x2c) * 0x1e) << 8) + 0x800) >> 12);
    ((struct S208 *)state)->a = ((struct S208 *)state)->b;
    if (state[0x16] < 0) {
        *(char *)(*state + 0x1c7) = 0xb;
    }
}
