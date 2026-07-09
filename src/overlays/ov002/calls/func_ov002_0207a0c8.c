extern int func_ov002_0207a0f0();
extern int func_ov002_0207cea4();

int func_ov002_0207a0c8(int arg0) {
    int b = *(unsigned char *)(arg0 + 0x1b4);
    if (b == 5) {
        return (int)func_ov002_0207a0f0;
    }
    if (b == 7) {
        return (int)func_ov002_0207cea4;
    }
    return 0;
}
