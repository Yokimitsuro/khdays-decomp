extern void FSi_WaitForCardThread(void *arg0);
extern int FS_LoadOverlayInfo(void *info, int proc, int id);

int func_0201e448(void *info, int proc, int id) {
    FSi_WaitForCardThread(info);
    return FS_LoadOverlayInfo(info, proc, id);
}
