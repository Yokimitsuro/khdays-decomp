extern void WM_EndKeySharing_0x020b15a4(int a, int b);

void func_ov083_020b9794(char *obj) {
    int i = 0;
    int *p = *(int **)(obj + 0x2644);
    int a = 0;
    int q = (int)obj + 0x2f0c;
    do {
        int c = p[3];
        WM_EndKeySharing_0x020b15a4(*(int *)(obj + 0x263c), q);
        i++;
        *(int *)(c + a + 0x130) = q;
        a += 0x1c8;
        q += 0x24;
    } while (i < 10);
}
