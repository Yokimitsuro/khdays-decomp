struct Obj {
    unsigned short a;   /* 0x00 */
    unsigned short b;   /* 0x02 */
    int size;           /* 0x04 */
    int c;              /* 0x08 */
    int d;              /* 0x0c */
};

struct Header {
    struct Obj *obj;    /* 0x00 */
    char *end;          /* 0x04 */
};

struct Obj *InitMBlock(struct Header *h, unsigned short val) {
    struct Obj *o = h->obj;
    o->a = val;
    o->b = 0;
    o->size = (int)(h->end - (char *)((char *)o + 0x10));
    o->c = 0;
    o->d = 0;
    return o;
}
