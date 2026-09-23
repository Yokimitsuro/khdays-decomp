/* Per-frame ov106 camera step: unless the ov022 camera is unset (-1), the +0x8b4c camera bounds are set
 * to +/-3.7 x +/-4.85 and then +/-95.0 x +/-127.0, the queued points are tested against the camera
 * (020b7dc4), the +0x8bc4 widget resets (020b7ec0) and the camera commits (02023cc0). */
extern char *data_ov106_020b8b60;
extern int func_ov022_02083f0c(void);
extern void *func_ov002_0204cb68(void);
extern void func_02023d70(void *bounds, int right, int left, int top, int bottom);
extern void func_ov106_020b7dc4(void *target);
extern void func_ov106_020b7ec0(void);
extern void func_02023cc0(void *camera);

void func_ov106_020b7f08(void)
{
    void *camera;

    if (func_ov022_02083f0c() == -1) {
        return;
    }
    camera = func_ov002_0204cb68();
    func_02023d70(data_ov106_020b8b60 + 0x8b4c, 0x3b33, -0x3b33, -0x4d9a, 0x4d9a);
    func_02023d70(data_ov106_020b8b60 + 0x8b4c, 0x5f000, -0x5f000, -0x7f000, 0x7f000);
    func_ov106_020b7dc4(camera);
    func_ov106_020b7ec0();
    func_02023cc0(camera);
}
