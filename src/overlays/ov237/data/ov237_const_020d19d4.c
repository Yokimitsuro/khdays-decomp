/* ov237 .rodata 0x020d19d4-0x020d19f8: three points 0xa00 ahead on x forming an equilateral
 * triangle of radius 0x500 in the y/z plane (at 90, -30 and 210 degrees). No code references
 * it: an initializer whose copy the compiler dropped. */
typedef struct Vec3 {
    int x, y, z;
} Vec3;

const Vec3 data_ov237_020d19d4[3] = {
    { 0xa00, 0, 0x500 },
    { 0xa00, 0x454, -0x280 },
    { 0xa00, -0x454, -0x280 },
};
