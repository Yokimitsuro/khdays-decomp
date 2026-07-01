extern int func_ov107_020c6980();
extern int func_ov107_020c9ec8();

typedef struct {
    int a[4];
    int b[4];
    int c[3];
} Block;

typedef struct {
    char _pad0[0xa0];
    Block block;        /* 0xa0 .. 0xcc */
    char _pad1[0x388 - 0xcc];
    char **p388;        /* 0x388 */
    char *p38c;         /* 0x38c */
    int field_390;      /* 0x390 */
} Obj;

void func_ov181_020cc1d8(Obj *obj, int arg1)
{
    func_ov107_020c9ec8(obj->field_390);
    func_ov107_020c6980(obj, arg1);

    *(Block *)(*obj->p388 + 0x10) = obj->block;
    *(Block *)(obj->p38c + 0x10) = obj->block;
}
