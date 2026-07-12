/* Kick anim 7, seed +0x54=0x3000, store speed*30/15 into +0x24, clear bit0 of +0x3d4, resolve a
 * value from obj+0xa0 into +0x28/+0x2c and dispatch 020d4544. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0202f384(void *, int, void *);
extern int func_020050b4(int, int);
extern int func_0203c634(int, int, void *);
extern int data_02042258;
extern int func_ov236_020d4544(int);
void func_ov236_020d4498(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 7, 0);
    *(int *)(*(int *)owner + 0x54) = 0x3000;
    *(int *)(owner + 0x24) = *(int *)(*(int *)param_1 + 0x2c) * 30 / 20;
    *(int *)(*(int *)owner + 0x3d4) &= ~1;
    int buf[3];
    func_0202f384(buf, *(int *)owner + 0xa0, &data_02042258);
    int result = func_020050b4(buf[0], buf[2]);
    *(int *)(owner + 0x28) = result;
    *(int *)(owner + 0x2c) = result;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov236_020d4544);
}
