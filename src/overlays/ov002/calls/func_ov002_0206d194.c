/*
 * Return the base address of record param_1 in the table at (*global)+0x8d14:
 * table_base + param_1 * 0x44 (0x44-byte stride, 16-bit multiply).
 */
extern int data_ov002_0207fa00;

int func_ov002_0206d194(int param_1) {
    return (short)param_1 * (short)0x44 +
           *(int *)(*(int *)&data_ov002_0207fa00 + 0x8d14);
}
