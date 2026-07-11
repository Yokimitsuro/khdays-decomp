/* Create/register entity[index]: r=func_0201ef9c(p2,1); attach via
 * func_0202aff4(cont,r); store r at base+index*4+0x44; return 1. */
#pragma thumb on

extern int data_0204c208;
extern int func_0201ef9c(int p2, int one);
extern void func_0202aff4(void *cont, int r);

int func_0202b820(int index, int p2) {
    int base = data_0204c208;
    int r = func_0201ef9c(p2, 1);
    void *cont = (void *)(data_0204c208 + 4 + index * 8);
    func_0202aff4(cont, r);
    *(int *)(base + index * 4 + 0x44) = r;
    return 1;
}
