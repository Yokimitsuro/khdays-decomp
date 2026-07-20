/* Script-VM command handler with a VARIABLE ENTRY LIST and a per-entry switch --
 * the most complex member of the family, and the one the generator cannot touch.
 * Builder: func_ov021_0208024c.
 *
 * The loop bound IS the builder id: descs+8 is fetched once and used both as the
 * entry count and, truncated to u16, as the id passed to the builder.
 *
 * Entries are SIX bytes ({u8 type; short value; u8 flag}) starting at
 * params+0x14, and each entry's type selects how its value is fetched -- a
 * four-case jump table where only case 3 advances the cursor without fetching,
 * and any type above 3 advances nothing at all (the range check is `bhi`, so a
 * negative type lands in the default too).
 *
 * Two things that each cost a compile:
 *   - params.bField12 needs an UNSIGNED shift. The ROM emits `lsrs`; reading the
 *     packed word as a signed int gives `asr` and a one-instruction diff.
 *   - inside each case, the cursor advance must be pinned BEFORE the store by
 *     putting the fetched value in a temp first. Written as
 *     `entry->nValue = fetch(descs); descs += 8;` the advance sinks past the
 *     store. Same lever as func_ov002_0207d610, so it is not specific to pointer
 *     arithmetic: any statement mwcc is free to move, it moves.
 */
typedef struct {
    unsigned char bType;     /* +0x00 */
    char pad01[1];
    short nValue;            /* +0x02 */
    unsigned char bFlag;     /* +0x04 */
    char pad05[1];
} Ov021Entry;                /* 6 */

typedef struct {
    int nField00;            /* +0x00 */
    int nField04;            /* +0x04 */
    unsigned char bField08;  /* +0x08 */
    char pad09[1];
    short nField0a;          /* +0x0a */
    short nField0c;          /* +0x0c */
    short nField0e;          /* +0x0e */
    short nField10;          /* +0x10 */
    unsigned char bField12;  /* +0x12 */
    char pad13[1];
    Ov021Entry aEntries[32]; /* +0x14 -- extent bounded by the 0xd4 frame slot */
} Ov021EmitParams;           /* 0xd4 */

extern int func_02021948(void *self, void *desc);
extern int func_02021980(void *self, void *desc);
extern int func_02021994(void *self, void *desc);
extern int func_ov021_0208024c(unsigned short count, Ov021EmitParams *params);
extern void func_ov002_0207643c(int target, int value);

int func_ov021_02080c98(void *self, char *descs) {
    Ov021EmitParams params;
    int target;
    int count;
    int i;
    short v;

    target = func_02021980(self, descs);
    count = func_02021980(self, descs + 0x8);
    params.nField00 = func_02021948(self, descs + 0x10);
    params.nField04 = func_02021994(self, descs + 0x18);
    params.bField08 = func_02021980(self, descs + 0x20);
    params.nField0a = func_02021994(self, descs + 0x28);
    params.nField0c = func_02021994(self, descs + 0x30);
    params.nField0e = func_02021994(self, descs + 0x38);
    params.nField10 = *(int *)(descs + 0x44);
    params.bField12 = *(unsigned int *)(descs + 0x44) >> 16;
    descs += 0x48;
    for (i = 0; i < count; i++) {
        params.aEntries[i].bType = func_02021980(self, descs);
        descs += 8;
        switch ((signed char)params.aEntries[i].bType) {
        case 0:
            v = func_02021980(self, descs);
            descs += 8;
            params.aEntries[i].nValue = v;
            break;
        case 1:
            v = func_02021994(self, descs);
            descs += 8;
            params.aEntries[i].nValue = v;
            break;
        case 2:
            v = func_02021980(self, descs);
            descs += 8;
            params.aEntries[i].nValue = v;
            break;
        case 3:
            descs += 8;
            break;
        }
        params.aEntries[i].bFlag = 0;
    }
    func_ov002_0207643c(target,
                        func_ov021_0208024c((unsigned short)count, &params));
    return 1;
}
