/* Initialize a cursor over the buffer param_2: zero the 0x14-byte header, point it
 * at param_2, seed start/read pointers to param_2 + *(param_2), the write pointer to
 * that + its own +8 field, and cache param_2's flag byte at +0x10. */
extern void MI_CpuFill8(void *dst, int val, int size);

void func_ov002_0206791c(int param_1, int param_2) {
    int v, p;

    MI_CpuFill8((void *)param_1, 0, 0x14);
    *(int *)param_1 = param_2;
    v = param_2 + *(int *)param_2;
    *(int *)(param_1 + 4) = v;
    *(int *)(param_1 + 8) = v;
    p = *(int *)(param_1 + 4);
    *(int *)(param_1 + 0xc) = p + *(int *)(p + 8);
    *(int *)(param_1 + 0x10) = *(unsigned char *)(param_2 + 4);
}
