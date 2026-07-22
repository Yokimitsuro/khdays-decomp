/* Point the five active-party slots at their roster entries. Each argument is an
 * index into the 0x18-byte roster; the fifth arrives on the stack. */
typedef struct {
    char bytes[0x18];
} RosterEntry;

typedef struct {
    char pad0000[8];
    RosterEntry *slots[5];  /* +8 */
} PartyState;

extern RosterEntry data_02042418[];
extern PartyState data_020423fc;

void func_02010e38(int a, int b, int c, int d, int e) {
    data_020423fc.slots[0] = &data_02042418[a];
    data_020423fc.slots[1] = &data_02042418[b];
    data_020423fc.slots[2] = &data_02042418[c];
    data_020423fc.slots[3] = &data_02042418[d];
    data_020423fc.slots[4] = &data_02042418[e];
}
