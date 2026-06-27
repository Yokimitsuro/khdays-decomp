extern void FS_LoadOverlay(int, int);
extern void func_01ff8110(int, int);

void func_0201e470(int a, int b)
{
    func_01ff8110(a, b);
    FS_LoadOverlay(a, b);
}
