/* func_ov008_0207ba68 -- arm a cursor-move request on the menu.
 * Reads the cursor row (0 while the scene is locked out at obj+0x4e8), then fills the
 * request slot for that row: obj+0x4ac is the "row 0 / home" slot and obj+0x4e0 the slot
 * for every other row. The request carries the target id, kind and one flag bit.
 *
 * PROVENANCE: byte-identical twin of func_ov006_0204fcd8 -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern int func_02030788(void);
extern int data_ov008_02090f24;

#define OBJ (*(int **)&data_ov008_02090f24)

struct Ov006CursorReq {
    unsigned short id;
    unsigned char pad2;
    unsigned char flag;
    signed char kind;
};

struct Ov006CursorSlot {
    unsigned char row;
    unsigned char active : 1;
    unsigned char alt : 1;
    unsigned char pad : 6;
    signed char kind;
    unsigned char pad3;
    unsigned short id;
};

void func_ov008_0207ba68(struct Ov006CursorReq *req) {
    unsigned int raw;
    unsigned int row;
    struct Ov006CursorSlot *dst;

    if (OBJ[0x13a] != 0) {
        raw = 0;
    } else {
        raw = func_02030788();
    }
    row = (raw << 16) >> 16;

    if (row == 0) {
        dst = (struct Ov006CursorSlot *)((char *)OBJ + 0x4ac);
    } else {
        dst = (struct Ov006CursorSlot *)((char *)OBJ + 0x4e0);
    }

    dst->row = (unsigned char)row;
    dst->active = 1;
    dst->kind = req->kind;
    dst->alt = req->flag;
    dst->id = req->id;
}
