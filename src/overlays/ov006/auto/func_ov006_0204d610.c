/* Remaps a menu entry id onto its resource slot. Entry 12 has no slot and falls back to 0, the
 * same as anything out of range. */
int func_ov006_0204d610(int id) {
    int slot = 0;
    switch (id) {
    case 0:  slot = 0xd;  break;
    case 1:  slot = 2;    break;
    case 2:  slot = 4;    break;
    case 3:  slot = 0xc;  break;
    case 4:  slot = 8;    break;
    case 5:  slot = 0xf;  break;
    case 6:  slot = 3;    break;
    case 7:  slot = 1;    break;
    case 8:  slot = 6;    break;
    case 9:  slot = 9;    break;
    case 10: slot = 0xa;  break;
    case 11: slot = 7;    break;
    case 12: slot = 0;    break;
    case 13: slot = 0xe;  break;
    case 14: slot = 0x10; break;
    case 15: slot = 5;    break;
    case 16: slot = 0xb;  break;
    case 17: slot = 0x11; break;
    case 18: slot = 0x12; break;
    }
    return slot;
}
