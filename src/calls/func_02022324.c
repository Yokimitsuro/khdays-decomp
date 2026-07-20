/* Re-read the current value via func_02021980 and, if it differs from the byte
 * cached at data_020425e8, commit the change: when bit 8 of func_02020a9c() is
 * set play sound 0x40 first, then store the new byte and notify func_020335ec.
 * Always reports success. */
extern int data_020425e8;

extern int func_02021980(void *arg);
extern int func_02020a9c(void);
extern void func_02033c24(int a, int b);
extern void func_020335ec(int v);

int func_02022324(void *arg) {
    int v = func_02021980(arg);

    if (v != *(signed char *)&data_020425e8) {
        if ((func_02020a9c() & 0x100) != 0) {
            func_02033c24(0x40, 0);
        }
        *(char *)&data_020425e8 = v;
        func_020335ec((unsigned char)v);
    }

    return 1;
}
