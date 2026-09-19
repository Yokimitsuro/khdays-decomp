/* Shadow update: refresh the +0x3c8 sub-object, then place the +0x390 item's transform (+4) on
 * the actor's +0xa0 pose at the +0x74 position lowered to y = 0x200, scaled in x/z by
 * 1.0 - height(+0x13c)/20 (at least 1/16), and run the base update. */
struct Vec3 { int x, y, z; };
extern void func_ov107_020c9ec8(int sub);
extern void func_0203c9d0(int srt, void *pose);
extern void func_0203ca30(int srt, struct Vec3 *pos);
extern void func_0203ca50(int srt, int sx, int sy, int sz);
extern void func_ov107_020c6980(char *obj, int arg1);

void func_ov278_020ce230(char *obj, int arg1) {
    struct Vec3 pos;
    int scale;

    func_ov107_020c9ec8(*(int *)(obj + 0x3c8));
    scale = 0x1000 - *(int *)(obj + 0x13c) / 20;
    if (scale < 0x100) scale = 0x100;
    pos = *(struct Vec3 *)(obj + 0x74);
    pos.y = 0x200;
    func_0203c9d0(*(int *)(obj + 0x390) + 4, obj + 0xa0);
    func_0203ca30(*(int *)(obj + 0x390) + 4, &pos);
    func_0203ca50(*(int *)(obj + 0x390) + 4, scale, 1, scale);
    func_ov107_020c6980(obj, arg1);
}
