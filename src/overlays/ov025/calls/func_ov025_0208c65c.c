/*
 * func_ov025_0208c65c -- x3 (ov002/...). Build the panel-id summary row for a menu unit.
 * First re-seed the four sub-slots at self+4 (0202ad74 with the recoil table self+0x13c). Then reset
 * the summary header (out[0]/+4/+0x4c/+0x50) and fill the 13-entry id array (out[8..0x14]) with the
 * "empty" sentinel 0x7f. If a source list `src` is given, copy each active entry's id byte
 * (*(src+0x88) is an array of 0x80-byte records, id at +3; count at src+0x8c), collapse duplicate ids
 * to 0x7f, bubble-sort the ids ascending, and finally turn every remaining 0x7f sentinel into 0xff.
 */
extern void func_0202ad74(unsigned short *arg0, int arg1, unsigned short *arg2, int arg3, int arg4);

struct rec { unsigned char b[0x80]; };

void func_ov025_0208c65c(int self, signed char *out, int src) {
    int i;

    for (i = 0; i <= 3; i++) {
        func_0202ad74((unsigned short *)(self + 4), (unsigned short)i,
                      (unsigned short *)(self + 0x13c), 0, 0);
    }

    out[0] = 0;
    *(int *)(out + 4) = 0;
    *(int *)(out + 0x4c) = 0;
    *(int *)(out + 0x50) = 0;
    for (i = 0; i < 0xd; i++) {
        out[8 + i] = 0x7f;
    }

    if (src != 0) {
        int n = *(int *)(src + 0x8c);
        if (n > 0) {
            int j;
            for (i = 0; i < *(int *)(src + 0x8c); i++) {
                out[8 + i] = ((struct rec *)(*(int *)(src + 0x88)))[i].b[3];
            }
            for (i = 0; i < n - 1; i++) {
                int key = (signed char)out[8 + i];
                for (j = i + 1; j < n; j++) {
                    int v = (signed char)out[8 + j];
                    if (v >= 0 && key == v) {
                        out[8 + j] = 0x7f;
                    }
                }
            }
            for (i = n - 1; i >= 0; i--) {
                for (j = 1; j <= i; j++) {
                    int b = (signed char)out[8 + j];
                    int a = (signed char)out[8 + j - 1];
                    if (a > b) {
                        out[8 + j - 1] = b;
                        out[8 + j] = a;
                    }
                }
            }
        }
        for (i = 0; i < 0xd; i++) {
            if ((signed char)out[8 + i] == 0x7f) {
                out[8 + i] = -1;
            }
        }
    }
}
