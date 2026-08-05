/*
 * func_ov002_0205bfa8 - refresh a 4-entry table of active elements (ARM).
 *
 * Walks the four stride-0x10 records starting at data_ov002_0207f620 + 0x440; for each record whose
 * type word is 3, recomputes its cached value by calling func_ov002_0205a598(0, record->arg).
 */
typedef struct {
    unsigned short type;    /* +0x00 */
    char _2[6];
    int cached;             /* +0x08 */
    unsigned short arg;     /* +0x0c */
} Ov002RefreshElem;

extern int data_ov002_0207f620;
extern int func_ov002_0205a598(int a, int b);

void func_ov002_0205bfa8(void)
{
    int base = *(int *)&data_ov002_0207f620;
    int i;
    Ov002RefreshElem *e = (Ov002RefreshElem *)(base + 0x440);
    for (i = 0; i < 4; i++) {
        if (e->type == 3) {
            e->cached = func_ov002_0205a598(0, e->arg);
        }
        e = (Ov002RefreshElem *)((char *)e + 0x10);
    }
}
