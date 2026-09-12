/* func_ov025_02099a94 -- Ov008_PollSaveCardOp: poll the save menu's pending card
 * operation (+0x238): 1 = a load in flight (Ov008_PollSaveLoad), 2 = nothing to
 * wait for, 3 = a transfer step (Ov008_CardTransferStep); any other value is
 * cleared and reported as 3.  A poll result of 1 (or anything outside 0..4)
 * keeps the operation pending and returns -1; otherwise the operation is
 * finished: after a transfer (op 3) the two "changed" bytes at +0x1efc/+0x1efd
 * set their game flags, and the op is cleared.  Result 2 also re-arms the card
 * poll (func_ov025_020b0a48(1)).
 */
typedef unsigned char u8;

#define CARD_OP_NONE     0
#define CARD_OP_LOAD     1
#define CARD_OP_IDLE     2
#define CARD_OP_TRANSFER 3

#define POLL_PENDING  1
#define POLL_REARM    2
#define POLL_NO_OP    3
#define POLL_FAILED  -1

#define FLAG_SAVE_CHANGED_A 0x18bd
#define FLAG_SAVE_CHANGED_B 0x18c9

typedef struct Ov008SaveMenu {
    u8  pad_0000[0x238];
    int nCardOp;              /* 0x238 */
    u8  pad_023c[0x1efc - 0x23c];
    u8  bChangedA;            /* 0x1efc */
    u8  bChangedB;            /* 0x1efd */
} Ov008SaveMenu;

extern int func_ov025_020b0c74(void);                          /* Ov008_PollSaveLoad */
extern int func_ov025_020b0db0(void);                          /* Ov008_CardTransferStep */
extern void func_020235a8(int nFlag);                          /* GameState_SetFlag */
extern void func_ov025_020b0a48(int bArm);                     /* re-arm the card poll */

int func_ov025_02099a94(Ov008SaveMenu *pMenu, int nSlot, int nPhase, int nArg)
{
    int nResult;

    switch (pMenu->nCardOp) {
    case CARD_OP_LOAD:
        nResult = func_ov025_020b0c74();
        break;
    case CARD_OP_IDLE:
        nResult = 0;
        break;
    case CARD_OP_TRANSFER:
        nResult = func_ov025_020b0db0();
        break;
    default:
        pMenu->nCardOp = CARD_OP_NONE;
        nResult = POLL_NO_OP;
        break;
    }
    switch (nResult) {
    case 0:
    case 2:
    case 3:
    case 4:
        if (pMenu->nCardOp == CARD_OP_TRANSFER) {
            if (pMenu->bChangedA != 0) {
                func_020235a8(FLAG_SAVE_CHANGED_A);
            }
            if (pMenu->bChangedB != 0) {
                func_020235a8(FLAG_SAVE_CHANGED_B);
            }
        }
        pMenu->nCardOp = CARD_OP_NONE;
        break;
    case POLL_PENDING:
    default:
        nResult = POLL_FAILED;
        break;
    }
    if (nResult == POLL_REARM) {
        func_ov025_020b0a48(1);
    }
    return nResult;
}
