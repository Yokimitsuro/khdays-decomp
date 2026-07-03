extern void func_ov107_020c9264(int val, int a, int b);
extern void func_0203c634(void *a, int b, void *cb);
extern void func_ov264_020ce908(void);

void func_ov264_020ce8d4(char *a) {
    func_ov107_020c9264(**(int **)(a + 0x4), 2, 1);
    func_0203c634(a, *(short *)(a + 0x20), func_ov264_020ce908);
}
