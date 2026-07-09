extern char *data_ov008_02090f00;

void func_ov008_0204ebbc(int enabled)
{
    int bit;
    int flags;

    bit = enabled != 0 ? 1 : 0;

    bit = (unsigned char)bit;
    bit &= 1;
    flags = *(unsigned char *)(data_ov008_02090f00 + 0x28);
    flags &= ~1;
    *(unsigned char *)(data_ov008_02090f00 + 0x28) = flags | bit;
}
