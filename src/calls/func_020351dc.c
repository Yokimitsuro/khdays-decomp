/* Builds the packed parameter index data_0204c590 from table 0x13 (0x73 records, func_02034150 /
 * func_020342e8 / func_020343cc / func_02034258): for every record present (+0x20) the width is the
 * position of the highest bit set in its +0x24 mask (4 bits, `lo`) and the start is the running sum
 * of the previous widths (12 bits, `hi`). */
#pragma thumb on
typedef unsigned char u8;

struct Params {
    unsigned short lo : 4;
    unsigned short hi : 12;
};

typedef struct {
    char pad00[0x20];
    int present;        /* 0x20 */
    u8 mask;            /* 0x24 */
} TableRec;

extern void func_02034150(int table, int a);
extern void func_020342e8(TableRec **rec, int table, int index, int a);
extern void func_020343cc(TableRec **rec);
extern int func_02034258(int table);
extern struct Params data_0204c590[];

void func_020351dc(void)
{
    int start;
    TableRec *rec = 0;
    int i;
    int width;

    func_02034150(0x13, 0xf);
    start = 0;
    for (i = 1; i < 0x74; i++) {
        func_020342e8(&rec, 0x13, i, 0xf);
        data_0204c590[i - 1].lo = 0;
        if (rec->present != 0) {
            u8 mask = rec->mask;
            int b;

            for (b = 0; b < 8; b++) {
                if ((1 << b) & mask) {
                    width = b + 1;
                }
            }
            data_0204c590[i - 1].lo = width;
            data_0204c590[i - 1].hi = start;
            start += width;
        }
        func_020343cc(&rec);
    }
    func_02034258(0x13);
}
