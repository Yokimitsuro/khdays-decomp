/* End the active key-sharing session (if any) and mark the handle slot free. */
extern void WM_EndKeySharing_0x02023ad0(int handle);
extern int data_ov002_0207f00c;

void func_ov002_0206ead8(void) {
    int handle = *(int *)&data_ov002_0207f00c;
    if (handle != -1) {
        WM_EndKeySharing_0x02023ad0(handle);
        *(int *)&data_ov002_0207f00c = -1;
    }
}
