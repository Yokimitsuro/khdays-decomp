/* Pick this enemy's step count for its current band: the progress value at +0x7b0 runs from
 * 0x9000 in 0x3000 steps over 15 bands (past the last band it wraps to the first); the second row
 * applies once the shared rig's +0x2cd4 flag is set. */
extern char *data_ov078_020ba4e0;

int func_ov078_020b9508(char *self) {
    char *rig = data_ov078_020ba4e0 + 0xd4 + 0x2c00;
    int table[2][15] = {
        { 3, 3, 3, 2, 2, 2, 2, 2, 2, 3, 3, 3, 2, 2, 2 },
        { 2, 2, 2, 3, 3, 3, 1, 1, 1, 2, 2, 2, 3, 3, 3 },
    };
    int *row;
    int band;

    band = (*(int *)(self + 0x7b0) - 0x9000) / 0x3000;
    if (band >= 15) band = 0;
    row = (*(int *)rig != 0) ? table[1] : table[0];
    return row[band];
}
