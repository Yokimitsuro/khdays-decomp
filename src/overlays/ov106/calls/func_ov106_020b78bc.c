/* Reset the ov106 scene's +0x8cd0 widget: it is placed on data_ov106_020b8ae0 at the origin (depth
 * 2.0x, style 5, 020b7758), refreshed (020b7794) and the four queued points are freed. */
typedef struct { int x, y, z; } Vec3;
struct Ov106Scene { char pad[0x8dd8]; Vec3 points[4]; int used[4]; };

extern struct Ov106Scene *data_ov106_020b8b60;
extern char data_ov106_020b8ae0[];
extern void func_ov106_020b7758(void *self, void *owner, const Vec3 *pos, int depth, int style);
extern void func_ov106_020b7794(void *self);

void func_ov106_020b78bc(void)
{
    Vec3 origin = {0, 0, 0};
    int i;

    func_ov106_020b7758((char *)data_ov106_020b8b60 + 0x8cd0, data_ov106_020b8ae0, &origin, 0x20000, 5);
    func_ov106_020b7794((char *)data_ov106_020b8b60 + 0x8cd0);
    for (i = 0; i < 4; i++) {
        data_ov106_020b8b60->used[i] = 0;
    }
}
