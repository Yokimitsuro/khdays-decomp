struct S { char pad[0x7c]; int flags; char pad2[0x8c - 0x80]; };

void func_020326cc(struct S *base, int index)
{
    if (index < 0) return;
    base[index].flags &= ~2;
}
