typedef unsigned char u8;

int func_01fffe14(void);
int func_01fffde0(int idx);
int func_ov022_020ad61c(int arg0, int arg1);

typedef struct {
    u8 pad_00[0x1c];
    u8 field_1c[1];
    u8 pad_1d[0x40 - 0x1d];
    u8 flags_40;
} Obj_ov015_0208075c;

void *func_ov015_0208075c(Obj_ov015_0208075c *obj)
{
    if (obj->flags_40 & 2)
    {
        if (func_ov022_020ad61c(func_01fffde0(func_01fffe14()), 0xc))
            return obj->field_1c;
    }

    return 0;
}
