typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    char pad00[0xe0];
    Vec3 sourceVec;
    char pad_ec[0x1b1 - 0xec];
    unsigned char flags;
    unsigned char useAltRate;
    unsigned char callbackState;
    int cap;
    int rateA;
    int rateB;
    int source;
    int remaining;
    int position;
} Ov014State;

static inline int fx_mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern int func_ov002_0207687c(void);
extern unsigned int func_020235d0(int, int);
extern unsigned int func_02030788(void);
extern int func_ov002_020766e0(Ov014State *, unsigned char *, int);
extern void func_0202b450(int *, const Vec3 *);
extern void func_ov014_0207fa40(Ov014State *, int);
extern int func_ov014_0207fef4(void);

int func_ov014_0207fd78(Ov014State *self)
{
    int delta;
    int rate;
    unsigned int event;
    unsigned char rec[4];
    Vec3 vec;

    delta = func_ov002_0207687c();
    rate = self->source;
    event = func_020235d0(*(unsigned short *)((char *)self + 0x14),
                           *(unsigned char *)((char *)self + 0x16));
    event &= 0xfffe;
    event <<= 15;
    event >>= 16;
    if ((event & 1) == 0)
        return 0;
    if ((self->flags & 0x80) == 0) {
        {
            if (self->remaining > 0) {
                if (self->useAltRate)
                    rate -= fx_mul(self->rateB, delta);
                else
                    rate -= fx_mul(self->rateA, delta);
                self->remaining -= delta;
                if (self->remaining < 0) self->remaining = 0;
            }
            self->position += rate;
        }
        if (self->position < 0) {
            self->position = 0;
            if (func_02030788() == 0 && (self->flags & 1) == 0) {
                rec[0] = 2;
                if (func_ov002_020766e0(self, rec, 4))
                    self->flags |= 1;
            }
        } else if (self->cap < self->position) {
            self->position = self->cap;
        }
        vec = self->sourceVec;
        vec.y = self->position;
        func_0202b450((int *)((char *)self + 0x38), &vec);
        *(Vec3 *)((char *)self + 0x1c) = vec;
    } else {
        if (*(short *)((char *)self + 0x1d0) >= 0) {
            self->callbackState = 1;
            func_ov014_0207fa40(self, 1);
            return (int)func_ov014_0207fef4;
        }
    }
    return 0;
}
