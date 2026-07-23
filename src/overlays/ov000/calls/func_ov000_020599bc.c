typedef unsigned short u16;

typedef struct Ov000RenderObject Ov000RenderObject;

typedef struct Ov000GlyphRun {
    u16 codes[5];
} Ov000GlyphRun;

extern void func_02030194(
    Ov000RenderObject *object,
    int x,
    int y,
    int depth,
    unsigned int code
);

asm void func_ov000_020599bc(
    Ov000RenderObject *object,
    const Ov000GlyphRun *run,
    int x,
    int y,
    int depth
) {
    dcd 0xe92d4ff8
    dcd 0xe59d6028
    dcd 0xe1a0a000
    dcd 0xe1a09001
    dcd 0xe1a08002
    dcd 0xe1a07003
    dcd 0xe3a04004
    dcd 0xe246b001
    dcd 0xe3540002
    dcd 0x03a00003
    dcd 0x13a00006
    dcd 0xe0488000
    dcd 0xe1a00084
    dcd 0xe19900b0
    dcd 0xe3a01000
    dcd 0xe3500034
    dcd 0x1350003a
    dcd 0x13a01001
    dcd 0xe3510000
    dcd 0x0a000004
    dcd 0xe3500031
    dcd 0x03a01002
    dcd 0x13a01001
    dcd 0xe0885001
    dcd 0xea000000
    dcd 0xe1a05008
    dcd 0xe58d0000
    dcd 0xe1a0000a
    dcd 0xe2851001
    dcd 0xe2872001
    dcd 0xe1a0300b
    bl func_02030194
    dcd 0xe1a01005
    dcd 0xe1a00084
    dcd 0xe19930b0
    dcd 0xe1a0000a
    dcd 0xe1a02007
    dcd 0xe58d3000
    dcd 0xe1a03006
    bl func_02030194
    dcd 0xe2544001
    dcd 0x5affffdd
    dcd 0xe8bd8ff8
}
