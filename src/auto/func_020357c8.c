/* Clamps `v` into [0, limit] and stores it in the byte pair addressed by (a, b):
 * a selects a 260-byte record, b a two-byte {current, limit} entry inside it at +0x9c. */
extern unsigned char data_0204c678[];

void func_020357c8(int a, int b, int v) {
    unsigned char *e = data_0204c678 + a * 260 + 0x9c + b * 2;
    if (v < 0) {
        v = 0;
    }
    if (v > e[1]) {
        v = e[1];
    }
    e[0] = (unsigned char)v;
}
