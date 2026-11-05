/* Set bit 0 of the u16 at *(child)+0x1ae, clear bit 0 of the low byte at *(*child+0x388)+8,
 * play the anim (ov107 mode 7), clear +0x44, set *(*child)+0x390 = 0xcc and register the handler. */
struct b8 { unsigned int f : 8; };
extern void Ov107_PostTagUpdate(int a, int b, int c);
extern int SetIndexedSlot(int a, int b, void *handler);
extern void Ov114_RiseFromGround(int);
void Ov114_AiEnterPursuit(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(unsigned short *)(*(int *)child + 0x1ae) |= 1;
    ((struct b8 *)(*(int *)(*(int *)child + 0x388) + 8))->f &= ~1;
    Ov107_PostTagUpdate(*(int *)child, 7, 0);
    *(int *)(child + 0x44) = 0;
    *(int *)(*(int *)child + 0x390) = 0xcc;
    SetIndexedSlot(param_1, *(signed char *)(param_1 + 0x20), (void *)&Ov114_RiseFromGround);
}
