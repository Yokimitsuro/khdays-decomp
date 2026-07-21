extern char data_0204c500[];
int func_020358a4(int idx) {
    if (idx < 0 || idx >= 2) {
        return 0;
    }
    return (int)(data_0204c500 + idx * 0x48);
}
