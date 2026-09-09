extern int func_ov002_0207285c(int slot);
extern void func_0202ba9c(void *dst, int id, int a, void *b);
extern int func_ov002_02074460(int id);
extern void func_ov002_02073ed0(int id, int a, int b);

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

void func_ov014_0207fb88(Actor *self)
{
    func_0202ba9c(&self->model,
                  (unsigned short)func_ov002_0207285c(self->slot),
                  0, 0);
    if (self->state & 0x80) {
        return;
    }
    if (self->soundId < 0) {
        return;
    }
    if (func_ov002_02074460(self->soundId) < 0) {
        return;
    }
    func_ov002_02073ed0(self->soundId, 0, -1);
}
