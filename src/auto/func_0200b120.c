typedef struct {
    int field0;
    int field1;
    int ptr_val;
    int pad3;
    int pad4;
    int pad5;
    int pad6;
    union {
        unsigned int word;
        struct {
            unsigned int lo : 24;
            unsigned int flag : 1;
            unsigned int hi : 7;
        } b;
    } u;
} Obj;

int func_0200b120(Obj *p)
{
    unsigned int v = p->u.word;
    if ((v >> 24) & 1)
        return p->u.b.lo;
    return p->ptr_val;
}
