extern int func_0203c634();

struct Inner {
    unsigned char *ptr0;        /* +0x00 */
    char pad[0x30 - 4];
    unsigned char *flagptr;     /* +0x30 */
};

struct Obj {
    char pad0;                  /* +0x00 */
    struct Inner *inner;        /* +0x04 */
    char pad1[0x20 - 8];
    signed char field20;        /* +0x20 */
};

void func_ov124_020d0838(struct Obj *obj)
{
    struct Inner *inner = obj->inner;
    if (inner->flagptr[0] != 0) {
        return;
    }
    inner->ptr0[0x1c7] = 2;
    func_0203c634(obj, obj->field20, 0);
}
