/* Projectile action enter step (Ghidra: Ov150_ProjectileAction_Enter).
 *
 * Posts tag update 4 on the owner, raises bit 0x40 of the actor flags at +0x1ae,
 * hands the canned 4-byte event record data_ov150_020d256c[1] to the owner's
 * notify callback at +0x24, starts anim 1 on the rig at +0x3cc, sets bit 0x40 in
 * the high byte of the status halfword at +0x60 and dispatches the next step.
 *
 * The same ROM, up to relocations, is shared with six siblings: ov141 020cd2b0,
 * ov142 020d0ef0, ov143 020d4b30, ov149 020cf0d4, ov151 020ce4f0 and ov152
 * 020d5d70.
 *
 * Codegen note on the two-halfword record copy. Written as a plain pair of
 * halfword assignments, mwcc merges the two stores and colours them last-first:
 * the last value takes the lowest free register and the first falls to r3,
 * giving `ldrh r3,[r2,#6] ; ldrh r0,[r2,#4]`. The ROM instead gives the first
 * value the lowest free register and lets the second reuse the pool base as it
 * dies. Reading the two halves through a char * cursor into named temporaries
 * and storing them through volatile lvalues keeps the merged emission but
 * restores the ROM's colouring:
 *
 *     ldrh r0, [r2, #6]
 *     ldrh r2, [r2, #4]
 *     strh r0, [sp, #2]
 *     strh r2, [sp]
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

typedef struct Ov150State Ov150State;

typedef void (*Ov150Callback)(Ov150State *state, u16 *pair, int count);

struct Ov150State {
    u8 pad_0000[0x24];
    Ov150Callback callback;              /* +0x024 */
    u8 pad_0028[0x38];
    u16 field_0060;                      /* +0x060 */
    u8 pad_0062[0x14c];
    u16 flags_01ae;                      /* +0x1ae */
    u8 pad_01b0[0x21c];
    int field_03cc;                      /* +0x3cc */
};

typedef struct Ov150StateRef {
    Ov150State *state;                   /* +0x00 */
} Ov150StateRef;

typedef struct Ov150Node {
    u8 pad_0000[4];
    Ov150StateRef *state_ref;            /* +0x04 */
    u8 pad_0008[0x18];
    s8 index_20;                         /* +0x20 */
} Ov150Node;

extern void func_ov107_020c9264();
extern void func_ov107_020c9ee8();
extern void func_0203c634(void *obj, int idx, void *value);
extern u16 data_ov150_020d256c[4];
extern void func_ov150_020d0fa8(void);

void func_ov150_020d0ef4(Ov150Node *node)
{
    Ov150StateRef *state_ref = node->state_ref;
    u16 buf[2];
    u16 *pp;
    Ov150Callback cb;

    func_ov107_020c9264(state_ref->state, 4, 0);
    state_ref->state->flags_01ae |= 0x40;

    pp = buf;
    {
        char *src = (char *)data_ov150_020d256c;
        u16 high = *(u16 *)(src + 6);
        u16 low = *(u16 *)(src + 4);

        *(volatile u16 *)&pp[1] = high;
        *(volatile u16 *)&pp[0] = low;
    }

    cb = state_ref->state->callback;
    if (cb != 0) {
        cb(state_ref->state, pp, 4);
    }

    func_ov107_020c9ee8(state_ref->state->field_03cc, 1, 0);

    {
        u16 value = state_ref->state->field_0060;
        state_ref->state->field_0060 =
            (u16)((value & ~0xff00) |
                  (((((unsigned int)value << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    }

    func_0203c634(node,
                  node->index_20,
                  func_ov150_020d0fa8);
}
