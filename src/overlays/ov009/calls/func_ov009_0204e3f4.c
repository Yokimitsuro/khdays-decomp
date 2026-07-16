extern char *data_ov009_020563e4[];
extern int func_ov009_0204d818(void);

void func_ov009_0204e3f4(void)
{
    int index = func_ov009_0204d818();

    if (index != -1) {
        *(unsigned char *)(data_ov009_020563e4[1] + 0x963c) |= 1 << index;
    }
}
