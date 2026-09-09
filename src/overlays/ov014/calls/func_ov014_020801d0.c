extern void func_ov002_020767ec(void *entry);
extern unsigned int func_020235d0(int bitOffset, int bitCount);
extern void func_020235e8(unsigned int id, unsigned int bitCount,
                          unsigned int value);

typedef struct Owner {
    unsigned char _000[0x58];
    int resource;                    /* 0x058 */
} Owner;

/* The block the model routines are handed, at actor+0x2c. */
typedef struct ModelBlock {
    unsigned char _000[0x0c];
} ModelBlock;

/* The block the animation routines are handed, at actor+0x3c. */
typedef struct AnimBlock {
    unsigned short flags;            /* 0x000 */
    unsigned char _002[0x7a];
} AnimBlock;

typedef struct Actor {
    unsigned char _000[8];
    Owner *owner;                    /* 0x008 */
    unsigned char _00c[4];
    unsigned char slot;              /* 0x010 */
    unsigned char _011;
    unsigned short flags;            /* 0x012 */
    unsigned short selector;         /* 0x014 */
    unsigned char count;             /* 0x016 */
    unsigned char _017;
    unsigned short animation;        /* 0x018 */
    unsigned char _01a[0x12];
    ModelBlock model;                /* 0x02c */
    int drawFlags;                   /* 0x038 */
    AnimBlock anim;                  /* 0x03c */
    unsigned short animId;           /* 0x0b8 */
    unsigned char _0ba[0x7a];
    unsigned char phase;             /* 0x134 */
    unsigned char step;              /* 0x135 */
    unsigned char _136[0x7b];
    unsigned char state;             /* 0x1b1 */
    unsigned char _1b2;
    unsigned char pose;              /* 0x1b3 */
    unsigned char _1b4[0x18];
    int progress;                    /* 0x1cc */
    short soundId;                   /* 0x1d0 */
} Actor;

void func_ov014_020801d0(Actor *self)
{
    unsigned int r;

    func_ov002_020767ec(self);
    r = func_020235d0(self->selector, self->count);
    func_020235e8(self->selector, self->count,
                  ((r & 0xffff0001) | 2) & 0xffff);
    self->flags &= ~8;
    self->step = 1;
    self->phase = 3;
}
