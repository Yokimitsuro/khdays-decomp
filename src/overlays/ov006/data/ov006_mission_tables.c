/* ov006 .rodata tail: the Mission Mode member-select tables.
 *
 * Reconstructed source for 0x0205628c-0x020563a4, the last 280 bytes of the overlay's
 * .rodata, verified byte and relocation exact with tools/verify_data.py against the
 * delinked ROM image. The range is contiguous and ends exactly at the section end, so
 * it can own a single .rodata range in delinks.txt.
 *
 *   0205628c  setup params        the six roster ids the unlock bits gate, plus the Q12
 *                                 origin the cursor cells are stacked from
 *   0205629c  scene setup         a 20-byte record the scene constructor copies onto the
 *                                 stack and passes by value to the scene-init call at
 *                                 0x0204d098 together with the context
 *   020562b0  buffer targets      one destination per cell buffer; the flush pass walks
 *                                 the dirty mask and enqueues a 0x600-byte transfer from
 *                                 cellBuffers[i] to targets[i]
 *   020562d0  step handlers       15 entries, one per member-select sub-state
 *   0205630c  screen offsets      19 slots: a row of nine at y=0x40 and a row of ten at
 *                                 y=0x80, both 0x18 apart
 */

typedef signed char s8;
typedef unsigned char u8;

typedef struct {
    int x;
    int y;
} MissionOffset;

typedef struct {
    MissionOffset entries[19];
} MissionOffsetTable;

typedef struct {
    s8 ids[6];
    u8 pad_0006[2];
    MissionOffset origin;
} MissionSetupParams;

typedef void (*MissionStepFn)(void);
typedef void (*MissionSceneFn)(void);

typedef struct {
    int limit0;
    int limit1;
    int limit2;
    MissionSceneFn callback0;
    MissionSceneFn callback1;
} MissionSceneSetup;

typedef struct {
    int targets[8];
} MissionBufferTargets;

extern void func_ov006_02054a90(void);
extern void func_ov006_02054aa0(void);

extern void func_ov006_020552ac(void);
extern void func_ov006_02055340(void);
extern void func_ov006_02055344(void);
extern void func_ov006_020553d8(void);
extern void func_ov006_020553dc(void);
extern void func_ov006_02055560(void);
extern void func_ov006_020556b8(void);
extern void func_ov006_020556bc(void);
extern void func_ov006_020556c0(void);
extern void func_ov006_020556e8(void);
extern void func_ov006_020556ec(void);
extern void func_ov006_020557d4(void);
extern void func_ov006_02055800(void);
extern void func_ov006_02055804(void);
extern void func_ov006_020558e0(void);

const MissionSetupParams data_ov006_0205628c = {
    { 0x11, 0x0a, 0x12, 0x09, 0x08, 0x00 },
    { 0, 0 },
    { 0, 0x20000 },
};

const MissionSceneSetup data_ov006_0205629c = {
    50,
    50,
    20,
    func_ov006_02054a90,
    func_ov006_02054aa0,
};

const MissionBufferTargets data_ov006_020562b0 = {{
    8, 9, 10, 11,
    24, 25, 26, 27,
}};

const MissionStepFn data_ov006_020562d0[15] = {
    func_ov006_020552ac,
    func_ov006_02055340,
    func_ov006_02055344,
    func_ov006_020553d8,
    func_ov006_020553dc,
    func_ov006_02055560,
    func_ov006_020556b8,
    func_ov006_020556bc,
    func_ov006_020556c0,
    func_ov006_020556e8,
    func_ov006_020556ec,
    func_ov006_020557d4,
    func_ov006_02055800,
    func_ov006_02055804,
    func_ov006_020558e0,
};

const MissionOffsetTable data_ov006_0205630c = {{
    { 0x20, 0x40 }, { 0x38, 0x40 }, { 0x50, 0x40 }, { 0x68, 0x40 }, { 0x80, 0x40 },
    { 0x98, 0x40 }, { 0xb0, 0x40 }, { 0xc8, 0x40 }, { 0xe0, 0x40 },
    { 0x14, 0x80 }, { 0x2c, 0x80 }, { 0x44, 0x80 }, { 0x5c, 0x80 }, { 0x74, 0x80 },
    { 0x8c, 0x80 }, { 0xa4, 0x80 }, { 0xbc, 0x80 }, { 0xd4, 0x80 }, { 0xec, 0x80 },
}};
