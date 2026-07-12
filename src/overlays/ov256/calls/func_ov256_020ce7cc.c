/* If +0x6c is set, hand to 020ce714. Else, unless busy, if +0x54 is under 3 hand to 020ce778;
 * otherwise clear both linked nodes' +0x398, latch +0x74+2 and dispatch. */
extern int func_0203c634(int, int, void *);
extern int func_ov256_020ce714(int);
extern int func_ov256_020ce778(int);
void func_ov256_020ce7cc(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(int *)(owner + 0x6c) != 0) {
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov256_020ce714);
        return;
    }
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    if (*(int *)(owner + 0x54) < 3) {
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov256_020ce778);
        return;
    }
    *(int *)(*(int *)(*(int *)owner + 0x434) + 0x398) = 0;
    *(int *)(*(int *)(*(int *)owner + 0x438) + 0x398) = 0;
    *(unsigned char *)(*(int *)owner + 0x1c7) = *(int *)(owner + 0x74) + 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
