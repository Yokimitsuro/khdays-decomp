/*
 * Build an axis-aligned bounding box from a sphere.
 *
 * src = { center_x, center_y, center_z, radius }
 * dst = { min_x, min_y, min_z, max_x, max_y, max_z }
 *
 * The source center components are re-read for the max corner (the compiler
 * does not CSE them), matching the original's reload-per-use codegen.
 */
void func_02039824(int *dst, int *src) {
    int radius = src[3];

    dst[0] = src[0] - radius;
    dst[1] = src[1] - radius;
    dst[2] = src[2] - radius;
    dst[3] = src[0] + radius;
    dst[4] = src[1] + radius;
    dst[5] = src[2] + radius;
}
