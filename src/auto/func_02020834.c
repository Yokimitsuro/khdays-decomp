/* Clears the two three-word tables and the two flag bytes, and returns 1.
 * The zero stored everywhere is taken FROM the loop counter (`z = i`), which is how the
 * ROM gets its `mov r2, r3` instead of a second `mov #0`. */
extern int data_0204bd88[];
extern int data_0204bd94[];
extern char data_0204bd84[];

int func_02020834(void) {
    int i = 0;
    int z = i;
    do {
        data_0204bd88[i] = z;
        data_0204bd94[i] = z;
        i = i + 1;
    } while (i < 3);
    data_0204bd84[0] = (char)z;
    data_0204bd84[1] = (char)z;
    return 1;
}
