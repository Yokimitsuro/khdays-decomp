typedef unsigned char u8;
typedef unsigned int u32;
typedef void (*Ov000StateFn)(void);

typedef struct Ov000RowDescriptor {
    int displayValue;
    u8 pad_0004[0x14];
} Ov000RowDescriptor;

typedef struct Ov000StreamOpenParams {
    void *resource;
    int enabled;
} Ov000StreamOpenParams;

typedef struct Ov000StreamInterface {
    void (*initialize)(void);
    void (*open)(const Ov000StreamOpenParams *params);
    void (*unused08)(void);
    void (*start)(void);
} Ov000StreamInterface;

typedef struct Ov000MovieFrame {
    char formatted[0x10];
    Ov000StreamOpenParams openParams;
    char path[0x80];
} Ov000MovieFrame;

typedef struct Ov000SceneContext {
    short secondValue;
    short selectedRow;
    u8 pad_0004[0x9674];
    Ov000RowDescriptor rows[18];
    u8 pad_9828[0x392c];
    void *resource;
    Ov000StreamInterface stream;
} Ov000SceneContext;

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern int OS_SPrintf(char *destination, const char *format, ...);
extern char data_ov000_0205abf8[];
extern void func_ov000_02059f50(void);
extern Ov000SceneContext *data_ov000_0205ac3c;
extern int func_020235a8(int handlerId);
extern void func_02020a90(int value);
extern void func_0201e470(int processor, int overlayId);
extern char data_ov000_0205ac00[];
extern void *func_02024ee8(const void *descriptor, int mode);
extern void func_0201f924(char *destination, const char *source);
extern void func_ov024_020832c4(Ov000StreamInterface *stream);
extern void func_ov000_0205a554(void);

asm Ov000StateFn func_ov000_0205a3e0(void) {
    dcd 0xe92d4010
    dcd 0xe24dd098
    bl NNSi_FndGetCurrentRootHeap
    dcd 0xe1a04000
    dcd 0xe1d420f2
    dcd 0xe3a01018
    dcd 0xe28d0000
    dcd 0xe1014182
    dcd 0xe2811a09
    dcd 0xe5912678
    dcd 0xe59f1094
    bl OS_SPrintf
    bl func_ov000_02059f50
    dcd 0xe59f108c
    dcd 0xe59f008c
    dcd 0xe5814000
    bl func_020235a8
    dcd 0xe3a00c01
    bl func_02020a90
    dcd 0xe59f107c
    dcd 0xe3a00000
    bl func_0201e470
    dcd 0xe59f0074
    dcd 0xe3a0100f
    bl func_02024ee8
    dcd 0xe2841a0d
    dcd 0xe5810154
    dcd 0xe58d0010
    dcd 0xe3a00001
    dcd 0xe58d0014
    dcd 0xe28d0018
    dcd 0xe28d1000
    bl func_0201f924
    dcd 0xe2840f56
    dcd 0xe2800a0d
    bl func_ov024_020832c4
    dcd 0xe2840a0d
    dcd 0xe5900158
    dcd 0xe12fff30
    dcd 0xe2841a0d
    dcd 0xe591115c
    dcd 0xe28d0010
    dcd 0xe12fff31
    dcd 0xe2840a0d
    dcd 0xe5900164
    dcd 0xe12fff30
    dcd 0xe59f0018
    dcd 0xe28dd098
    dcd 0xe8bd8010
    dcd data_ov000_0205abf8
    dcd data_ov000_0205ac3c
    dcd 0x000020e9
    dcd 0x00000018
    dcd data_ov000_0205ac00
    dcd func_ov000_0205a554
}
