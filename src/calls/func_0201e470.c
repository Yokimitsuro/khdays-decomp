extern void FS_LoadOverlay(int, int);
extern void FSi_WaitForCardThread(int, int);

void func_0201e470(int a, int b)
{
    FSi_WaitForCardThread(a, b);
    FS_LoadOverlay(a, b);
}
