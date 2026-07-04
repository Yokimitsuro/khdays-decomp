extern void func_ov022_02091eb0();

void func_ov061_020b69a0(int this_) {
    int i = 0;
    int off;
    if ((int)*(unsigned char *)(this_ + 0x19) <= 0) return;
    off = 0;
    do {
        int entry = *(int *)(this_ + 0xc) + off;
        signed char t = *(signed char *)(entry + 2);
        if (t != 0 && t != 2 && t != 3) {
            func_ov022_02091eb0(entry);
        }
        i++;
        off += 0x1c8;
    } while (i < (int)*(unsigned char *)(this_ + 0x19));
}
