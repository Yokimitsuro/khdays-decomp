typedef struct {
    char pad[4];
    void *container;
} Owner;

typedef struct {
    char pad0[0x60];
    unsigned short half60 : 8;
    char pad1[0x1ac - 0x62];
    unsigned short flags1ac;
} Elem;

typedef struct {
    void *f0;
    char pad[4];
    unsigned int f8 : 8;
} Inner;

extern int func_01fffd70(void *o);
extern int func_01fffd8c(void *o);
extern int func_ov107_020c3504(void *p, void *position, int flag);

Elem *func_ov107_020c9094(Owner *owner, void *position, void **outHit)
{
    Inner *innerIt;
    void *container;
    int *outerIt;
    Elem *cand;
    unsigned short flags1ac;
    int flag;

    container = owner->container;
    outerIt = (int *)func_01fffd70((char *)container + 0x80);
    cand = !outerIt ? 0 : *(Elem **)outerIt;

    while (cand != 0) {
        if (cand == (Elem *)owner) {
            goto nextOuter;
        }

        if (!(cand->half60 & 1)) {
            goto nextOuter;
        }

        flags1ac = cand->flags1ac;
        if (flags1ac & 1) {
            goto nextOuter;
        }
        if (flags1ac & 2) {
            goto nextOuter;
        }
        if (flags1ac & 4) {
            goto nextOuter;
        }

        innerIt = (Inner *)func_01fffd70((char *)cand + 0x22c);
        if (innerIt != 0) {
            flag = 0;
            do {
                if (innerIt->f8 & 1) {
                    if (func_ov107_020c3504(innerIt->f0, position, flag) != 0) {
                        if (outHit != 0) {
                            *outHit = innerIt;
                        }
                        return cand;
                    }
                }
                innerIt = (Inner *)func_01fffd8c((char *)cand + 0x22c);
            } while (innerIt != 0);
        }

    nextOuter:
        outerIt = (int *)func_01fffd8c((char *)container + 0x80);
        cand = !outerIt ? 0 : *(Elem **)outerIt;
    }

    return 0;
}
