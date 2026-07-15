/* func_ov008_0204e04c -- commit the menu to the selected page and bring up its UI, ov008.
 * Detaches the previous page (d6f8), marks the menu committed (heap+0x18=3), unloads the old
 * UI container (func_ov008_0204da14), rebuilds the page's cursor/help/selection widgets
 * (d6a8, 020335ec 0x1f, 02033c24 0x40/10), and for the current player's save slot pushes its
 * title (func_ov008_02053b18 from slot+4). Then loads the page layout (0205005c/020511c8) and
 * the difficulty glyph (020511f8 from func_ov008_0204ed58), and for each of the 4 slots pushes
 * its state icon (bits 1-3 of heap+slot*0x1c+0xbb) and its enabled flag (bit 0). */
extern void  func_ov008_0204d6f8(void);
extern void  func_ov008_0204da14(void);
extern int   func_02030788(void);
extern void  func_ov008_0204d6a8(int a);
extern void  func_020335ec(int a);
extern void  func_02033c24(int a, int b);
extern int   func_020315c0(int slot);
extern void  func_020352cc(void);
extern void  func_ov008_02053b18(int a, int b);
extern void  func_ov008_0205005c(int a);
extern void  func_ov008_020511c8(unsigned int a);
extern int   func_ov008_0204ed58(void);
extern void  func_ov008_020511f8(int a);
extern void  func_ov008_02051228(unsigned int a, int b);
extern void  func_ov008_02051260(unsigned int a, int b);
extern char *data_ov008_02090f00;
extern unsigned short data_0204c23c;
extern void  func_ov008_0204e948(void);

struct SlotByte { unsigned char b0 : 1, b123 : 3; };

void *func_ov008_0204e04c(int p1, int p2, int p3, int p4) {
    int slot;
    unsigned int i;
    int off;
    func_ov008_0204d6f8();
    *(int *)(data_ov008_02090f00 + 0x18) = 3;
    func_ov008_0204da14();
    func_ov008_0204d6a8(func_02030788());
    func_020335ec(0x1f);
    func_02033c24(0x40, 10);
    slot = func_020315c0(func_02030788());
    if (slot != 0) {
        func_020352cc();
        func_ov008_02053b18(*(int *)(slot + 4), 0);
    }
    func_ov008_0205005c(0);
    func_ov008_020511c8(data_0204c23c);
    func_ov008_020511f8((unsigned char)func_ov008_0204ed58());
    i = 0;
    off = 0;
    do {
        func_ov008_02051228(i & 0xffff, ((struct SlotByte *)(data_ov008_02090f00 + off + 0xbb))->b123);
        func_ov008_02051260(i, ((struct SlotByte *)(data_ov008_02090f00 + off + 0xbb))->b0);
        i++;
        off += 0x1c;
    } while ((int)i < 4);
    return (void *)func_ov008_0204e948;
}
