#pragma thumb on
/* MsgDb_LoadRecord15 -- load one entry of message db 0x15 into a fresh object, MAIN (THUMB). Needs db
 * 0x15 open (MsgDb_IsLoaded); with keep >= 0 the output slot must be empty. The 1-based id selects a
 * 0x64-byte record of the db's record block; a 0x9c-byte object is allocated into *out
 * (MsgDb_AllocRecord), its two strings are fetched (MsgDb_FetchStringPair; on failure the object is
 * released again) and every record field is copied into the object, widening bytes and halfwords
 * to the object's field sizes. Returns 1 on success, 0 otherwise. */

#include "nitro/types.h"

typedef struct DbRecord {
    u16 a0;                             /* +0x00 */
    u16 a2;                             /* +0x02 */
    u16 nIconId;                        /* +0x04: the panel's picture + 1 (ui/pnl/3d_&.pak.z, the shop's 2D sheet) */
    s16 a6;                             /* +0x06 */
    s8 b8;                              /* +0x08 */
    u8 b9;                              /* +0x09 */
    u8 ba;                              /* +0x0a */
    u8 bb;                              /* +0x0b */
    s8 bc;                              /* +0x0c */
    s8 bd;                              /* +0x0d */
    s8 be;                              /* +0x0e */
    s8 bf;                              /* +0x0f */
    int x10;                            /* +0x10 */
    int x14;                            /* +0x14 */
    u8 b18[12];                         /* +0x18 */
    int x24[14];                        /* +0x24 */
    u16 h5c;                            /* +0x5c */
    u16 h5e;                            /* +0x5e */
    u16 h60;                            /* +0x60 */
    u16 h62;                            /* +0x62 */
} DbRecord;

typedef struct DbEntry {
    u32 pad00;
    u32 *strings;                       /* +0x04 */
    DbRecord *records;                  /* +0x08 */
    u16 count;                          /* +0x0c */
    u16 pad0e;
    u32 pad10;
} DbEntry;

typedef struct DbObject {
    s16 id;                             /* +0x00 */
    s16 pad02;
    u16 *textA;                         /* +0x04 */
    u16 *textB;                         /* +0x08 */
    u16 *ptrA;                          /* +0x0c */
    u16 *ptrB;                          /* +0x10 */
    int index;                          /* +0x14 */
    int a0;                             /* +0x18 */
    int a2;                             /* +0x1c */
    u16 nIconId;                        /* +0x20: the record's +0x04, 1-based */
    s16 a6;                             /* +0x22 */
    int b8;                             /* +0x24 */
    u8 b9;                              /* +0x28 */
    u8 ba;                              /* +0x29 */
    u8 bb;                              /* +0x2a */
    s8 bc;                              /* +0x2b */
    s8 bd;                              /* +0x2c */
    s8 be;                              /* +0x2d */
    s8 bf;                              /* +0x2e */
    u8 x14;                             /* +0x2f */
    int x10;                            /* +0x30 */
    int b18;                            /* +0x34 */
    u16 b19;                            /* +0x38 */
    u16 b1a;                            /* +0x3a */
    int b1b;                            /* +0x3c */
    u16 b1c;                            /* +0x40 */
    u16 b1d;                            /* +0x42 */
    int b1e;                            /* +0x44 */
    u16 b1f;                            /* +0x48 */
    u16 b20;                            /* +0x4a */
    int b21;                            /* +0x4c */
    u16 b22;                            /* +0x50 */
    u16 b23;                            /* +0x52 */
    int x24[13];                        /* +0x54 */
    int x58;                            /* +0x88 */
    u16 h5c;                            /* +0x8c */
    u16 h5e;                            /* +0x8e */
    u16 h60;                            /* +0x90 */
    u16 h62;                            /* +0x92 */
    u32 cntA;                           /* +0x94 */
    u32 cntB;                           /* +0x98 */
} DbObject;

extern DbEntry *data_0204c238;

extern int MsgDb_IsLoaded(int db);                                        /* db open? */
extern int MsgDb_AllocRecord(DbObject **out, int size, int db, int keep);   /* allocate */
extern int MsgDb_FetchStringPair(DbObject *rec, u16 **ptrA, u16 **ptrB, u32 *cntA, u32 *cntB, int db, int index,
                         int keep);                                     /* MsgDb_FetchStringPair */
extern void DispatchByNodeKind(DbObject **obj);                              /* release */

int MsgDb_LoadRecord15(DbObject **out, int id, int keep)
{
    int index = id - 1;
    DbRecord *rec;

    if (MsgDb_IsLoaded(0x15) == 0 || (keep >= 0 && *out != 0)) {
        return 0;
    }
    if (index >= 0 && index < data_0204c238[0x15].count) {
        rec = &data_0204c238[0x15].records[index];
        if (MsgDb_AllocRecord(out, 0x9c, 0x15, keep) == 0 || *out == 0) {
            return 0;
        }
        if (MsgDb_FetchStringPair(*out, &(*out)->ptrA, &(*out)->ptrB, &(*out)->cntA, &(*out)->cntB, 0x15, index, keep) == 0) {
            DispatchByNodeKind(out);
            return 0;
        }
        (*out)->index = id;
        (*out)->a0 = rec->a0;
        (*out)->a2 = rec->a2;
        (*out)->nIconId = rec->nIconId;
        (*out)->a6 = rec->a6;
        (*out)->bb = rec->bb;
        (*out)->bc = rec->bc;
        (*out)->bd = rec->bd;
        (*out)->be = rec->be;
        (*out)->bf = rec->bf;
        (*out)->x10 = rec->x10;
        (*out)->x14 = rec->x14;
        (*out)->b18 = rec->b18[0];
        (*out)->b19 = rec->b18[1];
        (*out)->b1a = rec->b18[2];
        (*out)->b1b = rec->b18[3];
        (*out)->b1c = rec->b18[4];
        (*out)->b1d = rec->b18[5];
        (*out)->b1e = rec->b18[6];
        (*out)->b1f = rec->b18[7];
        (*out)->b20 = rec->b18[8];
        (*out)->b21 = rec->b18[9];
        (*out)->b22 = rec->b18[10];
        (*out)->b23 = rec->b18[11];
        (*out)->x24[0] = rec->x24[0];
        (*out)->x24[1] = rec->x24[1];
        (*out)->x24[2] = rec->x24[2];
        (*out)->x24[3] = rec->x24[3];
        (*out)->x24[4] = rec->x24[4];
        (*out)->x24[5] = rec->x24[5];
        (*out)->x24[6] = rec->x24[6];
        (*out)->x24[7] = rec->x24[7];
        (*out)->x24[8] = rec->x24[8];
        (*out)->x24[9] = rec->x24[9];
        (*out)->x24[10] = rec->x24[10];
        (*out)->x24[11] = rec->x24[11];
        (*out)->x24[12] = rec->x24[12];
        (*out)->b8 = rec->b8;
        (*out)->b9 = rec->b9;
        (*out)->ba = rec->ba;
        (*out)->x58 = rec->x24[13];
        (*out)->h5c = rec->h5c;
        (*out)->h5e = rec->h5e;
        (*out)->h60 = rec->h60;
        (*out)->h62 = rec->h62;
        return 1;
    }
    return 0;
}
#pragma thumb off
