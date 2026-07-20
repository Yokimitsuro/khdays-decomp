/* Populates the scene's 28-row list: loads its two resources, then fills each row.
 *
 * Same 0xd18c scene context as Ov000_InitSceneSurfaces -- +0x88 is the shared variant object fed
 * to func_ov000_02056970, and the rows sit at +0x9670 (stride 0x18), directly before the transfer
 * staging region. Each row caches two resolved variants (item i+1 and i+29, i.e. two parallel
 * banks of 28) and one u16 value pulled in order from the first loaded resource.
 *
 * The resource addresses are computed, not stored: ((base + 0x8000) & 0xfffffc) << 7 aligns the
 * base to a 4-byte boundary and shifts it into the high field, then | 0x8000000{7,8} tags which of
 * two adjacent sub-resources to load. The first (tag 7) is a scratch u16 table freed at the end;
 * the second (tag 8) is kept as the per-row resource handle.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    void *pVariantA; /* +0x00  item i+1  */
    void *pVariantB; /* +0x04  item i+29 */
    u32 nValue;      /* +0x08 */
    u8 slot[0x0c];   /* +0x0c */
} Ov000Row;

typedef struct {
    u8 pad_0000[0x84];
    u32 nResourceBase;         /* +0x84 */
    u8 variant_object[0x95e8]; /* +0x88 shared variant object */
    Ov000Row rows[28];         /* +0x9670 stride 0x18 */
    u8 pad_9910[0x3800];
    void *pRowResource;        /* +0xd110 */
} Ov000SceneContext;

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void *func_0201ef9c(u32 address, int mode);
extern void *func_ov000_02056970(void *object, int variant);
extern void func_02024c94(void *slot, void *resource, int first, int second,
                          int third);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void func_ov000_02059130(void) {
    Ov000SceneContext *context = NNSi_FndGetCurrentRootHeap();
    Ov000Row *row = context->rows;
    u16 *values = func_0201ef9c(
        (((context->nResourceBase + 0x8000) & 0xfffffc) << 7) | 0x80000007,
        14);
    u16 *next_value = values;
    int i;

    context->pRowResource = func_0201ef9c(
        (((context->nResourceBase + 0x8000) & 0xfffffc) << 7) | 0x80000008,
        14);

    for (i = 0; i < 28; i++, row++) {
        row->pVariantA = func_ov000_02056970(context->variant_object, i + 1);
        row->pVariantB = func_ov000_02056970(context->variant_object, i + 29);
        row->nValue = *next_value++;
        func_02024c94(row->slot, context->pRowResource, i, i, i);
    }

    if (values != 0) {
        NNSi_FndFreeFromDefaultHeap(values);
    }
}
