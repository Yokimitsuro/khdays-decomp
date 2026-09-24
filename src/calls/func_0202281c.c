#pragma thumb on
/* func_0202281c -- pause menu input poll, MAIN (THUMB). Always returns 0. While func_02030788 holds,
 * a first open (+0xe8 clear, root state 1) outside mode bit 1 hands over to the overlay and sets
 * game field 0x2484. With data_0204c240 bit 2 outside mode bit 1 it only runs the pending-request
 * pair (func_0202348c / func_020234e8) when field 0x248f is set and nothing is open. Otherwise the
 * menu needs data_0204bd85 or field 0x20ef, an idle menu (func_020208e0) and an expired timer
 * (+0xc8, counted down here); it then reacts to B or a latched request (+0xd8): it is refused while
 * func_0201e428 reports busy (unless mode 0xc without func_0201e438), in mode bit 1 without the
 * overlay's permission, and it only latches the request (+0xd8) in mode bit 3 with data_0204be04
 * clear or when an entry (+0xdc) finds none of the three overlay states; a real open pushes step 1
 * or 2 (func_020208d0) before func_020208a4(0). */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    char pad0000[0xc8];
    int timer;                          /* +0xc8 */
    char pad00cc[0xd8 - 0xcc];
    int request;                        /* +0xd8 */
    int entry;                          /* +0xdc */
    int handedOver;                     /* +0xe0 */
    int pad00e4;
    int opened;                         /* +0xe8 */
} PauseContext;

typedef struct {
    u16 state;                          /* +0x00 */
    u16 pad02;
    PauseContext *pCtx;                 /* +0x04 */
} Root0204be08;

extern Root0204be08 data_0204be08;
extern u8 data_0204c240;
extern u8 data_0204bd85;
extern u8 data_0204be04;
extern unsigned short data_0204c190;    /* keys pressed this frame */

extern int func_02030788(void);
extern int func_02020a9c(void);
extern void func_ov023_02083aa8(void);
extern void func_020235e8(int field, int width, int value);    /* GameState_SetField */
extern int func_0201e438(void);
extern int func_ov023_02083a48(void);
extern int func_02023588(int flag);                             /* GameState_IsFlagSet */
extern void func_0202348c(void);
extern void func_020234e8(void);
extern int func_020208e0(void);
extern int func_0201e428(void);
extern int func_ov002_0205196c(void);
extern int func_ov002_02063888(void);
extern int func_ov002_0205f4e0(void);
extern int func_ov002_0205f488(void);
extern int func_ov002_0205f4b4(void);
extern void func_020208d0(u8 step);
extern void func_020208a4(int a);

int func_0202281c(void)
{
    PauseContext *ctx = data_0204be08.pCtx;

    if (func_02030788() != 0) {
        if (func_02020a9c() & 2) {
            return 0;
        }
        if (ctx->opened == 0 && data_0204be08.state == 1) {
            func_ov023_02083aa8();
            func_020235e8(0x2484, 1, 1);
            ctx->opened = 1;
            return 0;
        }
    }
    if ((data_0204c240 & 4) && !(func_02020a9c() & 2)) {
        if ((func_0201e438() == 0 || func_ov023_02083a48() != 0) && func_02023588(0x248f) != 0
            && ctx->opened == 0) {
            func_0202348c();
            func_020234e8();
        }
        return 0;
    }
    if (data_0204bd85 == 0 && func_02023588(0x20ef) == 0) {
        return 0;
    }
    if (func_020208e0() != 0) {
        return 0;
    }
    if (ctx->timer > 0) {
        ctx->timer--;
        return 0;
    }
    if ((data_0204c190 & 8) || ctx->request != 0) {
        if (func_0201e428() != 0 && (func_02020a9c() != 0xc || func_0201e438() != 0)) {
            return 0;
        }
        if ((func_02020a9c() & 2) && func_ov002_0205196c() == 0) {
            return 0;
        }
        if ((func_02020a9c() & 8) && data_0204be04 == 0) {
            ctx->request = 1;
            return 0;
        }
        if (ctx->entry != 0) {
            if (func_ov002_02063888() != 0) {
                return 0;
            }
            if (func_ov002_0205f4e0() == 0 && func_ov002_0205f488() == 0 && func_ov002_0205f4b4() == 0) {
                ctx->request = 1;
                return 0;
            }
            func_020208d0(((data_0204c240 & 4) && (func_02020a9c() & 2)) ? 2 : 1);
        }
        func_020208a4(0);
    }
    return 0;
}
#pragma thumb off
