/*
 * Pltt_Upload - flush a palette resource and load it into the requested GX
 * palette memory, then record what was uploaded into a 2-word output header.
 *
 * desc holds the resource: pData/dwSize is the palette blob, dwUseExt selects
 * the extended-palette path, dwHandle is an opaque id copied to the output.
 * `slot` picks the destination family: 0 = texture palette, 1 = main-screen OBJ
 * palette, 2 = sub-screen (GXS) OBJ palette. For the OBJ families, dwUseExt
 * chooses between the plain OBJ palette slot and the begin/load/end extended
 * palette sequence. `addr` is the VRAM offset passed to every loader. Finally
 * the resource's handle and useExt flag are written to out[0]/out[1] and
 * func_02011f88 is notified (out, slot, addr).
 *
 * Codegen: the dispatch is a `switch (slot)` (case labels 0/1/2 give the
 * cmp/beq chain) with the case blocks ordered 1,2,0 in source so mwcc lays them
 * out to match the ROM; inside cases 1/2 the `dwUseExt != 0` test is written
 * ext-first so the extended-palette block falls through (beq to the plain slot).
 */

typedef struct PlttUpload {
    unsigned int dwHandle;   /* +0x00 opaque id, copied to out[0] */
    unsigned int dwUseExt;   /* +0x04 nonzero => extended-palette path */
    unsigned int dwSize;     /* +0x08 blob size in bytes */
    void *pData;             /* +0x0c palette blob */
} PlttUpload;

extern void DC_FlushRange(const void *addr, unsigned int size);
extern void GX_BeginLoadTexPltt(void);
extern void GX_LoadTexPltt(const void *src, unsigned int addr, unsigned int size);
extern void GX_EndLoadTexPltt(void);
extern void GX_LoadOBJPltt(const void *src, unsigned int offset, unsigned int size);
extern void GX_BeginLoadOBJExtPltt_0x02007b64(void);
extern void GX_LoadOBJExtPltt(const void *src, unsigned int offset, unsigned int size);
extern void GX_EndLoadOBJExtPltt(void);
extern void GXS_LoadOBJPltt(const void *src, unsigned int offset, unsigned int size);
extern void GXS_BeginLoadOBJExtPltt(void);
extern void GXS_LoadOBJExtPltt(const void *src, unsigned int offset, unsigned int size);
extern void GXS_EndLoadOBJExtPltt(void);
extern void func_02011f88(int *a, int i, int v);

void func_020121c0(PlttUpload *desc, int addr, int slot, int *out)
{
    void *data = desc->pData;
    unsigned int size = desc->dwSize;

    DC_FlushRange(data, size);
    switch (slot) {
    case 1:
        if (desc->dwUseExt != 0) {
            GX_BeginLoadOBJExtPltt_0x02007b64();
            GX_LoadOBJExtPltt(data, addr, size);
            GX_EndLoadOBJExtPltt();
        } else {
            GX_LoadOBJPltt(data, addr, size);
        }
        break;
    case 2:
        if (desc->dwUseExt != 0) {
            GXS_BeginLoadOBJExtPltt();
            GXS_LoadOBJExtPltt(data, addr, size);
            GXS_EndLoadOBJExtPltt();
        } else {
            GXS_LoadOBJPltt(data, addr, size);
        }
        break;
    case 0:
        GX_BeginLoadTexPltt();
        GX_LoadTexPltt(data, addr, size);
        GX_EndLoadTexPltt();
        break;
    }
    out[0] = desc->dwHandle;
    out[1] = desc->dwUseExt;
    func_02011f88(out, slot, addr);
}
