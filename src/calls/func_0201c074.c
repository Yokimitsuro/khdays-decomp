extern int func_0201b7e0(int handle);
extern int OS_IsThreadAvailable_0x0201b3d8(void);
extern int func_0201befc(int handle, void *cb, int arg, int handle2, int *out);
extern void func_0201b808(int handle, int entry);
extern void func_0201c2d4(void);

unsigned func_0201c074(unsigned handle, int *out, int flag) {
    unsigned entry = func_0201b7e0(handle);
    if (entry == 0) {
        int arg;
        if (flag == 0) arg = 0;
        else arg = OS_IsThreadAvailable_0x0201b3d8();
        entry = func_0201befc(handle, func_0201c2d4, arg, handle, out);
        if (flag != 0 && entry != 0) func_0201b808(handle, entry);
    }
    return entry;
}
