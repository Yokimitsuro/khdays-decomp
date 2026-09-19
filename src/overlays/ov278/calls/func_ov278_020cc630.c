/* Shadow update (first form): refresh the +0x3ac sub-object, run the base update, mirror bit 1
 * of the +0x9c list's +0x5c into the +0x388 item's +0x5c bit 1, then place that item's transform
 * (+4) on the actor's +0xa0 pose at the +0x74 position lowered to y = 0x200, scaled in x/z by
 * 1.0 - height(+0x13c)/20 (at least 1/16). */
struct Vec3 { int x, y, z; };
struct Flags5c { int b0 : 1; int b1 : 1; };
extern void func_ov107_020c9ec8(int sub);
extern void func_ov107_020c6980(char *obj, int arg1);
extern void func_0203c9d0(int srt, void *pose);
extern void func_0203ca30(int srt, struct Vec3 *pos);
extern void func_0203ca50(int srt, int sx, int sy, int sz);

void func_ov278_020cc630(char *obj, int arg1) {
    struct Vec3 pos;
    int scale;

    func_ov107_020c9ec8(*(int *)(obj + 0x3ac));
    scale = 0x1000 - *(int *)(obj + 0x13c) / 20;
    if (scale < 0x100) scale = 0x100;
    pos = *(struct Vec3 *)(obj + 0x74);
    pos.y = 0x200;
    func_ov107_020c6980(obj, arg1);
    ((struct Flags5c *)(*(int *)(obj + 0x388) + 0x5c))->b1 = ((struct Flags5c *)(*(int *)(obj + 0x9c) + 0x5c))->b1;
    func_0203c9d0(*(int *)(obj + 0x388) + 4, obj + 0xa0);
    func_0203ca30(*(int *)(obj + 0x388) + 4, &pos);
    func_0203ca50(*(int *)(obj + 0x388) + 4, scale, 1, scale);
}
