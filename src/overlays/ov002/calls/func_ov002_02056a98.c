extern int func_ov002_020536bc(int id);
extern void func_ov002_02053700(void);
extern void func_ov002_02053558(int id);
extern void func_ov002_020535f0(void);
extern void func_ov002_020536dc(int handle, int mode);

/* Refreshes widget 1: mode 0 restores the default caption, any other mode prints line 0x3c. */
void func_ov002_02056a98(int mode) {
    int handle = func_ov002_020536bc(1);
    if (mode != 0) {
        func_ov002_02053700();
    } else {
        func_ov002_02053558(0x3c);
        func_ov002_020535f0();
    }
    func_ov002_020536dc(handle, mode);
}
