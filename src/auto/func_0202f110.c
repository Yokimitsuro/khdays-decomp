/* Scale a 4-component vector by a .12 fixed-point scalar with rounding:
 * out[i] = (v[i] * scalar + 0x800) >> 12, computed in signed 64-bit. */
void func_0202f110(unsigned int *out, int *v, int scalar) {
    out[0] = (int)(((long long)v[0] * scalar + 0x800) >> 12);
    out[1] = (int)(((long long)v[1] * scalar + 0x800) >> 12);
    out[2] = (int)(((long long)v[2] * scalar + 0x800) >> 12);
    out[3] = (int)(((long long)v[3] * scalar + 0x800) >> 12);
}
