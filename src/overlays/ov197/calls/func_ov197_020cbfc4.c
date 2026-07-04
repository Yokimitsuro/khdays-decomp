extern int func_02016320();

struct w3 { int a, b, c; };

void func_ov197_020cbfc4(int arg0, int arg1) {
    int buf[12];
    if (func_02016320(*(int *)(arg0 + 0x88) + 0x20, buf, 0, *(int *)(arg1 + 0x3d4)) == 0) return;
    *(struct w3 *)(arg1 + 0x3d8) = *(struct w3 *)((char *)buf + 0x24);
}
