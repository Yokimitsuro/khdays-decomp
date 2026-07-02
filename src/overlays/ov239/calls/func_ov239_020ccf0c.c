extern void func_0203c634();
void func_ov239_020ccf0c(int node) {
    int *s = *(int **)(node + 4);
    if (*(unsigned char *)(s[1] + 0xad) != 0) return;
    *(unsigned short *)(*s + 0x1ae) &= ~1;
    *(signed char *)(*s + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
