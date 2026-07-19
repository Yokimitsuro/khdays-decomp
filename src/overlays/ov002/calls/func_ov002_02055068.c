extern int func_ov002_02053558(unsigned short id);
extern void func_ov002_020535a4(void);
extern void func_ov002_02053610(int handle, unsigned char slot);
extern int data_ov002_0207dd14;

/* Prints one help page: the page title, the entry the cursor is on, the "back" line on page 0,
 * and the footer -- twice, once through the slot-aware printer. */
void func_ov002_02055068(int page, int *cursor) {
    char *row = (char *)&data_ov002_0207dd14 + page * 0x18;
    func_ov002_02053558((unsigned short)*(int *)row);
    func_ov002_020535a4();
    func_ov002_02053558((unsigned short)*(int *)(row + *cursor * 4 + 4));
    func_ov002_020535a4();
    if (page == 0) {
        func_ov002_02053558(1);
        func_ov002_020535a4();
    }
    func_ov002_02053610(func_ov002_02053558((unsigned short)*(int *)(row + 0x14)),
                        (unsigned char)(page + 2));
    func_ov002_02053558((unsigned short)*(int *)(row + 0x14));
    func_ov002_020535a4();
}
