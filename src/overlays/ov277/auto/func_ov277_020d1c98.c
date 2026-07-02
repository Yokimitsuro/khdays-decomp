typedef struct { unsigned char flag : 1; } BitByte;

int func_ov277_020d1c98(char *obj) {
    char *node = *(char **)*(char **)(obj + 0x214);
    signed char state = *(signed char *)(node + 0x1c6);
    if (state == 0xc) {
        *(char *)(node + 0x1c7) = 0;
        return 1;
    }
    if (*(signed char *)(node + 0x1c7) != 0xb && state != 0xb) {
        if (((BitByte *)(node + 0x17a))->flag) {
            if (!(state != 2 && state != 4 && state != 9 && state != 0xa))
                *(char *)(node + 0x1c7) = 0xb;
        }
    }
    return 0;
}
