extern int WM_EndKeySharing_0x020b15a4();
void func_ov030_020b3efc(int r0) {
    int i = 0;
    char *r6 = (char *)(r0 + 0x234);
    int r4 = *(int *)(r0 + 0xdb4) + 0x2000;
    for (;;) {
        WM_EndKeySharing_0x020b15a4(*(int *)(r4 + 0x63c), r6 + 0x108);
        r6 += 0x170;
        if (++i >= 8) break;
    }
}
