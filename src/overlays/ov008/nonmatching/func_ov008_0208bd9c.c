/* UNFINISHED. 176/176 bytes, one 3-instruction scheduling window off.
 *
 * Begin a save WRITE for `slot`.  Fully decoded; the save format below is
 * confirmed from both sides (the read side is Ov008_PollSaveLoad):
 *     +0x00  magic 0xc8f592a6
 *     +0x04  SHA1 digest, 0x14 bytes, over `state`
 *     +0x18  state, 0x1cac bytes  <-- this IS what data_0204be18 points at, and
 *            GameState_IsFlagSet/SetFlag/GetField read its +0x10 bit store
 * Card block size is 0x2018.  playTimeSeconds is the state's first field.
 *
 * It also accumulates PLAY TIME: ((now - lastTick) << 6) / 0x1ff6210, where
 * 0x1ff6210 = 33,513,488 is the DS system clock and <<6 is because the OS tick
 * runs at clock/64 -- so the quotient is seconds.
 *
 * WHAT DIFFERS: only where data_0204be18 is loaded.
 *   ROM   ldr r0,[pc] ; lsls r1,r1,#6 ; ldr r4,[r0] ; lsrs r0,r3,#0x1a
 *   ours  ldr r2,[pc] ; lsrs r0,r3,#0x1a ; lsls r1,r1,#6 ; ldr r4,[r2]
 * The ROM interleaves the deref between the two shifts; mwcc puts it after both.
 * Everything before and after is byte-identical.
 *
 * RULED OUT:
 *   `*p += e` vs `*p = *p + e` vs a temp for the seconds (+4 bytes)
 *   splitting the delta and the <<6 (moves 0x34 -> 0x3D, i.e. closer; kept)
 *   dropping the (int) cast on the quotient
 *   a local pointer for data_0204be18 (hoists the load even earlier)
 *   * 2026-07-20: full TYPING pass -- real SaveFile/GameState/CardTransferCtx
 *     structs, which had just cracked func_ov008_0208b9e8 and func_ov007_0204ce94
 *     that same day.  Same residue at 0x3D.  Kept below: far better C, and it is
 *     where the save format is written down.
 *   arity and THUMB mode both verified.
 *
 * Twins riding on this: func_ov009_02055e18, func_ov025_020b0d00.
 */
typedef struct {
    int playTimeSeconds;        /* +0x00 */
    unsigned char pad04[0xc];
    unsigned char bits[1];      /* +0x10: the packed flag/bitfield store */
} GameState;

typedef struct {
    unsigned int magic;         /* 0xc8f592a6 */
    unsigned char sha1[0x14];   /* +0x04, digest of `state` */
    GameState state;            /* +0x18, 0x1cac bytes */
} SaveFile;

typedef struct {
    unsigned char blockCounter;
    unsigned char slot;
    unsigned char pad02[2];
    int resultCode;
    void *thread;
} CardTransferCtx;

extern void CARD_UnlockBackup(unsigned short lock);
extern int func_02020904(void);
extern int func_ov008_0208b930(int a, void *b, int c);
extern void func_0200e164(int id);
extern void func_020208f0(void);
extern long long func_020031d4(void);
extern void MATH_CalcSHA1(void *digest, const void *data, unsigned int len);
extern void func_ov008_0208ba70(int arg0, int arg1, int arg2);

extern unsigned short data_0204be10;
extern long long data_0204be1c;
extern GameState *data_0204be18;
extern SaveFile *data_0204be14;
extern CardTransferCtx data_ov008_02090fb4;

int func_ov008_0208bd9c(int slot) {
    int local;
    long long delta;

    CARD_UnlockBackup(data_0204be10);
    func_02020904();
    if (func_ov008_0208b930(0, &local, 1) != 0) {
        func_0200e164(data_0204be10);
        func_020208f0();
        return 0;
    }
    delta = (func_020031d4() - data_0204be1c) << 6;
    data_0204be18->playTimeSeconds += (int)(delta / 0x1ff6210);
    MATH_CalcSHA1(data_0204be14->sha1, &data_0204be14->state, 0x1cac);
    data_0204be14->magic = 0xc8f592a6;
    data_ov008_02090fb4.blockCounter = 0;
    data_ov008_02090fb4.slot = (unsigned char)slot;
    func_ov008_0208ba70((data_ov008_02090fb4.slot << 1) * 0x2018 + 0x20,
                        (int)data_0204be14, 0x2018);
    return 1;
}
