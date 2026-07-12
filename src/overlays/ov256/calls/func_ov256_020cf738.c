/* Unless busy, clear +0x54 and kick anim 0xb; always dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov256_020cf780(int);
void func_ov256_020cf738(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) == 0) {
        *(int *)(owner + 0x54) = 0;
        func_ov107_020c9264(*(int *)owner, 0xb, 0);
    }
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov256_020cf780);
}
