extern void NNS_FndInitList(void *list, unsigned int offsetOfLink);
extern void func_0201ae50(void);
extern void func_0201ae9c(void);
extern int data_0204abe0;
extern char data_0204abe4[];

typedef struct {
    char _0[8];
    void (*fn8)(void);   /* 0x08 */
    void *self_c;        /* 0x0c */
    char _10[4];
    void (*fn14)(void);  /* 0x14 */
    void *self_18;       /* 0x18 */
    char _1c[8];
    unsigned int flags24;/* 0x24 */
    char _28[0x1c];
    int x44;             /* 0x44 */
    int x48;             /* 0x48 */
} X0201a940;

void func_0201a940(X0201a940 *p)
{
    if (data_0204abe0 == 0) {
        NNS_FndInitList(data_0204abe4, 0);
        data_0204abe0 = 1;
    }
    p->fn8 = func_0201ae50;
    p->self_c = p;
    p->fn14 = func_0201ae9c;
    p->self_18 = p;
    p->x44 = 0;
    p->x48 = 0;
    p->flags24 &= ~(unsigned int)1;
    p->flags24 &= ~(unsigned int)2;
}
