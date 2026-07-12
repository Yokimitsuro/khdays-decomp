/* On sub-state 7 advance +0x44 by 0x3244 and mirror into +0x40, then reset anim 0 and dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov256_020cd9a8(int);
void func_ov256_020cd94c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(signed char *)(*(int *)owner + 0x1c8) == 7) {
        *(int *)(owner + 0x44) += 0x3244;
        *(int *)(owner + 0x40) = *(int *)(owner + 0x44);
    }
    func_ov107_020c9264(*(int *)owner, 0, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov256_020cd9a8);
}
