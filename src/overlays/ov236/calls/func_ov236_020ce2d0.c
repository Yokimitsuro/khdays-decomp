/* Model pose init: after the base 020c4924 step, mirror bit 1 of the +0x9c list's +0x5c into
 * the +0x390 item's, then for each rider pair: push the +0x3ac clip's pose (+4) into the +0x39c
 * item's +0x10 and the +0x3c0 handle's target, seat the +0x398 item's +0x58 anchor at the +0x3a8
 * clip's +0x14 position with its +0x64 direction from the +0x3a8 to the +0x3ac position
 * (normalised, length at +0x70); likewise +0x3b4 -> +0x3a4 / +0x3c4 and +0x3b0 -> +0x3a0. */
typedef struct { int x, y, z; } Vec3;
struct blk11 { int w[11]; };
struct Flags5c { int b0 : 1; int b1 : 1; };
struct Ov236Anchor { Vec3 pos; Vec3 dir; int len; };
extern void func_ov107_020c4924(void *obj);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);

void func_ov236_020ce2d0(char *obj) {
    struct Ov236Anchor *a;

    func_ov107_020c4924(obj);
    ((struct Flags5c *)(*(int *)(obj + 0x390) + 0x5c))->b1 = ((struct Flags5c *)(*(int *)(obj + 0x9c) + 0x5c))->b1;
    *(struct blk11 *)(*(char **)(obj + 0x39c) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x3ac) + 4);
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x3c0)) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x3ac) + 4);
    a = (struct Ov236Anchor *)(*(char **)(obj + 0x398) + 0x58);
    a->pos = *(Vec3 *)(*(char **)(obj + 0x3a8) + 0x14);
    VEC_Subtract((Vec3 *)(*(char **)(obj + 0x3ac) + 0x14), (Vec3 *)(*(char **)(obj + 0x3a8) + 0x14), &a->dir);
    a->len = func_01ff8d18(&a->dir, &a->dir);
    *(struct blk11 *)(*(char **)(obj + 0x3a4) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x3b4) + 4);
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x3c4)) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x3b4) + 4);
    a = (struct Ov236Anchor *)(*(char **)(obj + 0x3a0) + 0x58);
    a->pos = *(Vec3 *)(*(char **)(obj + 0x3b0) + 0x14);
    VEC_Subtract((Vec3 *)(*(char **)(obj + 0x3b4) + 0x14), (Vec3 *)(*(char **)(obj + 0x3b0) + 0x14), &a->dir);
    a->len = func_01ff8d18(&a->dir, &a->dir);
}
