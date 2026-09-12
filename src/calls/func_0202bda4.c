/* Scale-and-dispatch pass over the selected entity slots' two intrusive lists
 * (heads at data_0204c208+idx*4+{0x84,0x64}, same table func_0202bc90 walks).
 * The +0x84 list scales each node's own factor at +0x180 by `scale` in 1.19.12
 * fixed point before dispatching; the +0x64 list passes `scale` through. */
typedef int fx32;
typedef long long fx64;

extern int data_0204c208;
extern unsigned int func_0202b3f0(int slot, unsigned int *node, int scale);

void func_0202bda4(unsigned int mask, fx32 scale) {
    int i;
    unsigned int bit = 1;

    for (i = 0; i < *(int *)data_0204c208; i++, bit <<= 1) {
        if (mask & bit) {
            unsigned short idx = (unsigned short)i;
            int *p;
            int slot = data_0204c208 + 4 + idx * 8;

            for (p = *(int **)(data_0204c208 + idx * 4 + 0x84); p != 0; p = *(int **)p) {
                func_0202b3f0(slot, (unsigned int *)(p + 3),
                              (fx32)(((fx64)scale * p[0x60] + 0x800) >> 12));
            }
            for (p = *(int **)(data_0204c208 + idx * 4 + 0x64); p != 0; p = *(int **)p) {
                func_0202b3f0(slot, (unsigned int *)(p + 3), scale);
            }
        }
    }
}
