/*
 * Ov008_Menu_SetupSprites - reset and register the menu's sprite/OAM cells.
 *
 * Called when the main menu switches to page/mode `id`. First it resets and
 * zero-clears the manager's two adjacent OAM cell buffers (bufA at +0x54 and
 * bufB at +0x4a8c, each 0x4a38 bytes). Then, depending on the page, it registers
 * OAM cells (Oam_SetCell) and commits them (Oam_CommitCell) using cell handles
 * built from the manager's source offsets:
 *
 *     handle = (((src + 0x8000) & 0x00fffffc) << 7) | 0x80000000 | slot
 *
 * where bit31 marks the handle valid and the low bits select the OAM slot.
 * Oam_CommitCell takes the handle both as its gate (skipped when zero) and as
 * its second argument. Pages 8, 9, 12 and anything above 14 set up nothing.
 */

typedef struct {
    int cellSrc0;                /* 0x00 source offset for the primary cell */
    int cellSrc1;                /* 0x04 source offset for the committed cell */
    unsigned char pad[0x4c];     /* 0x08 */
    unsigned char bufA[0x4a38];  /* 0x54  first OAM cell buffer */
    unsigned char bufB[0x4a38];  /* 0x4a8c second OAM cell buffer */
} SpriteMgr;

typedef struct {
    unsigned int handle;         /* 0x00 valid-tagged cell handle */
    int count;                   /* 0x04 number of cells */
    int f8;                      /* 0x08 */
    int fc;                      /* 0x0c */
} OamReq;

extern SpriteMgr *data_ov006_02056664;
extern void func_02032428(void *region);
extern void MI_CpuFill8(void *dest, int val, int size);
extern void func_02032388(void *region, OamReq *req, int z);
extern void func_0203243c(void *region, unsigned int handle);

void func_ov006_020538a4(int id)
{
    OamReq req;
    unsigned int h;

    func_02032428(data_ov006_02056664->bufA);
    func_02032428(data_ov006_02056664->bufB);
    MI_CpuFill8(data_ov006_02056664->bufA, 0, 0x4a38);
    MI_CpuFill8(data_ov006_02056664->bufB, 0, 0x4a38);

    switch (id) {
    case 0: case 1: case 2: case 3: case 10: case 11:
        req.handle = (((data_ov006_02056664->cellSrc0 + 0x8000) & 0x00fffffc) << 7) | 0x80000001;
        req.count = 2; req.f8 = 0; req.fc = 0;
        func_02032388(data_ov006_02056664->bufB, &req, 0);
        h = (((data_ov006_02056664->cellSrc1 + 0x8000) & 0x00fffffc) << 7) | 0x80000000;
        if (h != 0) func_0203243c(data_ov006_02056664->bufB, h);
        break;
    case 13: case 14:
        req.handle = (((data_ov006_02056664->cellSrc0 + 0x8000) & 0x00fffffc) << 7) | 0x80000002;
        req.count = 2; req.f8 = 0; req.fc = 0;
        func_02032388(data_ov006_02056664->bufB, &req, 0);
        break;
    case 4: case 5: case 6: case 7:
        req.handle = (((data_ov006_02056664->cellSrc0 + 0x8000) & 0x00fffffc) << 7) | 0x80000003;
        req.count = 1; req.f8 = 0; req.fc = 0;
        func_02032388(data_ov006_02056664->bufA, &req, 0);
        h = (((data_ov006_02056664->cellSrc1 + 0x8000) & 0x00fffffc) << 7) | 0x80000002;
        if (h != 0) func_0203243c(data_ov006_02056664->bufA, h);
        req.handle = (((data_ov006_02056664->cellSrc0 + 0x8000) & 0x00fffffc) << 7) | 0x80000002;
        req.count = 2; req.f8 = 0; req.fc = 0;
        func_02032388(data_ov006_02056664->bufB, &req, 0);
        h = (((data_ov006_02056664->cellSrc1 + 0x8000) & 0x00fffffc) << 7) | 0x80000001;
        if (h != 0) func_0203243c(data_ov006_02056664->bufB, h);
        break;
    }
}
