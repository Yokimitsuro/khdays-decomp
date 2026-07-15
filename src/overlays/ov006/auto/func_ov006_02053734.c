/* func_ov006_02053734 -- reprogram the title BG char/screen-base registers per sub-state, ov006.
 * Preserving priority+mosaic bits (& 0x43), rewrites main BG0..3 (0x04000008) and sub
 * BG1..3 (0x0400100a) control words to one of two layouts: the default title layout for
 * sub-states 1/2/3/11/14, and the attract/logo layout for sub-states 4..7. All other states
 * (0/8/9/10/12/13 and out of range) leave the registers untouched. The last sub-BG3 base is
 * (v + 0x4f0) where v is the layout's shared base constant (0x524 vs 0x5a4). */
typedef volatile unsigned short vu16;

void func_ov006_02053734(int state) {
    vu16 *bg2 = (vu16 *)0x04000008;
    vu16 *bg3 = (vu16 *)0x0400100a;
    short v;
    switch (state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 10:
    case 11:
    case 13:
    case 14:
        v = 0x524;
        *bg2 = *bg2 & 0x43 | 0x182c;
        bg2[1] = bg2[1] & 0x43 | 0x200;
        bg2[2] = bg2[2] & 0x43 | v;
        bg2[3] = bg2[3] & 0x43 | 0x304;
        *bg3 = *bg3 & 0x43 | 4;
        bg3[1] = bg3[1] & 0x43 | 0x610;
        bg3[2] = bg3[2] & 0x43 | v + 0x4f0;
        return;
    case 4:
    case 5:
    case 6:
    case 7:
        v = 0x5a4;
        *bg2 = *bg2 & 0x43 | 0x18ac;
        bg2[1] = bg2[1] & 0x43 | 0x280;
        bg2[2] = bg2[2] & 0x43 | v;
        bg2[3] = bg2[3] & 0x43 | 0x304;
        *bg3 = *bg3 & 0x43 | 0x84;
        bg3[1] = bg3[1] & 0x43 | 0x690;
        bg3[2] = bg3[2] & 0x43 | v + 0x4f0;
        return;
    default:
        return;
    }
}
