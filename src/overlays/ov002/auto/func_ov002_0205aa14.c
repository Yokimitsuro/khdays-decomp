/*
 * Write four tile-map entries (param_2..param_5), each OR'd with the 0x9000
 * attribute bits, to the block at param_1: offsets +0, +2, +0x40, +0x42.
 */
void func_ov002_0205aa14(int param_1, int param_2, int param_3, int param_4, unsigned short param_5) {
    *(unsigned short *)(param_1 + 0x00) = param_2 | 0x9000;
    *(unsigned short *)(param_1 + 0x02) = param_3 | 0x9000;
    *(unsigned short *)(param_1 + 0x40) = param_4 | 0x9000;
    *(unsigned short *)(param_1 + 0x42) = param_5 | 0x9000;
}
