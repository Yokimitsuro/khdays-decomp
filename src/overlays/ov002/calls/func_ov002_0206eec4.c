typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

typedef struct Ov002SeatState {
    u16 hFlags;                 /* 0x00 */
    s16 aSeat[4];               /* 0x02, -1 while the seat is free */
    u8 bMask;                   /* 0x0a, one bit per seat that answered */
} Ov002SeatState;

typedef struct Ov002SeatMsg {
    u8 nOp;                     /* 0x00 */
    u8 nSeat;                   /* 0x01 */
    char pad002[2];
    int nValue;                 /* 0x04 */
} Ov002SeatMsg;

extern Ov002SeatState *data_ov002_0207fa04;

/* Non-zero once the link session is up and running the seats itself. */
extern int func_02030694(void);
/* The mask of seats the session currently holds. */
extern int func_01fff974(void);

/* Handle one seat message.
 *
 * Op 2 claims the first free seat for the value the message carries, and is
 * only honoured while the session is not running the seats itself.  Op 3 marks
 * one seat as having answered.  Op 4 takes the whole answered mask from the
 * session and flips the state over to waiting.  Anything else is ignored.
 */
void func_ov002_0206eec4(Ov002SeatMsg *pMsg)
{
    Ov002SeatState *pState;
    int i;

    pState = data_ov002_0207fa04;
    switch (pMsg->nOp) {
    case 2:
        if (func_02030694() != 0) {
            return;
        }
        for (i = 0; i < 4; i++) {
            if (pState->aSeat[i] == -1) {
                pState->aSeat[i] = (s16)pMsg->nValue;
                return;
            }
        }
        break;

    case 3:
        pState->bMask |= 1 << pMsg->nSeat;
        break;

    case 4:
        pState->bMask = (u8)func_01fff974();
        pState->hFlags = (pState->hFlags | 0x10) & ~8;
        break;
    }
}
