/* Reset the reaction slot (mark 0, state -1) then fan out three dispatches. */
extern int func_0203c634(int, int, void *);
extern int func_ov255_020d1c5c(int);
extern int func_ov255_020d1d00(int);
extern int func_ov255_020d1cd0(int);
void func_ov255_020d1bf4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 4) = *(int *)owner + 0xb0;
    *(signed char *)(*(int *)owner + 0x1c6) = 0;
    *(signed char *)(*(int *)owner + 0x1c7) = -1;
    func_0203c634(param_1, 0, (void *)&func_ov255_020d1c5c);
    func_0203c634(param_1, 1, (void *)&func_ov255_020d1d00);
    func_0203c634(param_1, 2, (void *)&func_ov255_020d1cd0);
}
