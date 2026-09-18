/* Model update hook of the ov220 enemy: refreshes the +0x394 item, runs the shared model update,
 * copies the +0xa0 transform into the +0x398 slot scaled uniformly by 0x14cd, then into the
 * +0x38c item's +0x10 transform, and from there into the +0x388 owner's +0x10 transform. */
struct s44 {
    int a[11];
};

struct obj {
    char pad[0xa0];
    struct s44 src;
    char pad2[0x388 - 0xa0 - 0x2c];
    char *p388;
    char *p38c;
    int p390;
    void *p394;
    struct s44 copy;
};

extern void func_ov107_020c9ec8(void *item);
extern void func_ov107_020c6980(struct obj *o, int a);
extern void func_0203ca9c(struct s44 *t, int scale);

void func_ov220_020d1c5c(struct obj *o, int a)
{
    func_ov107_020c9ec8(o->p394);
    func_ov107_020c6980(o, a);
    o->copy = o->src;
    func_0203ca9c(&o->copy, 0x14cd);
    *(struct s44 *)(o->p38c + 0x10) = o->src;
    *(struct s44 *)(*(char **)(o->p388) + 0x10) = *(struct s44 *)(o->p38c + 0x10);
}
