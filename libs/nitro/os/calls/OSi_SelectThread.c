struct Thread02001ff0 {
    char _0[0x64];
    int field_64;
    struct Thread02001ff0 *next;
};

struct Globals02001ff0 {
    char _0[0x2c];
    struct Thread02001ff0 *list;
};

extern struct Globals02001ff0 data_0204430c;

void *OSi_SelectThread(void)
{
    struct Thread02001ff0 *t = data_0204430c.list;
    while (t != 0 && t->field_64 != 1)
        t = t->next;
    return t;
}
