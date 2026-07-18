int func_ov100_020babb8(int i)
{
    unsigned char v = ((unsigned char *)0x918)[i];
    switch (v) {
    case 5: case 6: case 23:
        return 0x91;
    case 7: case 8: case 9: case 10:
        return 0x92;
    case 11: case 12: case 13:
        return 0x93;
    case 14: case 15:
        return 0x94;
    case 16: case 17: case 18: case 19:
        return 0x95;
    case 20:
        return 0x8e;
    case 21:
        return 0x8f;
    case 22:
        return 0x90;
    default:
        return 0x8d;
    }
}
