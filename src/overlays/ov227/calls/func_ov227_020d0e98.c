/* func_ov227_020d0e98 -- the move CHOOSER of the ov227 enemy (the ov221-family chooser without the
 * game-mode thresholds, with a ten-slot member table and an owner-health split): pick the next move
 * and re-arm the think timer. Returns 1 if a move ended up queued at ctx[0]+0x1c7, 0 if not.
 *
 * Two hard early-outs return 0: the busy byte at *(ctx[0]+0x384)+0xad and a think timer at
 * ctx[0x1a] that has not run down yet. Then a d100 is rolled and three facts gathered:
 *   charged  bit 0 of the byte at ctx[0]+0x17a
 *   clear    no live entry in the 10-slot table at ctx[0]+0x3ec (non-null with a non-zero +0x388)
 *   below    the thing at ctx[0]+0x3e8 sits lower than ctx[2][1] (its +0x194 minus ours is < 0)
 *
 *   target, near : <30 move 0x10 | <40 && clear move 8 | <70 && below move 0xb | move 9
 *   target, far  : mode 8 -> (<0x42 && below move 0xb | move 9)
 *                  else     <0 move 5 | <0x28 && clear move 8 | <0x41 && below move 0xb | move 9
 *   none,   near : health at most half -> <30 && clear move 8 | <60 move 0x10 | move 9
 *                  else                -> <15 && clear move 8 | <50 move 0x10 | move 9
 *   none,   far  : <0 && charged move 0xc | <0x28 && clear move 8 | move 9
 *
 * Every path then re-arms the timer with a uniform value between the two bounds at ctx[0]+0x224
 * and +0x228 (ctx[0x1a] = lo + rand(|hi - lo| + 1)) and reports whether +0x1c7 is no longer -1. */

typedef struct {
    unsigned char b0 : 1;
    unsigned char rest : 7;
} Bits8;

extern int func_02023eb4();
extern int func_ov002_0207298c(void);

int func_ov227_020d0e98(int self, int dist) {
    int *ctx;
    int roll;
    int charged;
    int clear;
    int below;
    int i;
    int p;
    int q;
    int lo;
    int d;

    ctx = *(int **)(self + 4);
    if (*(unsigned char *)(*(int *)(ctx[0] + 0x384) + 0xad) != 0) {
        goto fail;
    }
    if (ctx[0x1a] > 0) {
        goto fail;
    }

    roll = func_02023eb4(0x64);
    charged = ((Bits8 *)(ctx[0] + 0x17a))->b0;
    clear = 1;
    below = 0;

    for (i = 0; i < 0xa; i++) {
        p = ((int *)ctx[0])[i + 0xfb];
        if (p != 0 && *(int *)(p + 0x388) != 0) {
            break;
        }
    }
    clear &= (i >= 0xa);

    q = *(int *)(ctx[0] + 0x3e8);
    if (q != 0) {
        if (*(int *)(q + 0x194) - *(int *)(ctx[2] + 4) < 0) {
            below = 1;
        }
    }

    if (ctx[0x1e] != 0) {
        if (dist < 0x7000) {
            if (roll < 0x1e) {
                *(signed char *)(ctx[0] + 0x1c7) = 0x10;
            } else if (roll < 0x28 && clear != 0) {
                *(signed char *)(ctx[0] + 0x1c7) = 8;
            } else if (roll < 0x46 && below != 0) {
                *(signed char *)(ctx[0] + 0x1c7) = 0xb;
            } else {
                *(signed char *)(ctx[0] + 0x1c7) = 9;
            }
        } else if (func_ov002_0207298c() != 8) {
            if (roll < 0) {
                *(signed char *)(ctx[0] + 0x1c7) = 5;
            } else if (roll < 0x28 && clear != 0) {
                *(signed char *)(ctx[0] + 0x1c7) = 8;
            } else if (roll < 0x41 && below != 0) {
                *(signed char *)(ctx[0] + 0x1c7) = 0xb;
            } else {
                *(signed char *)(ctx[0] + 0x1c7) = 9;
            }
        } else if (roll < 0x42 && below != 0) {
            *(signed char *)(ctx[0] + 0x1c7) = 0xb;
        } else {
            *(signed char *)(ctx[0] + 0x1c7) = 9;
        }
    } else if (dist < 0x7000) {
        if (*(short *)(ctx[0] + 0x200 + 0x1a) <= *(short *)(ctx[0] + 0x200 + 0x18) / 2) {
            if (roll < 0x1e && clear != 0) {
                *(signed char *)(ctx[0] + 0x1c7) = 8;
            } else if (roll < 0x3c) {
                *(signed char *)(ctx[0] + 0x1c7) = 0x10;
            } else {
                *(signed char *)(ctx[0] + 0x1c7) = 9;
            }
        } else if (roll < 0xf && clear != 0) {
            *(signed char *)(ctx[0] + 0x1c7) = 8;
        } else if (roll < 0x32) {
            *(signed char *)(ctx[0] + 0x1c7) = 0x10;
        } else {
            *(signed char *)(ctx[0] + 0x1c7) = 9;
        }
    } else if (roll < 0 && charged != 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 0xc;
    } else if (roll < 0x28 && clear != 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 8;
    } else {
        *(signed char *)(ctx[0] + 0x1c7) = 9;
    }

    lo = *(int *)(ctx[0] + 0x224);
    d = *(int *)(ctx[0] + 0x228) - lo;
    if (d < 0) {
        d = -d;
    }
    ctx[0x1a] = func_02023eb4(d + 1) + lo;

    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        return 1;
    }
fail:
    return 0;
}
