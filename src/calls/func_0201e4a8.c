extern void FSi_WaitForCardThread(int, int);
extern void FS_UnloadOverlay(int, int);

void func_0201e4a8(int a, int b)
{
    FSi_WaitForCardThread(a, b);
    FS_UnloadOverlay(a, b);
}
