#pragma thumb on
/* MsgDb record builder for a plain entry table: take entry `index` (stride 0xc) of table `db`
 * (data_0204c238 tables, stride 0x14: entries +0x8, count +0xc), allocate a 0x24-byte record of
 * kind `db` and copy the entry's id, its flag bit (+6), mode (+2) and extra byte (+4) and its data
 * pointer (+8). A plain entry (mode 0) clears the four extracted-string slots; otherwise the
 * strings are extracted (func_02034fc4) and a failure frees the record again. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 id;                             /* +0x00 */
    u16 mode;                           /* +0x02 */
    u16 extra;                          /* +0x04 */
    u16 flag;                           /* +0x06 */
    int data;                           /* +0x08 */
} MsgEntry;

typedef struct {
    int pad00[2];
    MsgEntry *entries;                  /* +0x08 */
    u16 count;                          /* +0x0c */
    u16 pad0e;
    int pad10;
} MsgTable;

typedef struct {
    short keepFlag;                     /* +0x00 */
    short kind;                         /* +0x02 */
    int field_04;
    int field_08;
    u16 id;                             /* +0x0c */
    u8 flag : 1;                        /* +0x0e */
    u8 mode : 7;
    u8 extra;                           /* +0x0f */
    int data;                           /* +0x10 */
    int text0;                          /* +0x14 */
    int text1;                          /* +0x18 */
    int text2;                          /* +0x1c */
    int text3;                          /* +0x20 */
} Rec24;

extern int func_020342b4(int db);
extern int func_02034428(int *rec_out, unsigned int size, int kind, int keep);
extern int func_02034fc4(Rec24 *rec, int *text0, int *text1, int *text2, int *text3, int db, int data,
                         int keep);
extern void func_020343cc(int *rec_out);
extern MsgTable *data_0204c238;

int func_02034d40(int *rec_out, int index, int keep, int db)
{
    MsgEntry *entry;

    if (func_020342b4(db) == 0 || (keep >= 0 && *rec_out != 0)) {
        return 0;
    }
    if (index >= 0) {
        if (index < data_0204c238[db].count) {
            entry = &data_0204c238[db].entries[index];
            if (func_02034428(rec_out, 0x24, db, keep) == 0 || *rec_out == 0) {
                return 0;
            }
            ((Rec24 *)*rec_out)->id = entry->id;
            ((Rec24 *)*rec_out)->flag = (u8)entry->flag;
            ((Rec24 *)*rec_out)->mode = (u8)entry->mode;
            ((Rec24 *)*rec_out)->extra = entry->extra;
            if (entry->mode == 0) {
                ((Rec24 *)*rec_out)->data = entry->data;
                ((Rec24 *)*rec_out)->text0 = 0;
                ((Rec24 *)*rec_out)->text1 = 0;
                ((Rec24 *)*rec_out)->text2 = 0;
                ((Rec24 *)*rec_out)->text3 = 0;
            } else {
                ((Rec24 *)*rec_out)->data = entry->data;
                if (func_02034fc4((Rec24 *)*rec_out, &((Rec24 *)*rec_out)->text0, &((Rec24 *)*rec_out)->text1,
                                  &((Rec24 *)*rec_out)->text2, &((Rec24 *)*rec_out)->text3, db, entry->data,
                                  keep) == 0) {
                    func_020343cc(rec_out);
                    return 0;
                }
            }
            return 1;
        }
    }
    return 0;
}
