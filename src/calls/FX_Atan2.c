/* FX_Atan2 - fixed-point arctangent of a 2D vector, returned as a 1/65536-turn
 * angle (0x10000 = 360 degrees).
 *
 * The two components are sorted into a numerator/denominator pair with the
 * smaller magnitude over the larger, so the ratio handed to the table is
 * always in [0,1]. FX_Inv here is called two-argument style (numer, denom):
 * it is the same reciprocal primitive used elsewhere in the tree as a divide
 * by leaving the caller's denominator sitting in r1. data_02041314 holds
 * atan(i/128) for i = 0..128 in 1/65536-turn units; the ratio is scaled and
 * shifted down to an index into it, then added to or subtracted from the
 * octant's base angle depending on which side of the diagonal the vector
 * falls on. Each axis-aligned or diagonal special case (both zero handled by
 * degenerate ratios, one axis zero, or the two components equal) returns its
 * angle directly without the table.
 */

extern int FX_Inv(int numer, int denom);
extern const short data_02041314[130];

unsigned short FX_Atan2(int x, int y)
{
    int numer;
    int denom;
    int base;
    int add;

    if (x > 0) {
        if (y > 0) {
            if (y > x) {
                numer = x;
                denom = y;
                base = 0;
                add = 1;
            } else if (y < x) {
                numer = y;
                denom = x;
                base = 0x4000;
                add = 0;
            } else {
                return 0x2000;
            }
        } else if (y < 0) {
            int ny = -y;

            if (ny < x) {
                numer = ny;
                denom = x;
                base = 0x4000;
                add = 1;
            } else if (ny > x) {
                numer = x;
                denom = ny;
                base = 0x8000;
                add = 0;
            } else {
                return 0x6000;
            }
        } else {
            return 0x4000;
        }
    } else if (x < 0) {
        int nx = -x;

        if (y < 0) {
            int ny = -y;

            if (ny > nx) {
                numer = nx;
                denom = ny;
                base = -0x8000;
                add = 1;
            } else if (ny < nx) {
                numer = ny;
                denom = nx;
                base = -0x4000;
                add = 0;
            } else {
                return 0xa000;
            }
        } else if (y > 0) {
            if (y < nx) {
                numer = y;
                denom = nx;
                base = -0x4000;
                add = 1;
            } else if (y > nx) {
                numer = nx;
                denom = y;
                base = 0;
                add = 0;
            } else {
                return 0xe000;
            }
        } else {
            return 0xc000;
        }
    } else {
        if (y >= 0) {
            return 0;
        }
        return 0x8000;
    }

    if (denom == 0) {
        return 0;
    }
    if (add) {
        return (unsigned short)(base + data_02041314[FX_Inv(numer, denom) >> 5]);
    }
    return (unsigned short)(base - data_02041314[FX_Inv(numer, denom) >> 5]);
}
