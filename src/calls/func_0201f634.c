/* Acquires a resource slot: with data_020427f0 temporarily set to `withTex`, the first user loads
 * the data (an 'HPAK' pack through func_02025464 with textures, anything else through
 * func_02025138); the use count (+2) grows, and with `withTex` the texture count (+4) too. Returns
 * the resource data (+0xc). Counterpart of func_0201f6b0. */
extern void func_02025464(void *pack, int mode);
extern void func_02025138(void *data);
extern int data_020427f0;

struct S {
    short _0;
    unsigned short x2;
    unsigned short x4;
    char _6[6];
    void *xc;
};

void *func_0201f634(struct S *p, int withTex)
{
    int saved = data_020427f0;

    data_020427f0 = withTex;
    if (p->x2 == 0) {
        if (*(int *)p->xc == 0x4850414B) {
            func_02025464(p->xc, 1);
        } else {
            func_02025138(p->xc);
        }
    }
    p->x2++;
    data_020427f0 = saved;
    if (withTex != 0) {
        p->x4++;
    }
    return p->xc;
}
