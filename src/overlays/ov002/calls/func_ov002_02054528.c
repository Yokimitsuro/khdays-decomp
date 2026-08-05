/*
 * func_ov002_02054528 - allocate and initialise a record from a template (ARM).
 *
 * Allocates a new record via func_ov002_02053f4c(param_1), then fills it: the type word from `type`,
 * seven template fields copied from `tpl` (a/b/e/f signed, c/d unsigned halfwords, extra word), the
 * payload pointer from `payload`, and the active flag set to 1.
 */
typedef struct {
    short type;            /* +0x00 */
    short a, b;            /* +0x02, +0x04 */
    unsigned short c, d;   /* +0x06, +0x08 */
    short e, f;            /* +0x0a, +0x0c */
    char _e[0x10 - 0xe];
    int payload;           /* +0x10 */
    int active;            /* +0x14 */
    int extra;             /* +0x18 */
} Ov002Rec;

extern int func_ov002_02053f4c(int param_1);

void func_ov002_02054528(int param_1, Ov002Rec *tpl, int type, int payload)
{
    Ov002Rec *o = (Ov002Rec *)func_ov002_02053f4c(param_1);
    o->type = type;
    o->a = tpl->a;
    o->b = tpl->b;
    o->c = tpl->c;
    o->d = tpl->d;
    o->e = tpl->e;
    o->f = tpl->f;
    o->payload = payload;
    o->extra = tpl->extra;
    o->active = 1;
}
