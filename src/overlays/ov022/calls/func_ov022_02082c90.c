extern void func_ov022_02083c08(int mode);
extern int func_ov002_02071e08(void);
extern void func_01fffe14(void);
extern int func_ov022_02088474(void);
extern void func_ov002_020726a0(int a, int b, int *out);
extern void func_ov002_02072000(void);
extern void func_ov002_020764e4(unsigned short id);
extern int func_02030670(void);
extern int func_ov002_02072908(int id);
extern int func_ov002_02072934(int id);
extern void func_02033f50(int a, int b, unsigned short c);
extern void func_ov002_0206f514(int mode);
extern void func_ov022_02082d04(void);
extern unsigned char data_0204be04;

/* Starts the pause menu unless the lock byte is set: opens the panel, publishes the selected
 * entry and hands back the menu's tick handler. */
void *func_ov022_02082c90(void) {
    int entry;
    unsigned short alpha;
    if (data_0204be04 != 0) {
        /* No value: the ROM really does leave r0 untouched on this path. */
        return;
    }
    func_ov022_02083c08(0);
    if (func_ov002_02071e08() != 0) {
        func_01fffe14();
        func_ov002_020726a0(func_ov022_02088474(), 0, &entry);
        func_ov002_02072000();
        func_ov002_020764e4((unsigned short)entry);
        alpha = func_02030670() != 0 ? 0x66 : 0x7f;
        func_02033f50(func_ov002_02072908(entry), func_ov002_02072934(entry), alpha);
        func_ov002_0206f514(0);
        return (void *)&func_ov022_02082d04;
    }
    return 0;
}
