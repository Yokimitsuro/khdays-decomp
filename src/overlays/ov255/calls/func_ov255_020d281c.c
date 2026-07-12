/* Install the callback pointers and owner link on the child, clear a flag, then dispatch. */
extern int func_0203c634(int, int, void *);
extern int func_ov255_020d270c(int);
extern int func_ov255_020d2530(int);
extern int func_ov255_020d2878(int);
void func_ov255_020d281c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(*(int *)(owner + 4) + 0x78) = (int)&func_ov255_020d270c;
    *(int *)(*(int *)(owner + 4) + 0x6c) = (int)&func_ov255_020d2530;
    *(int *)(*(int *)(owner + 4) + 0x84) = owner;
    *(int *)(*(int *)(owner + 4) + 0x5c) &= ~2;
    *(int *)(owner + 0x10) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov255_020d2878);
}
