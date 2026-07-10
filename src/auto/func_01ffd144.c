/* Scales a 3-vector by a fixed-point factor: out[i] = (s64)a * in[i] >> 27. */
void func_01ffd144(int a, int *in, int *out) {
    out[0] = (int)(((long long)a * in[0]) >> 27);
    out[1] = (int)(((long long)a * in[1]) >> 27);
    out[2] = (int)(((long long)a * in[2]) >> 27);
}
