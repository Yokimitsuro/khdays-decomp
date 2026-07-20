/* Construct an ov016 list entry of CLASS 0x80: allocate 0x658 bytes through the
 * ov002 object allocator, copy the descriptor's name into the 0x10-byte field at
 * +0x58, carry its five parameters across, install thirteen handlers and stamp
 * kind 2.
 *
 * Sibling of Ov016_CreateEntry (func_ov016_0207feb8), which is the same shape for
 * CLASS 0x70: 0x2f4 bytes, nine handlers, kind 0x13. The two differ in class id,
 * size, handler set and kind stamp, so they are distinct object kinds rather than
 * one routine called twice -- hence the class in the name.
 *
 * This closes a pair: its parameter block is exactly the Ov016EmitParams that
 * the script-VM handler func_ov016_02081360 assembles, which is what confirms
 * that handler's stack block is an entry descriptor and not an ad-hoc argument
 * bundle.
 */
typedef struct {
    char *pszName;           /* +0x00 */
    int nParamA;             /* +0x04 */
    signed char cKind;       /* +0x08 */
    char pad09[3];
    int nParamB;             /* +0x0c */
    int nParamC;             /* +0x10 */
    int nParamD;             /* +0x14 */
    unsigned char bParamE;   /* +0x18 */
    char pad19[3];
} Ov016EmitParams;           /* 0x1c */

typedef struct {
    int nField00;            /* +0x00 */
    int nField04;            /* +0x04 */
    void *pfn08;             /* +0x08 */
    void *pfn0c;             /* +0x0c */
    void *pfn10;             /* +0x10 */
    void *pfn14;             /* +0x14 */
    void *pfn18;             /* +0x18 */
    void *pfn1c;             /* +0x1c */
    int nField20;            /* +0x20 */
    void *pfn24;             /* +0x24 */
    void *pfn28;             /* +0x28 */
    void *pfn2c;             /* +0x2c */
    char pad30[4];
    void *pfn34;             /* +0x34 */
    void *pfn38;             /* +0x38 */
    void *pfn3c;             /* +0x3c */
    char pad40[4];
    void *pfn44;             /* +0x44 */
    char pad48[4];
    unsigned short wKind;    /* +0x4c */
    char pad4e[0xa];
    char szName[0x10];       /* +0x58 */
    int nParamA;             /* +0x68 */
    signed char cKind;       /* +0x6c */
    char pad6d[3];
    int nParamB;             /* +0x70 */
    int nParamC;             /* +0x74 */
    int nParamD;             /* +0x78 */
    unsigned char bParamE;   /* +0x7c */
    char pad7d[3];
} Ov016Entry;

extern void *func_ov002_020769b0(int cls, int size, int owner);
extern char *strncpy(char *dst, const char *src, unsigned int n);
extern void func_ov016_02081670(void);
extern void func_ov016_020819c4(void);
extern void func_ov016_02081a78(void);
extern void func_ov016_020819a8(void);
extern void func_ov016_020819e0(void);
extern void func_ov016_02081b00(void);
extern void func_ov016_02081c34(void);
extern void func_ov016_02081cc8(void);
extern void func_ov016_02081d14(void);
extern void func_ov016_02081830(void);
extern void func_ov016_020818dc(void);
extern void func_ov016_02081af0(void);
extern void func_ov016_02081d20(void);

Ov016Entry *func_ov016_02081f64(int owner, Ov016EmitParams *desc) {
    Ov016Entry *self = func_ov002_020769b0(0x80, 0x658, owner);

    strncpy(self->szName, desc->pszName, 0x10);
    self->nParamA = desc->nParamA;
    self->cKind = desc->cKind;
    self->nParamB = desc->nParamB;
    self->nParamC = desc->nParamC;
    self->nParamD = desc->nParamD;
    self->bParamE = desc->bParamE;
    self->nField00 = 0;
    self->nField04 = 0;
    self->pfn08 = (void *)&func_ov016_02081670;
    self->pfn0c = (void *)&func_ov016_020819c4;
    self->pfn10 = (void *)&func_ov016_02081a78;
    self->pfn14 = (void *)&func_ov016_020819a8;
    self->pfn18 = (void *)&func_ov016_020819e0;
    self->pfn1c = (void *)&func_ov016_02081b00;
    self->nField20 = 0;
    self->pfn24 = (void *)&func_ov016_02081c34;
    self->pfn28 = (void *)&func_ov016_02081cc8;
    self->pfn2c = (void *)&func_ov016_02081d14;
    self->pfn38 = (void *)&func_ov016_02081830;
    self->pfn44 = (void *)&func_ov016_020818dc;
    self->pfn3c = (void *)&func_ov016_02081af0;
    self->pfn34 = (void *)&func_ov016_02081d20;
    self->wKind = 2;
    return self;
}
