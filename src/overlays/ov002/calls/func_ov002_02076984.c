/* The second parameter is FORWARDED, not used: it arrives in r1 and is handed to
 * the callee untouched, so it costs no instruction and is invisible in the
 * disassembly. Its only trace is that r1 is unavailable as a scratch register,
 * which shifts every other allocation up by one. */
/* Is entry `index` of the secondary table live? The probe reports the entry
 * itself, which is normalised to a plain 0/1 here. */
extern int func_02025694(void *entry, int arg);

typedef struct {
    char pad0000[0x200];
    void *entries[1];       /* +0x200 */
} Ov002ListTable;

typedef struct {
    char pad0000[4];
    Ov002ListTable *pTable;     /* +4 */
} Ov002ListRoot;

extern Ov002ListRoot data_ov002_0207fa20;

int func_ov002_02076984(int index, int arg) {
    return func_02025694(&data_ov002_0207fa20.pTable->entries[index], arg) != 0;
}
