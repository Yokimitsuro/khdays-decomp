extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_ov010_0204cddc(int a, int b, int c);
extern int func_ov010_0204ce20(void);
extern void func_0202fa20(int obj, int b);
extern void func_0202fa38(int obj, int b, int c, int d, int e, int f);
extern void func_0202f9f8(int obj);

/* Boot state machine for the ov010 root-heap work area (state at +0x78, 0..5):
 * configure the field, wait for the config to finish, wait for the A button,
 * reconfigure, then wait again. Always refreshes the +0x18 sub-object; returns
 * -2 once the final state (5) is reached, else 0. */
int func_ov010_0204ce60(void) {
    int root = NNSi_FndGetCurrentRootHeap();

    switch (*(int *)(root + 0x78)) {
    case 0:
        func_ov010_0204cddc(0x10000, 0, 0xc8);
        *(int *)(root + 0x78) = 1;
        break;
    case 1:
        if (func_ov010_0204ce20() != 0) {
            *(int *)(root + 0x78) = 2;
        }
        break;
    case 2: {
        unsigned short pressed = (unsigned short)(((*(volatile unsigned short *)0x04000130 |
                                                    *(volatile unsigned short *)0x027fffa8) ^ 0x2fff) & 0x2fff);
        if (pressed & 1) {
            *(int *)(root + 0x78) = 3;
        }
        break;
    }
    case 3:
        func_ov010_0204cddc(0, -0x10000, 0x3e8);
        *(int *)(root + 0x78) = 4;
        break;
    case 4:
        if (func_ov010_0204ce20() != 0) {
            *(int *)(root + 0x78) = 5;
        }
        break;
    }
    func_0202fa20(root + 0x18, 0);
    func_0202fa38(root + 0x18, 0x80, 0x60, 1, 0x412, *(int *)(root + 0x74));
    func_0202f9f8(root + 0x18);
    return *(int *)(root + 0x78) == 5 ? -2 : 0;
}
