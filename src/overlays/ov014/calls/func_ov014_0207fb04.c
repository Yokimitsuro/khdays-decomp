extern int func_ov002_0206da70(int);
extern int func_0202b930(void *, int, int, int);
extern unsigned int func_020235d0(int, int);
extern void func_0202bedc(void *, int);

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

extern void func_ov014_0207fa40(Actor *, int);

void func_ov014_0207fb04(Actor *self)
{
    unsigned short flags = self->flags;
    Owner *owner = self->owner;
    flags |= 4;
    self->flags = flags;
    int model = func_ov002_0206da70((int)&owner->resource);
    func_0202b930(&self->model, model, 1, 4);
    unsigned short animation = self->animation;
    if ((self->drawFlags & 0x20) == 0) {
        self->animId = animation;
        self->anim.flags |= 0x20;
    }
    func_ov014_0207fa40(self, self->pose);
    int flag;
    if (func_020235d0(self->selector, self->count) & 1)
        flag = 1;
    else
        flag = 0;
    func_0202bedc(&self->model, flag);
}
