/* AI step: raises the actor out of the ground (its height scale at +0x390, the model's Y scale,
 * grows with the timer up to 1.0); once the gate byte clears, picks a random range between the limits at +0x224/+0x228, queues action 2 and clears
 * the step handler. */

#include "game/engine.h"

extern int FX_Div();
extern int SetIndexedSlot();

void Ov277_AiRiseTick(int *s)
{
    int *a = (int *)s[0];
    int *b = (int *)s[1];
    int r, d, lo, hi;
    int *c;

    *(int *)((char *)b + 0x44) = *(int *)((char *)b + 0x44) + *(int *)((char *)a + 0x2c);
    r = FX_Div(*(int *)((char *)b + 0x44), 0x555);
    if (r > 0x1000)
        r = 0x1000;
    *(int *)((char *)b[0] + 0x390) = r;

    if (*(unsigned char *)(*(int *)((char *)b + 0xc)) != 0)
        return;

    c = (int *)b[0];
    lo = *(int *)((char *)c + 0x224);
    hi = *(int *)((char *)c + 0x228);
    d = hi - lo;
    if (d < 0)
        d = -d;
    d = d + 1;
    *(int *)((char *)b + 0x4c) = lo + RandNextScaled(d);

    *(signed char *)((char *)b[0] + 0x1c7) = 2;
    SetIndexedSlot(s, *(signed char *)((char *)s + 0x20), 0);
}
