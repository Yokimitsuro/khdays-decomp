extern int func_020235d0(int, int);
extern int func_ov002_020766e0(void *, unsigned char *, int);

typedef struct {
    unsigned char _0[0x80];
    unsigned char value;
} Owner;

typedef struct {
    unsigned char _0[8];
    Owner *owner;
    unsigned char _c[8];
    unsigned short selector;
    unsigned char count;
    unsigned char _17[0x19a];
    unsigned char flags;
    unsigned char _1b2[0x12];
    int total;
} Actor;

typedef struct {
    unsigned char _0[0xc];
    unsigned char value;
    unsigned char _d[7];
    int bits;
} Input;

int func_ov014_0207fbf0(Actor *actor, Input *input)
{
    unsigned char record[12];
    unsigned int r;
    Owner *owner = actor->owner;

    r = func_020235d0(actor->selector, actor->count);
    r = ((r & 0xfffe) << 0xf) >> 0x10;
    if ((r & 1) == 0)
        return 8;
    if ((actor->flags & 1) != 0 || actor->total != 0)
        goto fail;
    {
        record[0] = 1;
        record[8] = input->value;
        record[9] = (input->bits & 0x20) != 0;
        *(unsigned int *)(record + 4) = (unsigned int)owner->value << 12;
        if (func_ov002_020766e0(actor, record, 12) == 0)
            goto fail;
        actor->flags |= 1;
        return 0;
    }

fail:
    return 8;
}
