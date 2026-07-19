extern char *func_ov025_02084afc(void);
extern void func_ov025_02095070(char *self, int mode);
extern void func_02033b78(int a, int b);
extern void func_ov025_020988c0(void);
extern void func_ov025_020984ac(void);
extern void func_ov025_020985b8(void);
extern char *data_ov025_020b4d4c;

/* Once the pending transfer is done, rebinds the three list callbacks and starts the fade. */
void func_ov025_02099a20(void) {
    char *self = func_ov025_02084afc();
    if (*(int *)(self + 0x30) != 0) {
        return;
    }
    func_ov025_02095070(self, 0);
    *(void **)((char *)&data_ov025_020b4d4c + 0x24) = (void *)&func_ov025_020988c0;
    *(void **)((char *)&data_ov025_020b4d4c + 0x14) = (void *)&func_ov025_020984ac;
    *(void **)((char *)&data_ov025_020b4d4c + 0x18) = (void *)&func_ov025_020985b8;
    func_02033b78(0, 1);
}
