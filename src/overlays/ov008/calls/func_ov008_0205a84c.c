/* Return 1 if any slot 0..count-1 passes func_ov008_0205127c, else 0; count comes
 * from func_ov008_02051210. */
extern int func_ov008_02051210(void);
extern int func_ov008_0205127c(int index);

int func_ov008_0205a84c(void) {
    int count = func_ov008_02051210();
    unsigned short i = 0;
    if (count != 0) {
        do {
            if (func_ov008_0205127c(i) != 0) return 1;
            i++;
        } while ((unsigned int)count > i);
    }
    return 0;
}
