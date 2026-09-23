/* Place the ov218 actor at `pos` for `owner`: +0x398 clears, it is registered there (020c5c54), the
 * spawn point is kept in +0x3ac and its guard flag (+0x60 high byte bit 0) is set. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c5c54(char *self, int owner, Vec3 *pos);

void func_ov218_020cdff8(char *self, int owner, Vec3 *pos)
{
    *(int *)(self + 0x398) = 0;
    func_ov107_020c5c54(self, owner, pos);
    *(Vec3 *)(self + 0x3ac) = *pos;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
}
