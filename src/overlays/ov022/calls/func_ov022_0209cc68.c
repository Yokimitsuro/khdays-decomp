extern void WM_EndKeySharing_0x02023ad0(int arg0);
extern void func_ov022_02092354(int *arg0);
extern void func_ov022_0209aed0(int arg0);

void func_ov022_0209cc68(int arg0, int arg1, int arg2, int arg3) {
    if (*(int *)(arg0 + 0x7b8) != 0) WM_EndKeySharing_0x02023ad0(*(int *)(arg0 + 0x7b8));
    if (*(int *)(arg0 + 0x7c0) != 0) WM_EndKeySharing_0x02023ad0(*(int *)(arg0 + 0x7c0));
    if (*(int *)(arg0 + 0x7c8) != 0) WM_EndKeySharing_0x02023ad0(*(int *)(arg0 + 0x7c8));
    func_ov022_02092354((int *)(arg0 + 0x2648));
    func_ov022_0209aed0(arg0);
}
