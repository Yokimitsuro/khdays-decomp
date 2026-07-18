/*
 * func_ov279_020d14e8 -- x3. AI-state tick: decay the aim offset, then give up when facing pressure.
 * Copy state[0xf..0x11] down to state[0xc..0xe]; scale state[0xf..0x11] by 0xb00 (decay). If
 * state[0xd] < 0x20, clear the +0x60 hi-byte bit 0x40. If the ready byte *(u8)(state[1]+0xad) is set,
 * keep waiting. Else, if neither facing bit0 at *state+0x17a / +0x17c is set, keep waiting. Otherwise
 * give up: if the pending target *(state[0]+0x25c) is non-null, latch it into state[2] and mark
 * *state[0]+0x1c7 = 8; else mark 2. Hand off via 0203c634 (cb=0).
 */
struct vec3 { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };
struct b1 { unsigned char b0 : 1; };
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_0203c634(int self, int idx, int cb);

void func_ov279_020d14e8(int *self) {
    int *state = (int *)self[1];
    int t;

    *(struct vec3 *)(state + 0xc) = *(struct vec3 *)(state + 0xf);
    func_01ffa724(0xb00, (void *)(state + 0xf), (void *)(state + 0xf));
    if (state[0xd] < 0x20) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x40;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (((struct b1 *)(*state + 0x17a))->b0 == 0 && ((struct b1 *)(*state + 0x17c))->b0 == 0) {
        return;
    }
    t = *(int *)(*state + 0x25c);
    if (t != 0) {
        state[2] = t;
        *(char *)(*state + 0x1c7) = 8;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
    } else {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
    }
}
