typedef unsigned char u8;

typedef struct {
    u8 bKind;
    u8 bMode;
    u8 bIndex;
    u8 pad0003[0x4a9];
} Ctx;

extern Ctx *g_ctx[1];

extern int classify(int *pOut, int nMode);
extern void call4(int a, int b, int c, int d);
extern void call3(int a, int b, int c);
extern int call0(void);
extern void tail(int a, int b, int c);

void repro(int nFrom, int nTo) {
    int nColumn;
    int nTag;
    Ctx *s = g_ctx[0];
    int nClass = classify(&nColumn, s->bMode);

    call3(s->bMode, nTo, 0);

    switch (nClass) {
    case 0:
        switch (nFrom) {
        case 0:
            call3(s->bIndex, s->bKind, 0);
            break;
        case 1: {
            int nValue = call0();

            call4(4, 0, 0, 0);
            call3(nFrom + 2, nValue, 0);
            break;
        }
        }
        break;

    case 1: {
        int nOffset = nColumn * 6;

        call4(nFrom + nOffset, nFrom, 1, 0);
        nClass = nColumn * 6 + nTo;
        call4(nClass, nTo, 1, 1);
        s->bIndex = (u8)nClass;
        break;
    }

    case 2: {
        int nOld = nFrom + nColumn * 6;

        nTag = 0;
        if (nOld != 0) {
            nTag = call0();
        }
        call4(nOld, nTag, 1, 0);
        break;
    }
    }

    s->bKind = (u8)nTo;
    tail(s->bMode, nTo, 0);
}
