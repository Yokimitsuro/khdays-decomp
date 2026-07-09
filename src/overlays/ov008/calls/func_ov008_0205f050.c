extern const char data_ov008_02090360[];
extern const char data_ov008_02090370[];
extern void GFXi_EnqueueCommand(int command, int param, const void *data, int size);

void func_ov008_0205f050(int unused, int index, int use_alt_data)
{
    const void *data;
    int param = ((index << 3) + 0x30) << 1;

    if (use_alt_data != 0) {
        data = data_ov008_02090370;
    } else {
        data = data_ov008_02090360;
    }

    GFXi_EnqueueCommand(0xf, param, data, 0x10);
}
