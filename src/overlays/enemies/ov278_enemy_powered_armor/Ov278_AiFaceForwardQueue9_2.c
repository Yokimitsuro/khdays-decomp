/* Unless the +0x20 gate is busy, clear bit0 of +0x3d4, resolve a value from obj+0xa0 via
 * 0202f384/020050b4 into +0x28/+0x2c, latch sub-state 9 and dispatch. */
extern int Vec3TransformViaTempMtx(void *, int, void *);
extern short FX_Atan2(int, int);
extern int SetIndexedSlot(int, int, void *);
extern int data_02042258;
void Ov278_AiFaceForwardQueue9_2(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 0x20)) != 0) return;
    *(int *)(*(int *)owner + 0x3d4) &= ~1;
    int buf[3];
    Vec3TransformViaTempMtx(buf, *(int *)owner + 0xa0, &data_02042258);
    int result = FX_Atan2(buf[0], buf[2]);
    *(int *)(owner + 0x28) = result;
    *(int *)(owner + 0x2c) = result;
    *(unsigned char *)(*(int *)owner + 0x1c7) = 9;
    SetIndexedSlot(param_1, *(signed char *)(param_1 + 0x20), 0);
}
