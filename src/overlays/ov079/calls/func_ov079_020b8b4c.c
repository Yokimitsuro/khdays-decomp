extern void func_0202a818(void *p, int arg);

void func_ov079_020b8b4c(char *obj, char *b, int c) {
    int mode = *(int *)(obj + 0x6bc);
    if (mode != 48 && mode != 49) {
        *(int *)(b + 0x124) = 0;
    }
    if (*(int *)(b + 0x124) != 1) return;
    func_0202a818(b + 0x128, c);
}
