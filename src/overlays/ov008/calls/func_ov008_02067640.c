extern char *func_ov008_02050cd4(void);
extern void func_ov008_02062b44(char *self, int mode);
extern void func_02033b78(int a, int b);
extern void func_ov008_02066394(void);
extern void func_ov008_02065f80(void);
extern void func_ov008_0206608c(void);
extern char *data_ov008_02090380;

/* Once the pending transfer is done, rebinds the three list callbacks and starts the fade. */
void func_ov008_02067640(void) {
    char *self = func_ov008_02050cd4();
    if (*(int *)(self + 0x30) != 0) {
        return;
    }
    func_ov008_02062b44(self, 0);
    *(void **)((char *)&data_ov008_02090380 + 0x24) = (void *)&func_ov008_02066394;
    *(void **)((char *)&data_ov008_02090380 + 0x14) = (void *)&func_ov008_02065f80;
    *(void **)((char *)&data_ov008_02090380 + 0x18) = (void *)&func_ov008_0206608c;
    func_02033b78(0, 1);
}
