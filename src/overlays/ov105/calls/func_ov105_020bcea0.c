extern char data_ov105_020bfa20[];
/* Store `value` into the shared command block's argument slot `idx` (base +0x18, stride 4). */
void func_ov105_020bcea0(int idx, int value) {
    *(int *)(*(int *)(data_ov105_020bfa20 + 4) + idx * 4 + 0x18) = value;
}
