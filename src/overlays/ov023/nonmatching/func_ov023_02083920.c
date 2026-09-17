/* NONMATCHING (parked 2026-09-17, user decision after the sweeps below).  Best candidate: same size,
 * same instructions and relocations as the ROM; the residue is a register-allocator choice that no
 * mwcc build in tools/mwccarm reproduces.  Notes from build/held/ov023:
 *
 * # func_ov023_02083920 (Ov023_CreateHintSprites, THUMB, 152 B) — HOLD 16/09
 *
 * Best: build/held/ov023/func_ov023_02083920.c (struct form) — 152/152 bytes, relocs OK, 37 instr diffs.
 *
 * ROM keeps FIVE loop values: r4 = pScene, r6 = 0x144 (movs #0x51 / lsls #2, materialised ONCE before the
 * pre-loop func_02032388 call and reused by all seven `adds r0, r4, r6` leas + the slot induction init
 * `adds r5, r4, r6`), r5 = pScene+0x144+4i with `[r5, r1=0x4a38]`, r7 = &positions[i], and `i` SPILLED to [sp].
 * Every mwcc form tried either (a) hoists `pScene + 0x144` into a register (struct member / cast forms:
 * constloc, mgrstruct, castu8, idx0, scalar, intarr, inline helpers, const global) or (b) keeps per-use leas
 * but rematerialises the constant into r0 every time (u8 *pScene local: u8base, aw*, ip*, head*, offsetof*),
 * or (c) CSEs the leas into the slot-induction base with 4 stack copies (pind*, mix*, u8mgr).
 * Swept: base local type (Ov023Scene*/u8*/int*/u32*/Head*), slot expression association (assoc1-4), walking
 * offset variable (walk1-3), offsetof/shift/mul/unsigned/long spellings, pragmas opt_common_subs/
 * opt_loop_invariants/opt_propagation, register/const/block-scope/do-while/while, const global, inline helpers.
 * Corpus search: no other THUMB function in the ROM (≤1200 B) keeps a movs/lsls constant in a callee-saved
 * register across calls — unique shape. Next idea: find what makes mwcc treat 0x144 as a VALUE (single def)
 * without CSE-ing `pScene + 0x144`; maybe a synthetic mwcc probe with two different bases sharing one offset.
 *
 * 17/09: 7 stride-array forms (the manager as `&pScene->aBlock[1]` of a 0x144-byte block type, `aBlock + 1`,
 * `(u8 *)pScene + 1 * 0x144`, an index variable, the slots through `(u8 *)&aBlock[1] + 0x4a38 + i * 4`):
 * all still hoist the sum into a register; the last one (X6) does reproduce the `i` spill to [sp] with the
 * slot walker in r5 (30 diffs) but keeps pManager in r6 instead of 0x144.
 *
 * 17/09 (b) -- still OPEN, not archived (user's instruction). Micro harness build/try/micro/m3920*.c:
 * - A plain loop with only calls (`f1(p->sprites, i); f2(p->sprites, i)`) DOES give the ROM's mechanism in
 *   build 139: 0x144 hoisted into r6 and `adds r0, r4, r6` per call (t2). So the constant-in-register is
 *   natural; what breaks it is the slot store.
 * - As soon as the loop also stores `((M *)p->sprites)->ap[i]`, mwcc makes the manager sum the IV base
 *   (r5 = pManager + 4i, `[r5, #0x4a38]` like the ROM) and then materialises ONE COPY PER CALL USE of the
 *   invariant sum (r6, r7, then stack slots [sp], [sp+4].. for 5 uses) instead of rematerialising it (u1/v2,
 *   and s3920e u8_cast in the real function: four stack copies, 160 B). The ROM rematerialises.
 * - `S *volatile p` gives per-use adds with the constant hoisted (v3) but reloads p from the stack each time.
 * - Swept on top of the earlier list: const global, const local pointer, callee parameter types
 *   (SpriteManager * / u8 * / int), the slot address as (sprites + i*4)[0x4a38/4] and 8 other associations
 *   (c/h/m: i spilled and IV right but the sum hoisted once in r6), pragmas opt_loop_invariants /
 *   opt_common_subs / opt_propagation off, register/volatile p, p reassigned each iteration from a second
 *   local or from a const global, self-assignment. None rematerialises the sum.
 * Open question: what makes build 139 rematerialise `p + 0x144` per use instead of copying the hoisted value
 * (the copies are what forces the spill of `i`). If no source form does, this is a build >= 140 difference.
 *
 * 17/09 (c) -- micro harness build/try/micro/m3920[d-l].c, the decisive data:
 * - The ROM needs THREE things at once: (1) the slot IV based on the manager (r5 = pScene+0x144+4i,
 *   [r5, #0x4a38]), (2) pScene kept in r4 and the manager RECOMPUTED per call from r4 + r6, (3) 0x144
 *   kept in r6. Build 139 gives (2)+(3) whenever the loop has no manager-based IV (t2, v_b with a
 *   volatile counter, h4 with the scene passed from the global to an inline body) and gives (1) whenever
 *   the slot store goes through the manager -- but then LICM unifies the five call arguments with the IV's
 *   base node and materialises them as COPIES (r6, r7, [sp]..) or, for an int-typed argument, one hoisted
 *   copy. The only form that gave (1)+(2)+(3) in the micro is a two-step base node
 *   `(u8 *)&((S2 *)p)->nLast + 4` (address-of a member at 0x140, then +4): the IV init then costs two adds
 *   instead of the ROM's single `adds r5, r4, r6`. Every single-add spelling of pScene+0x144 (member,
 *   array decay, union member, address-of-member-at-0, int cast, different struct type, pad+0x144,
 *   walker pointer, inline helper with the scene / manager as parameter) is one CSE node with the calls.
 * - No build in tools/mwccarm (2.0, 3.0/136, 3.0/139, DSi 1.1-1.6) rematerialises the sum from two
 *   registers when the copies would need the stack; the DSi line hoists it into r4 instead.
 * Conclusion: the ROM's allocator rematerialises `p + const` from live registers instead of spilling
 * copies; build 139 does not. Compiler-version residue unless a natural two-step address exists at 0x144.
 */
/* func_ov023_02083920 -- Ov023_CreateHintSprites: create the event scene's three hint sprites.
 * The sprite manager at +0x144 is initialised with the "ev/hint_&.z" resource
 * (data_ov023_0208a098, enabled, 02032388); then three sprites are created (02032444) and kept
 * at +0x4b7c, each placed at its position from data_ov023_02089cfc (0203257c), sent to its
 * first animation entry (020325ec 0), shown (02032710 1) and left in the plain mode
 * (0203281c 0). */
typedef unsigned char  u8;

typedef struct Fx32Pair {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
} Fx32Pair;

typedef struct SpriteManagerInit {
    void *pResource;          /* 0x00 */
    int  bEnabled;            /* 0x04 */
    int  nReserved0;          /* 0x08 */
    int  nReserved1;          /* 0x0c */
} SpriteManagerInit;

typedef struct Ov023Scene {
    u8   pad_00000[0x144];
    u8   sprites[0x4b7c - 0x144]; /* 0x00144: the sprite manager */
    void *apHintSprite[3];    /* 0x04b7c */
} Ov023Scene;

typedef struct Ov023SceneRoot {
    int  nField00;            /* 0x00 */
    Ov023Scene *pScene;       /* 0x04 */
} Ov023SceneRoot;

typedef struct Ov023HintPositions {
    Fx32Pair aPos[3];         /* 0x00 */
} Ov023HintPositions;

extern void  func_02032388(void *pManager, SpriteManagerInit *pInit);  /* SpriteManager_Init */
extern void *func_02032444(void *pManager, int nIndex, int nArg);      /* SpriteManager_Create */
extern void  func_0203257c(void *pManager, void *pSprite, Fx32Pair *pPos); /* Sprite_SetPosition */
extern void  func_020325ec(void *pManager, void *pSprite, int nEntry); /* Sprite_SetEntry */
extern void  func_02032710(void *pManager, void *pSprite, int bVisible); /* Sprite_SetVisible */
extern void  func_0203281c(void *pManager, void *pSprite, int nMode);  /* Sprite_SetMode */
extern Ov023SceneRoot data_ov023_0208a784;
extern const Ov023HintPositions data_ov023_02089cfc;                /* the hint positions */
extern char  data_ov023_0208a098[];                                 /* "ev/hint_&.z" */

void func_ov023_02083920(void)
{
    SpriteManagerInit init;
    Ov023HintPositions positions;
    int i;
    Ov023Scene *pScene;

    pScene = data_ov023_0208a784.pScene;
    positions = data_ov023_02089cfc;
    init.pResource = data_ov023_0208a098;
    init.bEnabled = 1;
    init.nReserved0 = 0;
    init.nReserved1 = 0;
    func_02032388(pScene->sprites, &init);
    for (i = 0; i < 3; i++) {
        pScene->apHintSprite[i] = func_02032444(pScene->sprites, i, 0);
        func_0203257c(pScene->sprites, pScene->apHintSprite[i], &positions.aPos[i]);
        func_020325ec(pScene->sprites, pScene->apHintSprite[i], 0);
        func_02032710(pScene->sprites, pScene->apHintSprite[i], 1);
        func_0203281c(pScene->sprites, pScene->apHintSprite[i], 0);
    }
}
