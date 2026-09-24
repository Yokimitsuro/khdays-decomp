/* func_02009044 -- NitroSDK snd_bank.c: SND_GetNextInstData. Walks the bank's instrument table
 * from `pos`, returning the next single instrument, drum-set member or key-split member in
 * `inst`; FALSE once every program is exhausted. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef int BOOL;

#define TRUE 1
#define FALSE 0
#define SND_BANK_TO_WAVEARC_MAX 4
#define SND_INST_KEYSPLIT_MAX 8

typedef enum SNDInstType {
    SND_INST_INVALID = 0,
    SND_INST_PCM = 0x01,
    SND_INST_PSG,
    SND_INST_NOISE,
    SND_INST_DIRECTPCM,
    SND_INST_NULL,
    SND_INST_DRUM_SET = 0x10,
    SND_INST_KEY_SPLIT
} SNDInstType;

typedef struct SNDBinaryFileHeader {
    char signature[4];
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} SNDBinaryFileHeader;

typedef struct SNDBinaryBlockHeader {
    u32 kind;
    u32 size;
} SNDBinaryBlockHeader;

typedef struct SNDWaveArcLink {
    struct SNDWaveArc *waveArc;
    struct SNDWaveArcLink *next;
} SNDWaveArcLink;

typedef struct SNDBankData {
    struct SNDBinaryFileHeader fileHeader;
    struct SNDBinaryBlockHeader blockHeader;
    struct SNDWaveArcLink waveArcLink[SND_BANK_TO_WAVEARC_MAX];
    u32 instCount;
    u32 instOffset[0];
} SNDBankData;

typedef struct SNDInstParam {
    u16 wave[2];
    u8 original_key;
    u8 attack;
    u8 decay;
    u8 sustain;
    u8 release;
    u8 pan;
} SNDInstParam;

typedef struct SNDInstData {
    u8 type;
    u8 padding_;
    struct SNDInstParam param;
} SNDInstData;

typedef struct SNDKeySplit {
    u8 key[SND_INST_KEYSPLIT_MAX];
    struct SNDInstData instOffset[0];
} SNDKeySplit;

typedef struct SNDDrumSet {
    u8 min;
    u8 max;
    struct SNDInstData instOffset[0];
} SNDDrumSet;

typedef struct SNDInstPos {
    u32 prgNo;
    u32 index;
} SNDInstPos;

BOOL func_02009044(const SNDBankData *bank, SNDInstData *inst, SNDInstPos *pos)
{
    for (; pos->prgNo < bank->instCount; pos->prgNo++, pos->index = 0) {
        u32 instOffset = bank->instOffset[pos->prgNo];
        inst->type = (u8)(instOffset & 0xff);
        instOffset >>= 8;

        switch (inst->type) {
        case SND_INST_PCM:
        case SND_INST_PSG:
        case SND_INST_NOISE:
        case SND_INST_DIRECTPCM:
        case SND_INST_NULL:
        {
            const SNDInstParam *param = (const SNDInstParam *)((u8 *)bank + instOffset);
            inst->param = *param;
            pos->prgNo++;
            return TRUE;
        }
        case SND_INST_DRUM_SET:
        {
            const SNDDrumSet *drumSet = (const SNDDrumSet *)((u8 *)bank + instOffset);
            for (; pos->index < drumSet->max - drumSet->min + 1; pos->index++) {
                *inst = drumSet->instOffset[pos->index];
                pos->index++;
                return TRUE;
            }
            break;
        }
        case SND_INST_KEY_SPLIT:
        {
            const SNDKeySplit *keySplit = (const SNDKeySplit *)((u8 *)bank + instOffset);
            for (; pos->index < SND_INST_KEYSPLIT_MAX; pos->index++) {
                if (keySplit->key[pos->index] == 0)
                    break;
                *inst = keySplit->instOffset[pos->index];
                pos->index++;
                return TRUE;
            }
            break;
        }
        default:
            break;
        }
    }

    return FALSE;
}
