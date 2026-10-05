/* Kick anim 7, seed +0x54=0x3000, store speed*30/20 into +0x24, clear bit0 of +0x3d4, resolve a
 * value from obj+0xa0 into +0x28/+0x2c and dispatch 020d44f8. */
extern int Ov107_PostTagUpdate(int, int, int);
extern int Vec3TransformViaTempMtx(void *, int, void *);
extern short FX_Atan2(int, int);
extern int SetIndexedSlot(int, int, void *);
extern int data_02042258;
extern int Ov278_AiStalkStart(int);
void Ov278_AiEnterStalk(int param_1) {
    int owner = *(int *)(param_1 + 4);
    Ov107_PostTagUpdate(*(int *)owner, 7, 0);
    *(int *)(*(int *)owner + 0x54) = 0x3000;
    *(int *)(owner + 0x24) = *(int *)(*(int *)param_1 + 0x2c) * 30 / 20;
    *(int *)(*(int *)owner + 0x3d4) &= ~1;
    int buf[3];
    Vec3TransformViaTempMtx(buf, *(int *)owner + 0xa0, &data_02042258);
    int result = FX_Atan2(buf[0], buf[2]);
    *(int *)(owner + 0x28) = result;
    *(int *)(owner + 0x2c) = result;
    SetIndexedSlot(param_1, *(signed char *)(param_1 + 0x20), (void *)&Ov278_AiStalkStart);
}
