typedef struct { unsigned long long x, mul, add; } Rand64;
typedef struct { unsigned x, mul, add; } Rand32;
extern void func_02003b68(unsigned *buf);
extern Rand32 data_0204c168;
extern Rand64 data_0204c174;
static inline void initRand64(Rand64 *c, unsigned long long seed) {
    c->x = seed;
    c->mul = 0x5D588B656C078965ULL;
    c->add = 0x269EC3;
}
static inline void initRand32(Rand32 *c, unsigned seed) {
    c->x = seed;
    c->mul = 0x5D588B65;
    c->add = 0x269EC3;
}
void func_ov001_0204cccc(void) {
    unsigned buf[8];
    unsigned r;
    unsigned long long x;
    int i;
    func_02003b68(buf);
    for (i = 0; i < 8; i++) {
        unsigned v = buf[i];
        unsigned tmp;
        x ^= v;
        tmp = r ^ v;
        r = (tmp >> 5) | (tmp << 27);
        x = (x >> 9) | ((x & 0x1ff) << 55);
    }
    initRand64(&data_0204c174, x);
    initRand32(&data_0204c168, r);
}
