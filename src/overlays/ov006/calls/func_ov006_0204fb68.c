/* func_ov006_0204fb68 -- set the title-screen "pending input" state.
 * When the input object is live (ctx+0x4e8 != 0), set its ready bit (ctx+0x4ad bit0) and store
 * the key/param at ctx+0x4ae. Always sets the top-level pending bit (ctx+0x4a8 bit0). */
extern int data_ov006_020565e4;   /* -> title-screen context */

void func_ov006_0204fb68(unsigned char param_1) {
    if (*(int *)(data_ov006_020565e4 + 0x4e8) != 0) {
        *(unsigned char *)(data_ov006_020565e4 + 0x4ad) =
            (*(unsigned char *)(data_ov006_020565e4 + 0x4ad) & ~1) | 1;
        *(unsigned char *)(data_ov006_020565e4 + 0x4ae) = param_1;
    }
    *(unsigned int *)(data_ov006_020565e4 + 0x4a8) =
        (*(unsigned int *)(data_ov006_020565e4 + 0x4a8) & 0xfffffffe) | 1;
}
