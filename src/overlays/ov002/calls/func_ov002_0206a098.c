extern void WM_EndKeySharing_0x02023ad0(int handle);
extern void func_ov002_0206a080(void);
extern char *data_ov002_0207fa00;
/* Close the key-sharing session held at rootCtx+0x8d10 (if any) and run the follow-up. */
void func_ov002_0206a098(void) {
    int handle = *(int *)((int)data_ov002_0207fa00 + 0x8d10);
    if (handle != -1) {
        WM_EndKeySharing_0x02023ad0(handle);
        func_ov002_0206a080();
    }
}
