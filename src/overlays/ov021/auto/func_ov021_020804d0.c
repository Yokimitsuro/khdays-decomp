void func_ov021_020804d0(int actor, int delta)
{
    int flag;
    int t = *(int *)(actor + 0x2b8) - delta;
    *(int *)(actor + 0x2b8) = t;
    if (t < 0) *(int *)(actor + 0x2b8) = 0;
    flag = *(unsigned short *)(actor + 0x12) & 4;
    if (flag == 0) return;
    {
        int scaled = (int)(((long long)(*(int *)(actor + 0x2b8) / 300) * 0x5000 + 0x800) >> 12);
        if (flag != 0) {
            *(int *)(actor + 0x1ec) = scaled;
            *(int *)(actor + 0x1e8) = scaled;
            *(int *)(actor + 0x1e4) = scaled;
        }
    }
}
