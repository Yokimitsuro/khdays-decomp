/* Reset the ov106 scene's +0x8bc4 widget position: while +0x8ccc is set, its +0x8c68 position takes the
 * default (data_ov106_020b8a78) and the widget refreshes (0202aa9c). */
typedef struct { int x, y, z; } Vec3;

extern char *data_ov106_020b8b60;
extern const Vec3 data_ov106_020b8a78;
extern void func_0202aa9c(void *widget);

void func_ov106_020b7ec0(void)
{
    char *scene = data_ov106_020b8b60;

    if (*(int *)(scene + 0x8ccc) == 0) {
        return;
    }
    *(Vec3 *)(scene + 0x8c68) = data_ov106_020b8a78;
    func_0202aa9c(scene + 0x8bc4);
}
