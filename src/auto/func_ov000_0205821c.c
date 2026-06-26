struct S {
    char pad[0x10];
    unsigned long long bits;
};

void func_ov000_0205821c(struct S *s, unsigned short *outW, unsigned short *outH)
{
    int i;
    int j;
    unsigned short w = 0;
    unsigned short h = 0;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 8; j++) {
            if (s->bits & (1ULL << (j + i * 8))) {
                if (j + 1 > w) {
                    w = (unsigned short)(j + 1);
                }
                if (i + 1 > h) {
                    h = (unsigned short)(i + 1);
                }
            }
        }
    }

    *outW = w;
    *outH = h;
}
