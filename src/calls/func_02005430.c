/* Binary search the sin/cos table (data_0203d210, pairs of [cos,sin] shorts
 * per angle index) for the entry whose cos value matches nCos, splitting the
 * search range by the sign of nCos (upper vs lower half of the circle).
 * Converts the matching (or nearest, if no exact match) index back to a
 * 16-bit angle. */
typedef short s16;
typedef unsigned short u16;

extern short data_0203d210[];

u16 func_02005430(int nCos) {
    int lo, hi;
    int mid;
    s16 target;

    if (nCos >= 0) {
        lo = 0;
        hi = 0x400;
    } else {
        lo = 0x400;
        hi = 0x800;
    }
    target = (s16)nCos;

    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (target == data_0203d210[mid * 2 + 1]) {
            break;
        }
        if (data_0203d210[mid * 2 + 1] < target) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    return (u16)(((mid * 2 + 1) << 16) / 0x2000);
}
