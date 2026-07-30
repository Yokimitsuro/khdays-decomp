/*
 * QuatFromAxisAngle - build a unit quaternion from a rotation axis and angle.
 *
 * out[0] = cos(angle/2), out[1..3] = sin(angle/2) * axis[0..2], all fx32 (Q12).
 * The half-angle (angle >> 1) is scaled to a sin/cos table index by a 64-bit fixed-point
 * multiply (round-to-nearest), then the table data_0203d210 - a flat array of interleaved
 * (sin, cos) s16 pairs - is read as [idx*2] = sin, [idx*2+1] = cos. Each axis component is
 * multiplied by sin in Q12 with 0x800 rounding.
 *
 * A hot MAIN math primitive (hundreds of callers across animation/3D code). The angle->index
 * scale and the axis multiplies must stay as full 64-bit expressions, and the two idx shifts
 * must collapse into one expression, or mwcc spills idx*2 to the wrong scratch register.
 */

extern const short data_0203d210[];

void func_0202f188(int *out, int *axis, int angle)
{
    int idx;
    int sin;

    idx = (int)((unsigned)((int)(((long long)(angle >> 1) * 0x28be60db9391LL + 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    out[0] = data_0203d210[idx * 2 + 1];
    sin = data_0203d210[idx * 2];
    out[1] = (int)(((long long)sin * axis[0] + 0x800) >> 0xc);
    out[2] = (int)(((long long)sin * axis[1] + 0x800) >> 0xc);
    out[3] = (int)(((long long)sin * axis[2] + 0x800) >> 0xc);
}
