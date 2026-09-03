/* ov006 .rodata: the Mission Mode member-select tables.
 *
 * Reconstructed source for three symbols at 0x020562d0-0x020563a4, verified byte and
 * relocation exact with tools/verify_data.py against the delinked ROM image.
 *
 *   020562d0  step handlers      15 entries, one per member-select sub-state
 *   0205628c  setup params       the six roster ids the unlock bits gate, plus the
 *                                Q12 origin the cursor cells are stacked from
 *   0205630c  screen offsets     19 slots: a row of nine at y=0x40 and a row of ten
 *                                at y=0x80, both 0x18 apart
 *
 * The build does not compile this yet -- routing initialized DATA through
 * gen_delinks.py is the next step -- so the file is currently proof, not a build input.
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

const MissionSetupParams data_ov006_0205628c = {
    { 0x11, 0x0a, 0x12, 0x09, 0x08, 0x00 },
    { 0, 0 },
    { 0, 0x20000 },
};

const MissionOffsetTable data_ov006_0205630c = {{
    { 0x20, 0x40 }, { 0x38, 0x40 }, { 0x50, 0x40 }, { 0x68, 0x40 }, { 0x80, 0x40 },
    { 0x98, 0x40 }, { 0xb0, 0x40 }, { 0xc8, 0x40 }, { 0xe0, 0x40 },
    { 0x14, 0x80 }, { 0x2c, 0x80 }, { 0x44, 0x80 }, { 0x5c, 0x80 }, { 0x74, 0x80 },
    { 0x8c, 0x80 }, { 0xa4, 0x80 }, { 0xbc, 0x80 }, { 0xd4, 0x80 }, { 0xec, 0x80 },
}};
