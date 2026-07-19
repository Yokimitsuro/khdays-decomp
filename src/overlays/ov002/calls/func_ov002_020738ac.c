extern void func_02035d78(void);
extern int func_ov107_020c9c0c(int size, int a);
extern char *OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov002_02074054(int a);
extern int func_ov002_0206e6d0(void);
extern void func_ov002_0204cb70(void);
extern void func_ov002_0204cc9c(void);
extern char *data_ov002_0207fa14;

/* Creates the field's render context the first time round -- a negative size means "use the
 * default 0x57800" -- wires its two callbacks and republishes the camera and the active map.
 * `self` is advanced to the camera field on purpose: that is the ROM's `adds r4, #0x98`. */
void func_ov002_020738ac(int size) {
    char *self = data_ov002_0207fa14;
    if (size < 0) {
        size = 0x57800;
    }
    if (*(int *)(self + 0x18) == -1) {
        char *scene;
        int map;
        func_02035d78();
        *(int *)(self + 0x18) = func_ov107_020c9c0c(size, 0);
        *(void **)(OS_IsThreadAvailable_0x020c9848() + 0x74) = (void *)&func_ov002_0204cb70;
        *(void **)(OS_IsThreadAvailable_0x020c9848() + 0x78) = (void *)&func_ov002_0204cc9c;
        func_ov002_02074054(0);
        scene = *(char **)OS_IsThreadAvailable_0x020c9848();
        self += 0x98;
        *(int *)(scene + 0xa8) = *(int *)self;
        map = func_ov002_0206e6d0();
        *(int *)(OS_IsThreadAvailable_0x020c9848() + 0x8c) = map;
    }
}
