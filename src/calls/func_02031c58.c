/*
 * func_02031c58 - load a sprite resource archive for an object and upload its
 * palette. Opens archive `name` (kind 0xe) via Archive_LoadFile, stores it at
 * obj[7], then pulls members by kind: the character/cell block (kind 2 or 1
 * depending on the map-state flag), the CEBK cell bank (kind 3) and the extra
 * bank (kind 5), decoding each sub-block into the object's fields. Computes the
 * span/aligned-end via func_02031bc8/func_02031b50 and advances the map-state
 * VRAM cursor at +0x4610. Finally, if a palette member (kind 0) exists, uploads
 * it with Pltt_Upload: the extended-palette path (dwUseExt) forces a 0x200 size,
 * uploads to slot +0x4616 and bumps the ext counters at +0x4618/+0x4616; the
 * plain path uploads to +0x461c and advances that cursor by the palette size.
 */
#pragma thumb on

typedef struct PlttUpload {
    unsigned int dwHandle;
    unsigned int dwUseExt;
    unsigned int dwSize;
    void *pData;
} PlttUpload;

extern int func_02031b2c(unsigned int mapState);
extern void *func_0201ef9c(char *name, int kind);
extern void func_02025464(void *arc, int kind);
extern int func_020255d4(int arc, int type, int idx);
extern void func_02011988(int member, unsigned short **out);
extern void func_02011f94(unsigned short *hdr, unsigned int a, int mode, int *out);
extern void func_02011888(int member, int *out);
extern void WM_EndKeySharing_0x020116e4(int member, int *out);
extern unsigned int func_02031bc8(unsigned int mapState, int obj);
extern unsigned int func_02031b50(unsigned int mapState, int *obj);
extern void func_02011a20(int member, PlttUpload **out);
extern void func_020121c0(PlttUpload *desc, int addr, int slot, int *out);

void func_02031c58(unsigned int param_1, char *param_2, int *param_3)
{
    void *arc;
    int mode;
    int member;
    unsigned int span;
    unsigned short *charHdr;
    PlttUpload *pltt;

    func_02031b2c(param_1);
    arc = func_0201ef9c(param_2, 0xe);
    param_3[7] = (int)arc;
    func_02025464(arc, 1);
    mode = func_02031b2c(param_1);
    if (mode == 0)
        member = func_020255d4((int)arc, 2, 0);
    else
        member = func_020255d4((int)arc, 1, 0);
    func_02011988(member, &charHdr);
    *param_3 = *(int *)(charHdr + 8);
    param_3[1] = *(int *)(charHdr + 2);
    param_3[2] = *(int *)(charHdr + 4);
    func_02011f94(charHdr, *(unsigned int *)(param_1 + 0x4610), mode, param_3 + 0xd);
    member = func_020255d4((int)arc, 3, 0);
    param_3[5] = member;
    member = func_020255d4((int)arc, 5, 0);
    param_3[6] = member;
    func_02011888(param_3[5], param_3 + 3);
    WM_EndKeySharing_0x020116e4(param_3[6], param_3 + 4);
    span = func_02031bc8(param_1, (int)param_3);
    param_3[0x16] = span;
    span = func_02031b50(param_1, param_3);
    *(unsigned int *)(param_1 + 0x4610) += span;
    *(short *)(param_3 + 0x18) = -1;
    member = func_020255d4((int)arc, 0, 0);
    if (member != 0) {
        func_02011a20(member, &pltt);
        if (pltt->dwUseExt != 0) {
            pltt->dwSize = 0x200;
            func_020121c0(pltt, *(unsigned short *)(param_1 + 0x4616), mode, param_3 + 8);
            *(unsigned short *)(param_3 + 0x18) = *(unsigned short *)(param_1 + 0x4618);
            *(unsigned short *)(param_1 + 0x4618) += 1;
            *(unsigned short *)(param_1 + 0x4616) += 0x200;
            return;
        }
        func_020121c0(pltt, *(unsigned short *)(param_1 + 0x461c), mode, param_3 + 8);
        *(unsigned short *)(param_1 + 0x461c) += pltt->dwSize;
    }
}
