#pragma thumb on
/* Sibling of func_0202b930; second helper is func_0202b1ec. */

extern int data_0204c208;
extern void func_0202b87c(void *obj, int a, int b, void *c, int d);
extern int func_0202b1ec(void *field, int p2, int p3, int p4);

int func_0202b9a0(void *obj, int p2, int p3, int p4) {
    if ((*(unsigned char *)((char *)obj + 8) & 1) == 0) {
        func_0202b87c(obj, 0, 0, 0, 1);
    }
    if (func_0202b1ec((char *)obj + 0xc, p2, p3, p4) != 0) {
        *(unsigned char *)((char *)obj + 0xb) = *(unsigned char *)(data_0204c208 + 0xa4d0);
        *(unsigned char *)((char *)obj + 9) = (unsigned char)p4;
        *(unsigned char *)((char *)obj + 8) |= 4;
        return 1;
    }
    return 0;
}
