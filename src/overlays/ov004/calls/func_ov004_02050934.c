typedef unsigned short u16;
typedef struct { int x, y, z; } VecFx32;
typedef struct {
    unsigned char opaque000[0xa4];
    VecFx32 position;
    VecFx32 scale;
    unsigned char opaque0bc[0x48];
    u16 color;
    u16 opaque106;
} Ov004DigitGlyph;
typedef struct {
    int projection[4];
    int farPlane;
    VecFx32 target, pos, up;
} CamActor;
typedef struct {
    Ov004DigitGlyph digitGlyphs[10];
    int digitDrawCount;
    Ov004DigitGlyph *digitDrawGlyphs[6];
    VecFx32 digitDrawPositions[6];
    u16 digitDrawColors[6];
    CamActor digitCamera;
} Ov004Context;
extern Ov004Context *data_ov004_02051384;
extern void func_02023d70(CamActor *actor, int top, int bottom, int left, int right);
extern void func_0202afdc(Ov004DigitGlyph *glyph, u16 color);
extern void func_0202aa9c(Ov004DigitGlyph *glyph);

void func_ov004_02050934(void)
{
    int i;
    Ov004DigitGlyph *glyph;
    func_02023d70(&data_ov004_02051384->digitCamera, 0x3b33, -0x3b33, -0x4d9a, 0x4d9a);
    for (i = 0; i < data_ov004_02051384->digitDrawCount; i++) {
        glyph = data_ov004_02051384->digitDrawGlyphs[i];
        glyph->scale.x = glyph->scale.y = glyph->scale.z = 0x5e3;
        data_ov004_02051384->digitDrawGlyphs[i]->position = data_ov004_02051384->digitDrawPositions[i];
        func_0202afdc(data_ov004_02051384->digitDrawGlyphs[i], data_ov004_02051384->digitDrawColors[i]);
        func_0202aa9c(data_ov004_02051384->digitDrawGlyphs[i]);
    }
}

