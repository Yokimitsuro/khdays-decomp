/*
 * NON-MATCHING: 408B vs 400B. The hard part -- the two duplicated bit-0-toggle blocks -- is reproduced
 * (1-bit bitfield read for the shift-form bit extraction; each branch written out in full so mwcc does
 * not factor the shared toggle). Residual: small codegen-ordering diffs -- the compound skip condition
 * `!((flags&8)&&(flags&0x80)&&(*msg>>16==0x80))` computes the u16 flags / the tests in a different
 * order than the ROM, and the `msg[10]=dmg` store is scheduled one slot later. A few instructions of
 * accumulated scheduling; logic and structure otherwise match. Left parked pending the exact u16-flags
 * form.
 */
/*
 * func_ov185_020ce40c -- x3 (ov185/...). Apply an incoming hit: subtract HP, clamp, publish, react.
 * state = *(self+0x214). Do nothing (return 0) unless HP *(s16)(self+0x21a) > 0. Compute the damage
 * dealt via 020c89e8, store it in msg[10], and drop HP by it, clamped to [0, guard *(s16)(self+0x218)].
 * Record the attacker p2 at state[0x13] and the hit vector msg[1..3] at state[0x14..0x16]. If HP hit 0
 * set state mode 6; else if the "launch" bit 0x8000 of msg[0] is set, mode 5. Finally, unless the hit
 * was a specific ignored combo, flip the alternating-foot bit 0 of *(state+0x6c) and spawn reaction
 * 0x120: for a guard hit (msg[0] & 0x22) the new foot picks facing 2/3, otherwise 0/1.
 */
struct vec3 { int x, y, z; };

struct b1 { unsigned char lo : 1; unsigned char hi : 7; };

extern int func_ov107_020c89e8(int self, unsigned *msg, unsigned *msg2, int hp);
extern void func_ov107_020c5af8(int self, int kind, int facing, int owner);

int func_ov185_020ce40c(int self, int attacker, unsigned *msg, int p4) {
    int *state = *(int **)(self + 0x214);

    if (*(short *)(self + 0x21a) <= 0) {
        return 0;
    }
    {
        int dmg = func_ov107_020c89e8(self, msg, msg, (int)*(short *)(self + 0x21a));
        int rem = (int)*(short *)(self + 0x21a) - dmg;
        int clamped;
        msg[10] = dmg;
        if (rem < 0) {
            clamped = 0;
        } else {
            clamped = *(short *)(self + 0x218);
            if (rem <= clamped) {
                clamped = rem;
            }
        }
        *(short *)(self + 0x21a) = (short)clamped;
    }
    state[0x13] = attacker;
    *(struct vec3 *)&state[0x14] = *(struct vec3 *)&msg[1];
    if (*(short *)(self + 0x21a) == 0) {
        *(unsigned char *)(*state + 0x1c7) = 6;
    } else if (((unsigned short)*msg & 0x8000) != 0) {
        *(unsigned char *)(*state + 0x1c7) = 5;
    }
    if ((int)msg[10] > 0 &&
        !(((unsigned short)*msg & 8) != 0 && ((unsigned short)*msg & 0x80) != 0 &&
          (*msg >> 0x10) == 0x80)) {
        if ((*msg & 0x22) != 0) {
            unsigned char b = *(unsigned char *)((char *)state + 0x6c);
            unsigned char nb = (b & ~1) | (((((struct b1 *)&b)->lo) + 1) & 1);
            int facing = (((struct b1 *)&nb)->lo) ? 2 : 3;
            *(unsigned char *)((char *)state + 0x6c) = nb;
            func_ov107_020c5af8(self, 0x120, (unsigned short)facing, state[0x11]);
        } else {
            unsigned char b = *(unsigned char *)((char *)state + 0x6c);
            unsigned char nb = (b & ~1) | (((((struct b1 *)&b)->lo) + 1) & 1);
            int facing = (((struct b1 *)&nb)->lo) ? 0 : 1;
            *(unsigned char *)((char *)state + 0x6c) = nb;
            func_ov107_020c5af8(self, 0x120, (unsigned short)facing, state[0x11]);
        }
    }
    return 1;
}
