/* Run 020cd028; unless busy, take the ready path only when +0x38 is idle and 020cd2cc confirms. */
extern int func_ov258_020cd028(int, int);
extern int func_ov258_020cd2cc(int);
extern int func_0203c634(int, int, void *);
extern int func_ov258_020cdc08(int);
void func_ov258_020cdc3c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov258_020cd028(param_1, 1);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    if (*(int *)(owner + 0x38) == 0 && func_ov258_020cd2cc(param_1) != 0)
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    else
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov258_020cdc08);
}
