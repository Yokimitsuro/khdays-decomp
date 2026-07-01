struct S {
    unsigned char pad0[6];
    unsigned short lo;   /* +6 */
    unsigned short hi;   /* +8 */
    unsigned char pad1[0x23 - 0xA];
    unsigned char flag;  /* +0x23 */
};

int func_ov026_0208473c(struct S *p, unsigned int v) {
    if (p->flag) {
        return 0;
    }
    if (p->lo <= v && v <= p->hi) {
        return 1;
    }
    return 0;
}
