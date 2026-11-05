/* Plays anim 5 and installs the sub-object fade-in. */

extern void Ov107_PostTagUpdate(int v, int a, int b);
extern void SetIndexedSlot(void *a, int b, void *cb);
extern void Ov114_SinkIntoGround(void);

void Ov114_AiEnterFadeIn(char *a) {
    char *p = *(char **)(a + 0x4);
    Ov107_PostTagUpdate(*(int *)p, 5, 0);
    *(int *)(p + 0x44) = 0;
    SetIndexedSlot(a, *(signed char *)(a + 0x20), Ov114_SinkIntoGround);
}
