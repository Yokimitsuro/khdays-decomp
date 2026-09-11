typedef unsigned char u8;
typedef unsigned int u32;

struct Ov023Work
{
    /* 0x0000 */ u8 pad_0[0x159c];
    /* 0x159c */ u32 field_159c;
    /* 0x15a0 */ u32 field_15a0;
    /* 0x15a4 */ u32 field_15a4;
    /* 0x15a8 */ u32 field_15a8;
    /* 0x15ac */ u8 pad_15ac[8];
    /* 0x15b4 */ u32 field_15b4;
};

void func_ov023_02087210(struct Ov023Work *work)
{
    work->field_159c = work->field_15a0 = work->field_15a4 = 0;
    if (work->field_15b4 != 2)
    {
        work->field_15a8 = 0;
    }
}
