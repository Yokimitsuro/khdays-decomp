/* Reset via 020cdfe8, accumulate the frame delta into +0x64 and +0x6c; when armed (+0x89==1) and
 * +0x6c passes 0xee0, disarm and fire the 0x148/0x13 effect; then unless busy anim 0x25 and dispatch. */
extern int func_ov252_020cdfe8(int, int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov252_020d1674(int);
void func_ov252_020d15b8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov252_020cdfe8(param_1, 0, 1);
    *(int *)(owner + 0x64) += *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(owner + 0x6c) += *(int *)(*(int *)param_1 + 0x2c);
    int b = *(unsigned char *)(owner + 0x89);
    if (b == 1) {
        if (*(int *)(owner + 0x6c) >= 0xee0) {
            *(unsigned char *)(owner + 0x89) = b - 1;
            func_ov107_020c5af8(*(int *)owner, 0x148, 0x13, *(int *)(owner + 8));
        }
    }
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)owner, 0x25, 0);
    *(unsigned char *)(owner + 0x86) = 0;
    *(unsigned char *)(owner + 0x88) = 1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov252_020d1674);
}
