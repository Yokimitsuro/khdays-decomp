/* NONMATCHING: redundant-mask elision. The ROM emits `lsl#31; lsr#31` to test bit 0 and
 * `and #0xff; and #1` on the flag; mwcc folds both (`and #1`, and drops the #0xff) because it
 * knows the values are already narrow (112B vs 120B). No C form re-introduces the dead masks.
 * "Our compiler is smarter" class. */
/* func_ov025_020896fc -- arm or disarm a tag-tracker node.
 * When enabling (param_3) and it was not already armed (bit 0 of node+0x24), reset its
 * accumulators (+0x14/+0x18), stamp the time (+0x1c) and re-resolve its selected tag.
 * Bit 0 of node+0x24 then records the new armed state. */
extern long long func_020031d4(void);
extern void func_ov025_02089544(int owner, int tag);

void func_ov025_020896fc(int param_1, int param_2, int param_3) {
    unsigned char armed = 0;
    if (param_3 != 0) {
        armed = 1;
        if ((((unsigned int)*(unsigned char *)(param_2 + 0x24) << 0x1f) >> 0x1f) != 1) {
            *(int *)(param_2 + 0x14) = 0;
            *(int *)(param_2 + 0x18) = 0;
            *(long long *)(param_2 + 0x1c) = func_020031d4();
            func_ov025_02089544(param_1,
                *(int *)(*(int *)(param_2 + 0x2c) + *(unsigned short *)(param_2 + 4) * 4));
        }
    }
    *(unsigned char *)(param_2 + 0x24) = (*(unsigned char *)(param_2 + 0x24) & ~1) | (armed & 1);
}
