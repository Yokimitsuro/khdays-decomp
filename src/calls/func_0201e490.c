extern int FSi_WaitForCardThread();
extern int FS_LoadOverlayImage();

int func_0201e490(int a) {
    FSi_WaitForCardThread(a);
    return FS_LoadOverlayImage(a);
}
