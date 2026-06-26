extern int func_01ff8110();
extern int FS_LoadOverlayImage();

int func_0201e490(int a) {
    func_01ff8110(a);
    return FS_LoadOverlayImage(a);
}
