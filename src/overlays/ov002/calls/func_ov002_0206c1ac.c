typedef unsigned char u8;
typedef unsigned short u16;

/* One seat row of the session board, as the readers at 0206bdcc see it. */
typedef struct Ov002SeatRow {
    int nHandle;
    int nUnk04;
    int aValues[9];
} Ov002SeatRow;

typedef struct Ov002SeatTable {
    Ov002SeatRow aRows[4];
    char pad0b0[8];
    u8 bFlags;                  /* bit 4 says the rows were filled locally */
} Ov002SeatTable;

/* Four halfwords per seat, as they arrive from the caller. */
typedef struct Ov002SeatSourceRow {
    u16 aw[4];
} Ov002SeatSourceRow;

extern char *data_ov002_0207fa00;

/* Non-zero once the link session is up and feeding the board itself. */
extern int func_02030694(void);

/* Fill the session board's seat rows from a local table.  With the link
   session up the board is already being fed from the wire, so only the
   "filled" flag is raised; otherwise each seat takes its own values from the
   caller's table.  The inner run writes three values from the tail of each
   row, which is one past the row proper and so carries into the next one --
   that is what the game does. */
void func_ov002_0206c1ac(Ov002SeatSourceRow *pSource)
{
    Ov002SeatTable *pTable;
    Ov002SeatRow *pRow;
    int i;
    int j;

    pTable = (Ov002SeatTable *)(data_ov002_0207fa00 + 0x8bcc);
    if (func_02030694() == 0) {
        for (i = 0; i < 4; i++) {
            pRow = &pTable->aRows[i];
            pRow->aValues[6] = 0;
            pRow->aValues[7] = pSource[i].aw[1];
            for (j = 0; j < 3; j++) {
                (&pRow->aValues[8])[j] = pSource[i].aw[j + 2];
            }
        }
    }
    pTable->bFlags |= 0x10;
}
