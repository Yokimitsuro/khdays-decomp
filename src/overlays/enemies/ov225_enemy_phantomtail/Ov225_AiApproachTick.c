/* Heads for the target (direct or rotated preset velocity); queues action 2 once within 0x2000. */

#include "game/ai_task.h"

extern int VEC_Subtract();
extern short FX_Atan2();
extern int VEC_Normalize();
extern int ScaleVec3Fx12();
extern int MTX_RotY33_();
extern int MTX_MultVec33();
extern int SetIndexedSlot();
extern short data_0203d210[];

struct sub {
    int f0;       /* +0x00 */
    int pad04;    /* +0x04 */
    int f8;       /* +0x08 */
    char pad0c[0x80 - 0x0c];
    int f80;      /* +0x80 */
    char pad84[0x190 - 0x84];
    char f190[1]; /* +0x190 */
    char pad191[0x1c7 - 0x191];
    unsigned char f1c7; /* +0x1c7 */
    char pad1c8[0x3fc - 0x1c8];
    int f3fc;     /* +0x3fc */
};

struct mid {
    struct sub *f0;   /* +0x00 */
    int pad04;        /* +0x04 */
    int f8;           /* +0x08 */
    char pad0c[0x14 - 0x0c];
    char f14[1];      /* +0x14 */
    char pad15[0x58 - 0x15];
    int f58;          /* +0x58 */
    char pad5c[0x78 - 0x5c];
    int f78;          /* +0x78 */
};

struct top {
    AI_TASK_FIELDS(struct mid)
};

void Ov225_AiApproachTick(struct top *a)
{
    struct mid *r4 = a->pState;
    int s24[3];
    int s0[9];
    int diff;

    struct sub *sub0;

    VEC_Subtract((char *)r4->f0 + 0x190, r4->f8, s24);
    r4->f58 = FX_Atan2(s24[0], s24[2]);
    sub0 = r4->f0;
    diff = VEC_Normalize(s24, s24) - sub0->f80;

    if (r4->f78 != 0) {
        ScaleVec3Fx12(0x100, s24, r4->f14);
    } else {
        long long p = (long long)r4->f58 * 0x28be60db9391LL + 0x80000000000LL;
        int h = (int)(p >> 32);
        int idx = (int)((unsigned)h << 4 >> 16) >> 4;
        MTX_RotY33_(s0, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
        MTX_MultVec33(r4->f0->f3fc + 0x2c, s0, r4->f14);
    }

    if (diff < 0x2000) {
        r4->f0->f1c7 = 2;
        SetIndexedSlot(a, a->slot, 0);
    }
}
