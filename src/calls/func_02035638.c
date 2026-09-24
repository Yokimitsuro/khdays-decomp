#pragma thumb on
/* func_02035638 -- rebuild the dialogue record of member `slot` (1-based), MAIN. The member's
 * message record (+0x44) is released and rebuilt from message db 0x1e (func_020342e8, kind 5 with
 * `msgArg`) with the db pinned around it, then the member's flags (+0x4) are recomputed from two
 * progress queries (func_020235d0): 0x37c7 gives 0 = record marked (+0x30), 1 = 0x800, 2 = 0x1;
 * 0x35bf gives 1 = 0x1000|0x200, 2 = 0x2; a member whose table entry (data_0204c678, stride
 * 0x104, byte +3) is 0xe also gets 0x1 once flag 0x208c is set. */
typedef unsigned char u8;

typedef struct PartyMsgRec {
    char pad00[0x30];
    int marked;                         /* +0x30 */
} PartyMsgRec;

typedef struct PartyMember {
    int pad00;
    unsigned int flags;                 /* +0x04 */
    char pad08[0x44 - 8];
    PartyMsgRec *msg;                   /* +0x44 */
} PartyMember;

typedef struct PartyEntry {
    u8 pad00[3];
    u8 kind;                            /* +0x03 */
    u8 pad04[0x104 - 4];
} PartyEntry;

extern PartyMember *func_020358a4(int idx);
extern int func_02034150(int db, int mode);
extern void func_020343cc(PartyMsgRec **rec_out);
extern int func_020342e8(PartyMsgRec **rec_out, int db, int arg, int kind);
extern void func_02034258(int db);
extern int func_020235d0(int id, int mode);
extern int func_02023588(int id);
extern PartyEntry data_0204c678[];

void func_02035638(int slot, int msgArg)
{
    PartyMember *member = func_020358a4(slot - 1);
    int state;

    func_02034150(0x1e, 2);
    if (member->msg != 0) {
        func_020343cc(&member->msg);
    }
    func_020342e8(&member->msg, 0x1e, msgArg, 5);
    func_02034258(0x1e);
    state = func_020235d0(0x37c7, 2);
    member->flags = 0;
    switch (state) {
    case 0:
        member->msg->marked = 1;
        break;
    case 1:
        member->flags |= 0x800;
        break;
    case 2:
        member->flags |= 1;
        break;
    }
    switch (func_020235d0(0x35bf, 2)) {
    case 0:
        break;
    case 1:
        member->flags |= 0x1000;
        member->flags |= 0x200;
        break;
    case 2:
        member->flags |= 2;
        break;
    }
    if (((PartyEntry *)((u8 *)data_0204c678 + slot * sizeof(PartyEntry)))->kind == 0xe && func_02023588(0x208c)) {
        member->flags |= 1;
    }
}
