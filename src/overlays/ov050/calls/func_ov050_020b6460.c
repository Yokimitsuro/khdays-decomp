extern void func_01ff87e0(int a, int b);
extern void func_02016b60(int a, int b, int c);
extern void func_01ff9f00(int tag, int *buf, int count);
extern void func_0201571c(void);
extern void func_020279e0(int p);

void func_ov050_020b6460(int this, int entry, int p3) {
    int buf[3];
    int val;
    switch (*(int *)(entry + 4)) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
        switch (*(int *)entry) {
        case 0:
            func_01ff87e0(this + 0x528, entry + 0x88);
            break;
        case 1:
            func_01ff87e0(this + 0x558, entry + 0x88);
            break;
        }
        func_02016b60(*(int *)(entry + 0x80), 2, p3 + 5);
        val = *(int *)(*(int *)(entry + 0x2c) + 0x1c);
        buf[0] = val;
        buf[1] = val;
        buf[2] = val;
        func_01ff9f00(0x1b, buf, 3);
        func_0201571c();
        func_01ff9f00(0x17, (int *)(entry + 0x88), 0xc);
        func_020279e0(entry + 0x28);
        break;
    default:
        break;
    }
}
