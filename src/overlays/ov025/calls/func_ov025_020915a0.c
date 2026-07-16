extern const char data_ov025_020b4d2c[];
extern const char data_ov025_020b4d3c[];
extern void GFXi_EnqueueCommand(int command, int param, const void *data, int size);

void func_ov025_020915a0(int unused, int index, int use_alt_data)
{
    const void *data;
    int param = ((index << 3) + 0x30) << 1;

    if (use_alt_data != 0) {
        data = data_ov025_020b4d3c;
    } else {
        data = data_ov025_020b4d2c;
    }

    GFXi_EnqueueCommand(0xf, param, data, 0x10);
}
