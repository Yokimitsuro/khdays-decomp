extern void func_ov022_02091eb0(int arg0);
void func_ov022_02090ec4(int arg0) {
    int i = 0;
    if (i < *(unsigned char *)(arg0 + 0x19)) {
        int e = i;
        do {
            int slot = *(int *)(arg0 + 0xc) + e;
            char c = *(char *)(slot + 2);
            if (c != 0 && c != 3) func_ov022_02091eb0(slot);
            i++;
            e += 0x1c8;
        } while (i < *(unsigned char *)(arg0 + 0x19));
    }
}
