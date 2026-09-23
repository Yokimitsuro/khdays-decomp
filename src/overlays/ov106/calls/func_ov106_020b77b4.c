/* Set up the ov106 scene's view: the data_ov106_020b8ad0 resource loads (mode 0xe) into +0x8b48, the
 * +0x8b4c camera initialises and its projection is built into +0x8b84, the scene layout runs
 * (020b782c), the resource is released and the scene widgets reset (020b78bc). */
extern char *data_ov106_020b8b60;
extern char data_ov106_020b8ad0[];
extern void *func_02024ee8(const void *descriptor, int mode);
extern void func_02023c60(void *obj);
extern void func_02004d60(int a, int b, int c, int d, int e, int scale, void *projOut);
extern void func_ov106_020b782c(void);
extern void func_02024fd4(void *resource);
extern void func_ov106_020b78bc(void);

void func_ov106_020b77b4(void)
{
    *(void **)(data_ov106_020b8b60 + 0x8b48) = func_02024ee8(data_ov106_020b8ad0, 0xe);
    func_02023c60(data_ov106_020b8b60 + 0x8b4c);
    func_02004d60(*(int *)(data_ov106_020b8b60 + 0x8b4c), *(int *)(data_ov106_020b8b60 + 0x8b50),
                  *(int *)(data_ov106_020b8b60 + 0x8b54), *(int *)(data_ov106_020b8b60 + 0x8b58),
                  *(int *)(data_ov106_020b8b60 + 0x8b5c), 0x1000, data_ov106_020b8b60 + 0x8b84);
    func_ov106_020b782c();
    func_02024fd4(*(void **)(data_ov106_020b8b60 + 0x8b48));
    func_ov106_020b78bc();
}
