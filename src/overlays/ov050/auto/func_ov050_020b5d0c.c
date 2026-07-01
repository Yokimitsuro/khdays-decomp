int func_ov050_020b5d0c(int i)
{
    unsigned char v = ((unsigned char *)0x918)[i];
    switch (v) {
    case 0x14: return 0x71;
    case 0x15: return 0x72;
    case 0x16: return 0x73;
    default:   return 0x70;
    }
}
