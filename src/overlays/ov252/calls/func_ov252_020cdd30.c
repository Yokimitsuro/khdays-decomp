/* Light (`lit`) or dim armour marker `i` of the ov252 actor: lit hides its +0x38c model (+0x5c bit 1),
 * shows its +0x4f4 shape and sets bit 0 of its +0x518 record's high nibble; dim does the reverse and
 * the actor plays effect 0xb at the marker's +0x53c anchor. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;
typedef struct { u8 lo : 4; u8 hi : 4; } NibblePair;
struct Ov252Body {
    char pad[0x38c];
    int models[4];
    char pad39c[0x4f4 - 0x39c];
    int shapes[4];
    char pad504[0x518 - 0x504];
    NibblePair *records[4];
    char pad528[0x53c - 0x528];
    int anchors[4];
};

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);

void func_ov252_020cdd30(int *state, int i, int lit)
{
    if (lit != 0) {
        *(int *)(((struct Ov252Body *)*state)->models[i] + 0x5c) &= ~2;
        ((B8 *)(((struct Ov252Body *)*state)->shapes[i] + 8))->f |= 1;
        ((struct Ov252Body *)*state)->records[i]->hi |= 1;
    } else {
        *(int *)(((struct Ov252Body *)*state)->models[i] + 0x5c) |= 2;
        ((B8 *)(((struct Ov252Body *)*state)->shapes[i] + 8))->f &= ~1;
        ((struct Ov252Body *)*state)->records[i]->hi &= ~1;
        func_ov107_020c0b90(*state, 0xb, *(Vec3 *)(((struct Ov252Body *)*state)->anchors[i] + 0x14), 0);
    }
}
