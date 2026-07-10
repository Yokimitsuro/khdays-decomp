/* Equivalent, readable C. NOT byte-exact: the original registers three callbacks
 * with `if (cb != -1) obj[slot] = cb;` and KEEPS the compare+branch even for the
 * two slots whose value is a constant 0 (`cmp 0,-1; beq; str`). mwcc 3.0/139
 * folds `0 != -1` to always-true and drops those branches from every constant
 * source form tried (literal -1, `int neg=-1`, `cb != cb-1`, inline helper), so
 * mine comes out 16B short. The original's 0 values must reach the check through
 * an opaque source (table/param) not yet identified. Byte-exact via asm stub. */
extern void *NNSi_FndAllocFromDefaultExpHeap(int size);
extern void func_ov013_0207fa40(void);

void func_ov013_0207fba4(int a, int b, int c) {
    int *obj = (int *)NNSi_FndAllocFromDefaultExpHeap(0x1c);
    *(unsigned char *)((char *)obj + 0x18) = a;
    *(unsigned char *)((char *)obj + 0x19) = b;
    obj[3] = c;
    obj[5] = 0;
    if ((int)func_ov013_0207fa40 != -1) obj[0] = (int)func_ov013_0207fa40;
    obj[1] = 0;
    obj[2] = 0;
}
