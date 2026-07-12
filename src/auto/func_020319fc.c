/*
 * Append a 32-byte record to a bounded table embedded at param_1+0x4638.
 * Header: capacity at +0x462c, count at +0x4634; the table is full at count >=
 * capacity/4. On success stores four shorts (param_2[0..3] >> 4) into the new
 * slot at offsets +6/+0xe/+0x16/+0x1e, bumps the count, and returns the slot
 * index; returns -1 when full.
 */
int func_020319fc(int param_1, int *param_2) {
    int *hdr = (int *)(param_1 + 0x4000);
    int cap = hdr[0x18b];
    int count = hdr[0x18d];
    int result = -1;

    if (count < cap / 4) {
        int slot = param_1 + 0x4638 + count * 0x20;
        *(short *)(slot + 6)    = (short)(param_2[0] >> 4);
        *(short *)(slot + 0xe)  = (short)(param_2[1] >> 4);
        *(short *)(slot + 0x16) = (short)(param_2[2] >> 4);
        *(short *)(slot + 0x1e) = (short)(param_2[3] >> 4);
        hdr[0x18d] = hdr[0x18d] + 1;
        result = count;
    }
    return result;
}
