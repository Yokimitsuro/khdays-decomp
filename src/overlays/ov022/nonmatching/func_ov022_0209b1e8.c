/*
 * [nonmatching: frame/outgoing-arg-slot layout: the 5th arg to func_ov002_0206df6c is stored to the pushed-r3 scratch slot in the original (push {r3,r4,r5,lr}); mwcc allocates a fresh sub-sp slot (+4B)]
 *
 * Equivalent C; mwcc 3.0/139 diverges in the noted codegen. Left uncarved.
 */
extern void func_ov002_0206df6c(int arg0, int arg1, int arg2, int arg3, int arg4);
extern void func_ov022_0209be44(int arg0);

void func_ov022_0209b1e8(int arg0, int arg1, int arg2, int arg3) {
    if (*(char *)(arg0 + 0x2770) == 0xc) {
        func_ov002_0206df6c(*(unsigned char *)(arg0 + 9), 0, arg2, arg3, arg3);
    }
    *(unsigned char *)(arg0 + 0x2770) = 0xe;
    *(unsigned char *)(arg0 + 0x2771) = 0xe;
    *(int *)(arg0 + 0x2774) = 0;
    *(int *)(arg0 + 0x2778) = 0;
    *(int *)(arg0 + 0x2780) = 0;
    *(unsigned char *)(arg0 + 0x277c) &= 0xfd;
    *(unsigned char *)(arg0 + 0x2ab8) = 0xe;
    func_ov022_0209be44(arg0);
}
