/* Enable or disable the ov106 scene's +0x8bc4 animation: track 4 is set to 1.0 or 0 and the node
 * re-evaluates (0202af1c). No-op without a scene. */
extern char *data_ov106_020b8b60;
extern void func_01fff774(void *node, int track, int frame);
extern void func_0202af1c(void *node);

void func_ov106_020b81ac(int enable)
{
    if (data_ov106_020b8b60 == 0) {
        return;
    }
    func_01fff774(data_ov106_020b8b60 + 0x8bc4, 4, enable != 0 ? 0x1000 : 0);
    func_0202af1c(data_ov106_020b8b60 + 0x8bc4);
}
