extern void func_01ff8110(void *arg0);
extern int FS_LoadOverlayInfo(void *info, int proc, int id);

int func_0201e448(void *info, int proc, int id) {
    func_01ff8110(info);
    return FS_LoadOverlayInfo(info, proc, id);
}
