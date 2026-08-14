typedef unsigned short u16;
typedef struct { int x, y, z; } VecFx32;
typedef struct { void *node; int pad; } Slot;
typedef struct { int w[5]; } KindTable;
typedef struct { int w[6]; } ParamBlock;
typedef struct { VecFx32 v; int w; } SpawnSeed;

extern void *func_ov107_020c9440(void *self, int slot);
extern void *func_0203b898(void *res);
extern void func_0203bfb4(void *list, void *node);
extern void func_0202a388(void *dst, void *a, void *b, int n);
extern void func_0203b9ac(void *obj, void *block);
extern int func_0203bdfc(void *obj, const char *name);
extern void func_0203c7ac(void *obj, int a);
extern void func_ov107_020c92b0(void *self, int a, int b, const VecFx32 *v, int e);
extern void *OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov107_020c9074(void *self, void *obj);
extern void *func_0203c1b0(void *res, int n);
extern void *func_ov264_020ce9fc(void *self);
extern void *func_01fffca8(void *list, int size, int count);
extern void *func_ov107_020c319c(const SpawnSeed *seed);
extern void func_0203355c(int id);

extern KindTable data_ov264_020cebc4;
extern const char data_ov264_020cec2c[];
extern const char data_ov264_020cec38[];
extern const VecFx32 data_02041dc8;

extern void func_ov264_020cbfc8(void);
extern void func_ov264_020cc09c(void);
extern void func_ov264_020cc5c4(void);
extern void func_ov264_020cc61c(void);
extern void func_ov264_020cc6a8(void);
extern void func_ov264_020cca58(void);
extern void func_ov264_020cc8e4(void);
extern void func_ov264_020ccab4(void);
extern void func_ov264_020cc9e0(void);
extern void func_ov264_020ccde8(void);
extern void func_ov264_020cce14(void);