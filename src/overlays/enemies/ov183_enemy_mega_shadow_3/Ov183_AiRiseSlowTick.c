/* Raises the actor out of the ground (its height scale, +0x394) over 0x555; then continues when the watched flag clears. */

#include "game/engine.h"

extern int FX_Div();
extern int SetIndexedSlot();

void Ov183_AiRiseSlowTick(int *s)
{
    int *a = (int *)s[0];
    int *b = (int *)s[1];
    int r, d, lo, hi;
    int *c;

    *(int *)((char *)b + 0x1c) = *(int *)((char *)b + 0x1c) + *(int *)((char *)a + 0x2c);
    r = FX_Div(*(int *)((char *)b + 0x1c), 0x555);
    if (r > 0x1000)
        r = 0x1000;
    *(int *)((char *)b[0] + 0x394) = r;

    if (*(unsigned char *)(*(int *)((char *)b + 0xc)) != 0)
        return;

    c = (int *)b[0];
    lo = *(int *)((char *)c + 0x224);
    hi = *(int *)((char *)c + 0x228);
    d = hi - lo;
    if (d < 0)
        d = -d;
    d = d + 1;
    *(int *)((char *)b + 0x74) = lo + RandNextScaled(d);

    *(signed char *)((char *)b[0] + 0x1c7) = 2;
    SetIndexedSlot(s, *(signed char *)((char *)s + 0x20), 0);
}
