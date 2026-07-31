/*
 * Ov002_SelectTableEntry - load a table via Archive_LoadFile, find the entry whose cmpField
 * matches the selector at root-context + 0x8ba8, and copy its payload into the record at
 * ctx + 0x8d84. Part of the ov002 gameplay bootstrap (dep of func_ov002_020679d4).
 *
 * The table is [u32 count][Entry entries[]], each Entry 0x3c bytes. The last entry whose
 * cmpField equals *(short*)(ctx+0x8ba8) wins; its payload0 goes to rec+0x10 (0 if none), and
 * one payload byte (payload2 if data_0204c240 & 4, else payload1) goes to ctx+0x8bae, after
 * which Ov002_StoreRequestPayload runs. The table buffer is freed at the end.
 *
 * THUMB. Modeling the table as a struct with array indexing is what makes mwcc emit the clean
 * strength-reduced pointer walk (inits in the post-guard preheader) instead of a multiply; the
 * payload byte-select uses (flag & 4) != 0 with swapped arms so the beq/fall-through layout
 * matches the original.
 */

typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct {
    short cmpField;   /* +0x00 */
    short pad2;       /* +0x02 */
    u32   payload0;   /* +0x04 */
    u32   payload1;   /* +0x08 */
    u32   payload2;   /* +0x0c */
    u8    rest[0x3c - 0x10];
} Entry;

typedef struct {
    u32   count;
    Entry entries[1];
} Table;

extern Table *func_0201ef9c(void *archive, int mode, int c, int d);
extern void   func_ov002_02074084(int entry);
extern void   NNSi_FndFreeFromDefaultHeap(void *p);
extern int    data_ov002_0207fa00;
extern char   data_ov002_0207f000[];
extern u8     data_0204c240;

void func_ov002_0206e640(int param_1, int param_2, int param_3, int param_4)
{
    Entry *found = 0;
    u32    i;
    char  *rec;
    Table *hdr;
    char  *ctx;

    ctx = (char *)data_ov002_0207fa00;
    rec = ctx + 0x8d84;
    hdr = func_0201ef9c(data_ov002_0207f000, 2, param_3, param_4);
    for (i = 0; i < hdr->count; i++) {
        if (*(short *)(ctx + 0x8ba8) == hdr->entries[i].cmpField)
            found = &hdr->entries[i];
    }
    *(int *)(rec + 0x10) = 0;
    if (found != 0) {
        u32 val;
        *(u32 *)(rec + 0x10) = found->payload0;
        if ((data_0204c240 & 4) != 0)
            val = found->payload2;
        else
            val = found->payload1;
        *(char *)(ctx + 0x8bae) = val;
        func_ov002_02074084((int)found);
    }
    NNSi_FndFreeFromDefaultHeap(hdr);
}
