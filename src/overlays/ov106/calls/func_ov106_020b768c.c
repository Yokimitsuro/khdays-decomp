/* Tear down the ov106 scene: field 0x248c is cleared, the scene layers close (020b7c50), window 0
 * spans the whole screen and the sub engine's windows are disabled, the data_ov106_020b8ab4 resource
 * is released, the +0x8b38 model, the +0x8cd0 and +0x8bc4 widgets and the +0x8e40 handle are freed,
 * and the scene pointer clears. */
typedef unsigned short u16;
typedef unsigned int u32;

extern char *data_ov106_020b8b60;
extern char data_ov106_020b8ab4[];
extern void func_020235e8(int field, int width, int value);
extern void func_ov106_020b7c50(void);
extern void func_02000fb4(int a, void *b);
extern void func_0202e944(void *p);
extern void func_0202a7dc(void *p);
extern void func_02034138(char arg0);
extern void WM_EndKeySharing_0x02023ad0(int handle);
extern void func_02020aa8(int nId, int nFlags);

void func_ov106_020b768c(void)
{
    func_020235e8(0x248c, 1, 0);
    func_ov106_020b7c50();
    *(volatile u16 *)0x04000040 = 0xff;
    *(volatile u16 *)0x04000044 = 0xc0;
    *(volatile u32 *)0x04001000 &= ~0xe000;
    func_02000fb4(1, data_ov106_020b8ab4);
    func_0202e944(data_ov106_020b8b60 + 0x8b38);
    func_0202a7dc(data_ov106_020b8b60 + 0x8cd0);
    func_0202a7dc(data_ov106_020b8b60 + 0x8bc4);
    func_02034138(1);
    WM_EndKeySharing_0x02023ad0(*(int *)(data_ov106_020b8b60 + 0x8e40));
    func_02020aa8(0x14, 0);
    data_ov106_020b8b60 = 0;
}
