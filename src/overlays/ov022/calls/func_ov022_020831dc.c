extern void WM_EndKeySharing_0x02023ad0(int arg0);
extern void func_ov002_020518d0(void);
extern int data_ov022_020b2e60;

void func_ov022_020831dc(void) {
    unsigned int i = 0;
    int base = *(int *)(*(int *)((char *)&data_ov022_020b2e60 + 4) + 0x20);
    do {
        if (*(int *)(base + 8) != 0) {
            WM_EndKeySharing_0x02023ad0(*(int *)(base + 8));
        }
        i = i + 1;
        base = base + 4;
    } while (i < 3);
    func_ov002_020518d0();
}
