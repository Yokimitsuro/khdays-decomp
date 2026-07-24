typedef unsigned char  u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov000TileAsset {
    u8 pad_0000[8];
    const u16 *tiles;
} Ov000TileAsset;

typedef struct Ov000TileBlitRequest {
    u8 pad_0000[2];
    s16 destinationX;
    s16 destinationY;
    u16 sourceX;
    u16 sourceY;
    s16 width;
    s16 height;
    u8 pad_000e[2];
    int bufferHandle;
    u8 pad_0014[4];
    const Ov000TileAsset *asset;
} Ov000TileBlitRequest;

typedef struct Ov000SceneContext {
    u8 pad_0000[0x4afa];
    u8 tileDirtyFlags;
} Ov000SceneContext;

extern Ov000SceneContext *volatile data_ov000_0205ac24;
extern u16 *func_ov000_02053088(int handle, int *bufferIndex);
extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);
extern void MIi_CpuClear16(int value, void *destination, u32 size);

asm void func_ov000_020530cc(
    const Ov000TileBlitRequest *request,
    int copySource
) {
    dcd 0xe92d4ff0
    dcd 0xe24dd00c
    dcd 0xe1a0a000
    dcd 0xe59a0010
    dcd 0xe1a04001
    dcd 0xe28d1008
    bl func_ov000_02053088
    dcd 0xe59a2018
    dcd 0xe1da10fa
    dcd 0xe5925008
    dcd 0xe3e02000
    dcd 0xe1d530b0
    dcd 0xe1a06000
    dcd 0xe1da90fc
    dcd 0xe1a001a3
    dcd 0xe1510002
    dcd 0xe58d0004
    dcd 0x01a01000
    dcd 0xe3e00000
    dcd 0xe1590000
    dcd 0x01d500b2
    dcd 0xe1dab0b6
    dcd 0xe1da50b8
    dcd 0x01a091a0
    dcd 0xe1da00f2
    dcd 0xe3500000
    dcd 0xa1a00800
    dcd 0xa1a07820
    dcd 0xaa000002
    dcd 0xe04bb000
    dcd 0xe0811000
    dcd 0xe3a07000
    dcd 0xe0870001
    dcd 0xe3500020
    dcd 0xc2400020
    dcd 0xc0411000
    dcd 0xe1da00f4
    dcd 0xe3500000
    dcd 0xa1a00800
    dcd 0xa1a08820
    dcd 0xaa000002
    dcd 0xe0455000
    dcd 0xe0899000
    dcd 0xe3a08000
    dcd 0xe0880009
    dcd 0xe3500018
    dcd 0xc2400018
    dcd 0xc0499000
    dcd 0xe3540000
    dcd 0x0a000014
    dcd 0xe3590000
    dcd 0xe3a04000
    dcd 0xda00001f
    dcd 0xe1a00081
    dcd 0xe58d0000
    dcd 0xe59d0004
    dcd 0xe0851004
    dcd 0xe023b190
    dcd 0xe59a0018
    dcd 0xe0871288
    dcd 0xe5900008
    dcd 0xe59d2000
    dcd 0xe280000c
    dcd 0xe0800083
    dcd 0xe0861081
    bl MIi_CpuCopy16
    dcd 0xe2844001
    dcd 0xe1540009
    dcd 0xe2888001
    dcd 0xbafffff0
    dcd 0xea00000d
    dcd 0xe3590000
    dcd 0xe3a0a000
    dcd 0xda00000a
    dcd 0xe1a05081
    dcd 0xe1a0400a
    dcd 0xe0871288
    dcd 0xe1a00004
    dcd 0xe1a02005
    dcd 0xe0861081
    bl MIi_CpuClear16
    dcd 0xe28aa001
    dcd 0xe15a0009
    dcd 0xe2888001
    dcd 0xbafffff6
    dcd 0xe59f0020
    dcd 0xe59d1008
    dcd 0xe5900000
    dcd 0xe3a02001
    dcd 0xe2800901
    dcd 0xe5d03afa
    dcd 0xe1831112
    dcd 0xe5c01afa
    dcd 0xe28dd00c
    dcd 0xe8bd8ff0
    dcd data_ov000_0205ac24
}
