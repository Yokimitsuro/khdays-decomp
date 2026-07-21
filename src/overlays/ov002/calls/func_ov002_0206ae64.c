extern void func_ov002_0206374c(int arg);
extern char *data_ov002_0207fa00;
/* Only in link mode 1, and only for event kind 1, forward the payload. */
void func_ov002_0206ae64(int kind, int arg) {
    if (*(unsigned char *)((int)data_ov002_0207fa00 + 0x8d0b) != 1) {
        return;
    }
    if (kind == 0) {
        return;
    }
    if (kind != 1) {
        return;
    }
    func_ov002_0206374c(arg);
}
