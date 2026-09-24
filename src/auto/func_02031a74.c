/* func_02031a74 -- append one OAM entry (attr01 + attr2) to the object's bounded OAM buffer
 * (count +0x4630, capacity +0x462c, 8-byte entries from +0x4638). Returns TRUE when stored. */
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;

typedef struct {
    u32 attr01;
    u16 attr2;
    u16 _3;
} GXOamAttr;

typedef struct DispOamBuffer {
    char pad0000[0x462c];
    int capacity;               /* +0x462c */
    int count;                  /* +0x4630 */
    int pad4634;
    GXOamAttr oams[1];          /* +0x4638 */
} DispOamBuffer;

BOOL func_02031a74(DispOamBuffer *buf, const GXOamAttr *oam)
{
    BOOL result = 0;
    int count = buf->count;

    if (count < buf->capacity) {
        buf->oams[count].attr01 = oam->attr01;
        buf->oams[count].attr2 = oam->attr2;
        buf->count++;
        result = 1;
    }
    return result;
}
