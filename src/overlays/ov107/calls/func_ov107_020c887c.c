/* Load "Ms/UP.bin", pick record `recordIndex` (remembered at AiState +0x19e)
 * and store its two halfwords, sign-extended and scaled by 16, into
 * AiState +0x224 / +0x228. The file is a u16 header followed by 4-byte
 * records.
 *
 * The file name and the read-back pair share one stack struct. The
 * block-copied name keeps the whole struct in memory, so the pair is stored
 * with strh and reloaded with ldrsh after the free, the way the ROM does it.
 * As separate locals the pair would be forwarded in registers. Reading the
 * record field by field (not as a struct copy) keeps file + 2 as its own
 * base; a struct copy folds the +2 into the load offsets. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Record {
    u16 field_00;
    u16 field_02;
} Record;

typedef struct Path {
    char name[10];
} Path;

typedef struct RecordLookup {
    short field_00;     /* sp+0: record halfword 0, read back after the free */
    short field_02;     /* sp+2: record halfword 1 */
    Path path;          /* sp+4: file name handed to the loader */
} RecordLookup;

typedef struct AiState {
    char pad0[0x19e];
    u8 field_19e;
    char pad1[0x224 - 0x19f];
    int field_224;
    int field_228;
} AiState;

extern const char data_ov107_020cb642[10];     /* "Ms/UP.bin" */
extern void *func_0201ef9c(char *name, u32 kind);
extern void NNSi_FndFreeFromDefaultHeap(void *p);

void func_ov107_020c887c(AiState *self, u8 recordIndex)
{
    RecordLookup lookup;

    lookup.path = *(const Path *)data_ov107_020cb642;
    self->field_19e = recordIndex;

    {
        char *file = func_0201ef9c(lookup.path.name, 11);
        Record *records = (Record *)(file + 2);
        Record *rec = &records[self->field_19e];

        lookup.field_00 = rec->field_00;
        lookup.field_02 = rec->field_02;

        NNSi_FndFreeFromDefaultHeap(file);
        self->field_224 = lookup.field_00 << 4;
        self->field_228 = lookup.field_02 << 4;
    }
}
