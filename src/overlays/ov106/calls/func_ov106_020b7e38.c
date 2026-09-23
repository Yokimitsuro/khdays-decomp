/* Whether the ov106 +0x8cd0 widget misses `point` seen through `cam` (0202a818 with a 1.5 margin in
 * mode 1, else 1.0): on a hit test of 0 the widget moves to the projected point (+0x8d74) and
 * refreshes. Returns the test result. */
typedef struct { int x, y, z; } Vec3;

extern char *data_ov106_020b8b60;
extern int func_02023c40(void);
extern void func_ov106_020b7cf8(Vec3 *out, const Vec3 *point, void *cam);
extern unsigned int func_0202a818(void *p, int a);
extern void func_0202aa9c(void *widget);

int func_ov106_020b7e38(void *cam, Vec3 *point)
{
    Vec3 pos;
    int margin = func_02023c40() == 1 ? 0x1800 : 0x1000;
    int hit;

    func_ov106_020b7cf8(&pos, point, cam);
    hit = func_0202a818(data_ov106_020b8b60 + 0x8cd0, margin);
    if (hit == 0) {
        *(Vec3 *)(data_ov106_020b8b60 + 0x8d74) = pos;
        func_0202aa9c(data_ov106_020b8b60 + 0x8cd0);
    }
    return hit;
}
