/* Physics tick of an ov254 helper, skipped while the actor's +0x60 low byte has bit 7. In moves 1
 * and 2 the actor's +0xf0 velocity mirrors the +0x1c one; in move 3 it does too and: a pending
 * bounce (+0x40) is cleared on landing (+0x17a bit 0); after one (+0x44) the horizontal velocity
 * decays by 0xe80 on the ground with no source (+4) or 0xfb0 otherwise; the +0x20 vertical speed
 * falls by the frame rate * 0xd0 / 0x88 (zeroed when landed and not rising); on the ground a
 * velocity under 1/16 is zeroed and the bounce flag +0x44 is set. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
struct Hw60 { u16 lo : 8; u16 hi : 8; };
struct Flag17a { u8 b0 : 1; };

extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern const Vec3 data_02041dc8;

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov254_020d31c0(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int actor = *state;
    int onGround;
    int move;
    int f;

    if ((((struct Hw60 *)(actor + 0x60))->lo & 0x80) != 0) {
        return;
    }
    onGround = ((struct Flag17a *)(actor + 0x17a))->b0;
    move = *(signed char *)(actor + 0x100 + 0xc6);
    switch (move) {
    case 1:
    case 2:
        *(Vec3 *)(actor + 0xf0) = *(Vec3 *)(state + 7);
        break;
    case 3:
        *(Vec3 *)(actor + 0xf0) = *(Vec3 *)(state + 7);
        if (state[0x10] != 0) {
            if (onGround) {
                state[0x10] = 0;
            }
        } else if (state[0x11] != 0) {
            f = (onGround && state[1] == 0) ? 0xe80 : 0xfb0;
            state[7] = FX_Mul(state[7], f);
            state[9] = FX_Mul(state[9], f);
        }
        state[8] = (onGround && state[8] <= 0) ? 0 : state[8] + *(int *)(node[0] + 0x2c) * -0xd0 / 0x88;
        if (!onGround) {
            return;
        }
        if (func_01ff8d18((Vec3 *)(state + 7), &dir) < 0x100) {
            *(Vec3 *)(state + 7) = data_02041dc8;
        }
        state[0x11] = 1;
        break;
    }
}
