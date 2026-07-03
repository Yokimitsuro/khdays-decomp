int func_ov266_020cdde8(int a, int b)
{
    int diff = a - b;
    int mag = diff < 0 ? -diff : diff;
    if (mag < 0x3244)
        return diff;
    if (diff >= 0)
        return -(0x3244 * 2 - diff);
    return diff + 0x6488;
}
