/* func_ov025_0209f430 -- resolve the panel's 19 row ids (tags 5, 6, then 7..0x17) from the item
 * table at ctx+0xb8 into the slot array at ctx+8. */
extern int func_ov025_02084afc(void);
extern int func_ov025_0208843c(int table, int tag);

void func_ov025_0209f430(void) {
    int ctx = func_ov025_02084afc();
    int *slots = (int *)(ctx + 8);
    int i;
    slots[0] = func_ov025_0208843c(*(int *)(ctx + 0xb8), 5);
    slots[1] = func_ov025_0208843c(*(int *)(ctx + 0xb8), 6);
    i = 0;
    do {
        slots[i + 2] = func_ov025_0208843c(*(int *)(ctx + 0xb8), i + 7);
        i = i + 1;
    } while (i < 0x11);
}
