/* func_ov008_0204dfb4 -- advance the main menu into the selected page, ov008.
 * Refreshes the cursor (func_ov008_0204da6c) and marks the menu busy (heap+0x18=2). With a
 * sub-scene active, ungates input (func_020307b8(0)), clears the four per-slot save flags
 * (heap+0x92/0x96/0x9a/0x9e) and hands off to func_ov008_0204e04c. Otherwise it only proceeds
 * once the current page's option count (high nibble of heap+0x1e) reaches 3, clearing the
 * transition marker (heap+0x172) before handing off; below 3 it stays (returns 0). */
extern void  func_ov008_0204da6c(void);
extern int   func_ov008_0204ed3c(void);
extern void  func_020307b8(int a);
extern char *data_ov008_02090f00;
extern void  func_ov008_0204e04c(void);

void *func_ov008_0204dfb4(void) {
    func_ov008_0204da6c();
    *(int *)(data_ov008_02090f00 + 0x18) = 2;
    if (func_ov008_0204ed3c() != 0) {
        func_020307b8(0);
        *(short *)(data_ov008_02090f00 + 0x92) = 0;
        *(short *)(data_ov008_02090f00 + 0x96) = 0;
        *(short *)(data_ov008_02090f00 + 0x9a) = 0;
        *(short *)(data_ov008_02090f00 + 0x9e) = 0;
        return (void *)func_ov008_0204e04c;
    }
    if ((unsigned int)*(unsigned char *)(data_ov008_02090f00 + 0x1e) << 0x18 >> 0x1c < 3) {
        return 0;
    }
    *(short *)(data_ov008_02090f00 + 0x172) = 0;
    func_020307b8(0);
    return (void *)func_ov008_0204e04c;
}
