/*
 * NONMATCHING (2-byte scheduler swap, size-exact byte-diff @0x44). The word
 * stores (0xa000, 0), the shared (param_3>>4)*2 index, the FUN_01ff9010 negated
 * short args, and the double vec3 struct-copy all match. mwcc just materializes
 * `mov r3,#0` one slot BEFORE the `str 0xa000,[0x168]`, the original the reverse
 * (both independent). Byte-equivalent.
 */
extern void func_01ff9010(void *a, int b, int c);
extern short data_0203d210;

struct vec3_02092b60 {
    int a;
    int b;
    int c;
};

void func_ov022_02092b60(unsigned char *param_1, struct vec3_02092b60 *param_2, int param_3) {
    if ((*param_1 & 1) != 0) {
        int k = (param_3 >> 4) * 2;
        short sVar1 = *(short *)((int)&data_0203d210 + k * 2);
        short sVar2 = *(short *)((int)&data_0203d210 + (k + 1) * 2);
        struct vec3_02092b60 tmp;
        *(int *)(param_1 + 0x168) = 0xa000;
        *(int *)(param_1 + 0x16c) = 0;
        *(int *)(param_1 + 0x174) = 0;
        func_01ff9010(param_1 + 0x144, -(int)sVar1, -(int)sVar2);
        tmp = *param_2;
        param_1[0x135] = 1;
        *(struct vec3_02092b60 *)(param_1 + 0x138) = tmp;
        *(struct vec3_02092b60 *)(param_1 + 0xa8) = tmp;
    }
}
