extern int func_0203c634();

void func_ov205_020d5a60(char *r0) {
    char *r2 = *(char **)(r0 + 4);
    char *r1 = *(char **)(r2 + 0x28);
    if (*(unsigned char *)r1 != 0) {
        return;
    }
    r1 = *(char **)r2;
    *(unsigned char *)(r1 + 0x1c7) = 2;
    func_0203c634(r0, *(signed char *)(r0 + 0x20), 0);
}
