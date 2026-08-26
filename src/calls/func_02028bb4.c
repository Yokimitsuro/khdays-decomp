typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef union CollisionRelPtr {
    u32 offset;
    void *pointer;
} CollisionRelPtr;

typedef struct CollisionTreeNode CollisionTreeNode;

typedef union CollisionNodeRef {
    int index;
    CollisionTreeNode *pointer;
} CollisionNodeRef;

struct CollisionTreeNode {
    u8 data00[0xc];
    CollisionNodeRef link0c;
    CollisionNodeRef children10[4];
};

typedef struct CollisionFace88 {
    u8 data[0x88];
} CollisionFace88;

typedef struct CollisionFace84 {
    u8 data[0x84];
} CollisionFace84;

typedef struct CollisionModelBlob {
    u32 runtime00;
    u32 runtime04;
    u32 runtime08;
    u32 runtime0c;
    u8 data10[0x64];
    u16 flags74;
    u16 field76;
    u16 pointerCount78;
    u16 nodeCount7a;
    u16 face88Count7c;
    u16 face84Count7e;
    u16 face84Count80;
    u16 namedRecordCount82;
    u8 data84[0x10];
    CollisionRelPtr field94;
    CollisionRelPtr pointerTable98;
    CollisionRelPtr treeRoot9c;
    CollisionRelPtr modelDataA0;
    CollisionRelPtr faces84A4;
    CollisionRelPtr faces84A8;
    CollisionRelPtr namedRecordsAc;
} CollisionModelBlob;

extern void func_02028a64(CollisionModelBlob *, CollisionFace88 *);
extern void func_02028924(CollisionModelBlob *, CollisionFace84 *);

int func_02028bb4(CollisionModelBlob *blob)
{
    int i;
    int nodeAddress;
    int resolvedAddress;
    int j;
    int byteOffset;
    int nodeOffset;
    int childIndex;
    int invalidIndex;
    int nullAddress;

    if ((blob->flags74 & 0x8000) == 0) {
        blob->field94.pointer = (u8 *)blob + blob->field94.offset;
        blob->pointerTable98.pointer = (u8 *)blob + blob->pointerTable98.offset;

        i = 0;
        if (i < blob->pointerCount78) {
            byteOffset = 0;
            do {
                CollisionRelPtr *entry =
                    (CollisionRelPtr *)((u8 *)blob->pointerTable98.pointer + byteOffset);
                i++;
                entry->pointer = (u8 *)blob + entry->offset;
                byteOffset += 4;
            } while (i < blob->pointerCount78);
        }

        blob->treeRoot9c.pointer = (u8 *)blob + blob->treeRoot9c.offset;
        blob->modelDataA0.pointer = (u8 *)blob + blob->modelDataA0.offset;
        blob->faces84A4.pointer = (u8 *)blob + blob->faces84A4.offset;
        blob->faces84A8.pointer = (u8 *)blob + blob->faces84A8.offset;
        blob->namedRecordsAc.pointer = (u8 *)blob + blob->namedRecordsAc.offset;

        i = 0;
        if (i < blob->face88Count7c) {
            byteOffset = 0;
            do {
                func_02028a64(blob,
                              (CollisionFace88 *)((u8 *)blob->modelDataA0.pointer + byteOffset));
                i++;
                byteOffset += 0x88;
            } while (i < blob->face88Count7c);
        }

        i = 0;
        if (i < blob->face84Count7e) {
            byteOffset = 0;
            do {
                func_02028924(blob,
                              (CollisionFace84 *)((u8 *)blob->faces84A4.pointer + byteOffset));
                i++;
                byteOffset += 0x84;
            } while (i < blob->face84Count7e);
        }

        i = 0;
        if (i < blob->face84Count80) {
            byteOffset = 0;
            do {
                func_02028924(blob,
                              (CollisionFace84 *)((u8 *)blob->faces84A8.pointer + byteOffset));
                i++;
                byteOffset += 0x84;
            } while (i < blob->face84Count80);
        }

        i = 0;
        if (i < blob->nodeCount7a) {
            nodeOffset = i;
            nullAddress = i;
            invalidIndex = i - 1;
            do {
                nodeAddress = (int)blob->treeRoot9c.pointer + nodeOffset;
                j = 0;
                byteOffset = nodeAddress;

                do {
                    childIndex = *(int *)(byteOffset + 0x10);
                    if (childIndex != invalidIndex) {
                        resolvedAddress = (int)blob->treeRoot9c.pointer + childIndex * 0x20;
                    } else {
                        resolvedAddress = nullAddress;
                    }
                    j++;
                    *(int *)(byteOffset + 0x10) = resolvedAddress;
                    byteOffset += 4;
                } while (j < 4);

                childIndex = *(int *)(nodeAddress + 0xc);
                if (childIndex != invalidIndex) {
                    resolvedAddress =
                        (int)blob->treeRoot9c.pointer + childIndex * 0x20;
                } else {
                    resolvedAddress = nullAddress;
                }
                *(int *)(nodeAddress + 0xc) = resolvedAddress;

                i++;
                nodeOffset += 0x20;
            } while (i < blob->nodeCount7a);
        }

        blob->runtime08 = 0;
        blob->runtime04 = 0;
        blob->runtime00 = 0;
        blob->runtime0c = 0;
        blob->flags74 |= 0x8000;
        blob->flags74 |= 0x4000;
    }

    return 1;
}
