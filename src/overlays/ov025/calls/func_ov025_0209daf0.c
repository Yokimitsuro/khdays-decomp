/* func_ov025_0209daf0 -- resolve the list's 17 row ids (tags 4, 5, then 6..0x14) from the item
 * table at ctx+0xc8 into the slot array at ctx+0x10, and clear the scroll offset (ctx+0x68). */
extern int func_ov025_02084afc(void);
extern int func_ov025_0208843c(int table, int tag);

void func_ov025_0209daf0(void) {
    int ctx = func_ov025_02084afc();
    int *slots = (int *)(ctx + 0x10);
    int i;
    slots[0] = func_ov025_0208843c(*(int *)(ctx + 0xc8), 4);
    slots[1] = func_ov025_0208843c(*(int *)(ctx + 0xc8), 5);
    i = 0;
    do {
        slots[i + 2] = func_ov025_0208843c(*(int *)(ctx + 0xc8), i + 6);
        i = i + 1;
    } while (i < 0xf);
    slots[0x16] = 0;   /* ctx+0x68 */
}
