/* Construct one ov016 list entry: allocate 0x2f4 bytes through the ov002 object
 * allocator, copy the caller's name into the 0x10-byte field at +0x58, install
 * the nine handlers, stamp kind 0x13, and carry the descriptor's two parameters
 * across.
 *
 * The size is written 0xbd * 4 because that is how the ROM materialises it --
 * movs #0xbd + lsls #2, the THUMB idiom for a constant that will not fit in an
 * immediate.  Spelling it 0x2f4 gives the same bytes; spelling it as a literal
 * that needs a pool entry does not.
 *
 * The handler stores are written in field order even though the ROM emits +0x34
 * before +0x2c and +0x44 before +0x3c -- that reordering is the scheduler's, and
 * mwcc reproduces it from the natural order. */
typedef struct {
    char *pszName;          /* +0x00 */
    int nParamA;            /* +0x04 */
    int nParamB;            /* +0x08 */
} Ov016EntryDesc;

typedef struct {
    int nField00;           /* +0x00 */
    int nField04;           /* +0x04 */
    void *pfnA;             /* +0x08 */
    void *pfnB;             /* +0x0c */
    void *pfnC;             /* +0x10 */
    void *pfnD;             /* +0x14 */
    void *pfnE;             /* +0x18 */
    void *pfnF;             /* +0x1c */
    int nField20;
    int nField24;
    int nField28;
    void *pfnG;             /* +0x2c */
    char pad30[4];
    void *pfnH;             /* +0x34 */
    int nField38;
    void *pfnI;             /* +0x3c */
    char pad40[4];
    int nField44;
    char pad48[4];
    unsigned short wKind;   /* +0x4c */
    char pad4e[0xa];
    char szName[0x10];      /* +0x58 */
    int nParamA;            /* +0x68 */
    int nParamB;            /* +0x6c */
} Ov016Entry;

extern void *func_ov002_020769b0(int cls, int size, int owner);
extern char *strncpy(char *dst, const char *src, unsigned int n);
extern void func_ov016_0207fa40(void);
extern void func_ov016_0207fa5c(void);
extern void func_ov016_0207fad0(void);
extern void func_ov016_0207fa4c(void);
extern void func_ov016_0207fa68(void);
extern void func_ov016_0207fafc(void);
extern void func_ov016_0207fb20(void);
extern void func_ov016_0207fb18(void);
extern void func_ov016_0207fb28(void);

Ov016Entry *func_ov016_0207feb8(int owner, Ov016EntryDesc *desc) {
    Ov016Entry *self = func_ov002_020769b0(0x70, 0xbd * 4, owner);

    strncpy(self->szName, desc->pszName, 0x10);
    self->nField00 = 0;
    self->nField04 = 0;
    self->pfnA = (void *)&func_ov016_0207fa40;
    self->pfnB = (void *)&func_ov016_0207fa5c;
    self->pfnC = (void *)&func_ov016_0207fad0;
    self->pfnD = (void *)&func_ov016_0207fa4c;
    self->pfnE = (void *)&func_ov016_0207fa68;
    self->pfnF = (void *)&func_ov016_0207fafc;
    self->nField20 = 0;
    self->nField24 = 0;
    self->nField28 = 0;
    self->pfnH = (void *)&func_ov016_0207fb20;
    self->pfnG = (void *)&func_ov016_0207fb18;
    self->nField38 = 0;
    self->nField44 = 0;
    self->pfnI = (void *)&func_ov016_0207fb28;
    self->wKind = 0x13;
    self->nParamA = desc->nParamA;
    self->nParamB = desc->nParamB;
    return self;
}
