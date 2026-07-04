extern long long func_02020400(int num, int den);

/* Linear interpolation: base + (elapsed * (target - base)) / duration,
   clamped to target once elapsed reaches duration. */
int func_0201e16c(int *p) {
    if (p[2] < p[3]) {
        int base = p[0];
        return base + (int)func_02020400(p[2] * (p[1] - base), p[3]);
    }
    return p[1];
}
