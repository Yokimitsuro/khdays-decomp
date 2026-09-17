/* NitroSystem nsbca.c: pivotUtil_, the four off-pivot matrix cells written by a pivot-compressed
 * joint rotation (getRotData_ / getRotDataEx_), indexed by the pivot position 0-8. */
typedef unsigned char u8;

const u8 data_02041ae0[9][4] = {
    {4, 5, 7, 8},
    {3, 5, 6, 8},
    {3, 4, 6, 7},

    {1, 2, 7, 8},
    {0, 2, 6, 8},
    {0, 1, 6, 7},

    {1, 2, 4, 5},
    {0, 2, 3, 5},
    {0, 1, 3, 4}
};
