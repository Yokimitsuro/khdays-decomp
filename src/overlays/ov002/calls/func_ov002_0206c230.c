typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov002SeatRow {
    char pad0000[0x28];
    unsigned int nPeerValue;        /* +0x28, last word of the row */
} Ov002SeatRow;                     /* 0x2c */

typedef struct Ov002RosterBlock {
    Ov002SeatRow aSeats[4];         /* +0x00 */
    char pad00b0[8];
    u8 bSeatMask;                   /* +0xb8 */
} Ov002RosterBlock;

typedef struct Ov002RootContext {
    char pad0000[0x8bcc];
    Ov002RosterBlock roster;        /* +0x8bcc */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

extern int func_02030694(void);     /* the session is ready */

/* Take the three halfwords a peer sent for one seat into the roster and mark
 * that seat present.  The seat number is the message's second byte and the
 * values start at its third, and each one widens to a word on the way in. */
void func_ov002_0206c230(u8 *pMsg)
{
    Ov002RosterBlock *pRoster;
    int i;

    if (func_02030694() == 0) {
        return;
    }

    pRoster = &data_ov002_0207fa00->roster;
    for (i = 0; i < 3; i++) {
        (&pRoster->aSeats[pMsg[1]].nPeerValue)[i] = ((u16 *)pMsg)[i + 1];
    }

    pRoster->bSeatMask |= 1 << (pMsg[1] + 4);
}
