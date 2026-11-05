/* Action 0xb: plays anim 5, restarts the timer (+0x44) and installs Ov114_AiSinkTick, which
 * flattens the actor into the ground and leaves it there (action 0xc). */

extern void Ov107_PostTagUpdate(int v, int a, int b);
extern void SetIndexedSlot(void *a, int b, void *cb);
extern void Ov114_AiSinkTick(void);

void Ov114_AiEnterSinkAndStay(char *a) {
    char *p = *(char **)(a + 0x4);
    Ov107_PostTagUpdate(*(int *)p, 5, 0);
    *(int *)(p + 0x44) = 0;
    SetIndexedSlot(a, *(signed char *)(a + 0x20), Ov114_AiSinkTick);
}
