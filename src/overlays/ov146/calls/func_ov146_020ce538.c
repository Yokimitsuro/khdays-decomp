extern void func_ov107_020c6980(void *obj, int arg2);

void func_ov146_020ce538(char *obj, int arg2) {
    if (*(unsigned char *)(*(char **)(obj + 0x3b4) + 0x1c4) & 2) {
        if (*(unsigned short *)(obj + 0x1ac) & 0x10) {
            arg2 = 0;
        }
    }
    func_ov107_020c6980(obj, arg2);
}
