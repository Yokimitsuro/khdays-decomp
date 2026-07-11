extern void func_0202af2c(void *p);
extern void func_0202af1c(void *p);

void func_ov014_0207fd2c(char *obj, int sel) {
    switch (sel) {
        case 0:
            if ((*(int *)(obj + 0x38) & 0x20) == 0) func_0202af2c(obj + 0x3c);
            break;
        case 1:
            if ((*(int *)(obj + 0x38) & 0x20) == 0) func_0202af1c(obj + 0x3c);
            break;
        case 2:
            break;
    }
}
