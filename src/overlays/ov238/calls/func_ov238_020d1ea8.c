/* When the parent's +0x390 slot is free and 020d0878 grants a slot, commit the launch (clear
 * +0x20/+0x2e, anim 2, 0x12e/8 timer, notify 020d2600, dispatch 020d1f54); otherwise latch 2. */
extern int func_ov238_020d0878(int);
extern int func_0203c634(int, int, void *);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_ov238_020d2600(int);
extern int func_ov238_020d1f54(int);
void func_ov238_020d1ea8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(int *)(*(int *)(*(int *)owner + 0x384) + 0x390) != 0 || func_ov238_020d0878(param_1) == -1) {
        *(unsigned char *)(*(int *)owner + 0x1c7) = 2;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    } else {
        func_ov238_020d0878(param_1);
        *(int *)(owner + 0x20) = 0;
        *(unsigned char *)(owner + 0x2e) = 0;
        func_ov107_020c9264(*(int *)owner, 2, 0);
        func_ov107_020c5af8(*(int *)owner, 0x12e, 8, *(int *)(owner + 8));
        func_ov238_020d2600(*(int *)(*(int *)owner + 0x384));
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov238_020d1f54);
    }
}
