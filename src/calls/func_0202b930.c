#pragma thumb on
/* Register obj on entity system: lazily init (func_0202b87c) if state bit 0 is
 * clear, run func_0202b178 on obj+0xc; on success stamp obj[0xb] from a global
 * table byte, store p4 in obj[9], set state bit 4, return 1 (else 0). */

extern int data_0204c208;
extern void func_0202b87c(void *obj, int a, int b, void *c, int d);
extern int func_0202b178(void *field, int p2, int p3, int p4);

int func_0202b930(void *obj, int p2, int p3, int p4) {
    if ((*(unsigned char *)((char *)obj + 8) & 1) == 0) {
        func_0202b87c(obj, 0, 0, 0, 1);
    }
    if (func_0202b178((char *)obj + 0xc, p2, p3, p4) != 0) {
        *(unsigned char *)((char *)obj + 0xb) = *(unsigned char *)(data_0204c208 + 0xa4d0);
        *(unsigned char *)((char *)obj + 9) = (unsigned char)p4;
        *(unsigned char *)((char *)obj + 8) |= 4;
        return 1;
    }
    return 0;
}
