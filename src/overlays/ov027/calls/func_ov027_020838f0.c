extern int func_020235d0(int key, int sub);
extern char data_0204c4d8[];
/* True only in mission mode 5 with game field 0x40a/2 equal to 1. */
int func_ov027_020838f0(void) {
    if (*(char *)(data_0204c4d8 + 0x11) == 5 && func_020235d0(0x40a, 2) == 1) {
        return 1;
    }
    return 0;
}
