struct S { char pad[0x74]; int field_74; };

void func_0203281c(int *base, int index, int value)
{
    if (index < 0) return;
    *(int *)((char *)base + index * 0x8c + 0x74) = value & 3;
}
