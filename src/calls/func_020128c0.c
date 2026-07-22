/* Reads the current display mode from REG_DISPCNT, looks the mode up in `tbl`, folds the
 * value into 0..7 and tail-calls func_020056b4 with the DISPCNT bit-3 flag.
 *
 * The table load must be written inline as `tbl[*reg & 7]`: bound to a `mode` local first,
 * mwcc schedules the load after the boolean materialisation and colours the flag one
 * register away from the ROM's r0. */
extern void *func_020056b4();

void *func_020128c0(unsigned char *tbl) {
    volatile unsigned int *reg = (volatile unsigned int *)0x4000000;
    int v = tbl[*reg & 7];
    int on = (*reg & 8) != 0;
    int b2 = on != 0;
    if (v >= 8) {
        v -= 8;
    }
    return func_020056b4(1, v, b2);
}
