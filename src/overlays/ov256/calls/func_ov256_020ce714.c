/* Flag both linked nodes (+0x434/+0x438 -> +0x398=1); if 020ccd54 accepts, snap +0x40 to +0x44
 * and clear +0x6c; always clear +0x54 and dispatch. */
extern int func_ov256_020ccd54(int);
extern int func_0203c634(int, int, void *);
extern int func_ov256_020ce778(int);
void func_ov256_020ce714(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(*(int *)(*(int *)owner + 0x434) + 0x398) = 1;
    *(int *)(*(int *)(*(int *)owner + 0x438) + 0x398) = 1;
    if (func_ov256_020ccd54(param_1) != 0) {
        *(int *)(owner + 0x40) = *(int *)(owner + 0x44);
        *(int *)(owner + 0x6c) = 0;
    }
    *(int *)(owner + 0x54) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov256_020ce778);
}
