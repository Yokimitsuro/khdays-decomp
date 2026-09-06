typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct MtxFx33 {
    int m[9];
} MtxFx33;

typedef struct Ov008DecodedTransform {
    u32 resourceIndex;
    VecFx32 scale;
    MtxFx33 rotation;
    VecFx32 translation;
} Ov008DecodedTransform;

extern void MI_CpuFill8(void *dst, int value, unsigned int size);
extern void MTX_Identity33_(MtxFx33 *matrix);

static inline u32 *GetTransformIndexEntry(u8 *dictionaryBase, u32 recordIndex)
{
    u16 tableOffset;
    u16 stride;

    if (dictionaryBase != 0 && recordIndex < dictionaryBase[1]) {
        tableOffset = *(u16 *)(dictionaryBase + 6);
        stride = *(u16 *)(dictionaryBase + tableOffset);
        return (u32 *)(dictionaryBase + tableOffset + 4 + stride * recordIndex);
    }
    return 0;
}

void func_ov008_0205bd50(Ov008DecodedTransform *outTransform,
                          u8 *resourceBase, u32 recordIndex)
{
    u8 *dictionaryBase;
    u32 *indexEntry;
    u32 *payload;
    u8 *packedTransform;

    dictionaryBase = resourceBase != 0 ? resourceBase + 0x40 : 0;
    outTransform->resourceIndex = recordIndex;

    if (dictionaryBase != 0) {
        indexEntry = GetTransformIndexEntry(dictionaryBase, recordIndex);
        if (indexEntry != 0) {
            packedTransform = dictionaryBase + *indexEntry;
            goto transform_found;
        }
    }
    packedTransform = 0;

transform_found:
    payload = (u32 *)(packedTransform + 4);
    if ((*(u16 *)packedTransform & 1) != 0) {
        MI_CpuFill8(&outTransform->translation, 0, 0xc);
    } else {
        outTransform->translation.x = payload[0];
        outTransform->translation.z = payload[1];
        outTransform->translation.y = -(int)payload[2];
        payload += 3;
    }

    if ((*(u16 *)packedTransform & 2) != 0) {
        MTX_Identity33_(&outTransform->rotation);
    } else {
        if ((*(u16 *)packedTransform & 8) != 0) {
            payload += 1;
        } else {
            short *matrixValues = (short *)payload;
            MTX_Identity33_(&outTransform->rotation);
            outTransform->rotation.m[1] = matrixValues[0];
            outTransform->rotation.m[2] = matrixValues[1];
            outTransform->rotation.m[3] = matrixValues[2];
            outTransform->rotation.m[4] = matrixValues[3];
            outTransform->rotation.m[5] = matrixValues[4];
            outTransform->rotation.m[6] = matrixValues[5];
            outTransform->rotation.m[7] = matrixValues[6];
            outTransform->rotation.m[8] = matrixValues[7];
            payload += 4;
        }
    }

    if ((*(u16 *)packedTransform & 4) != 0) {
        outTransform->scale.z = 0x1000;
        outTransform->scale.y = 0x1000;
        outTransform->scale.x = 0x1000;
        return;
    }
    outTransform->scale.x = payload[0];
    outTransform->scale.y = payload[1];
    outTransform->scale.z = payload[2];
}

