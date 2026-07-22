/* Seed the camera with its default framing: distance from the metrics helper,
 * height 1.0 and pitch 6.0, all in FX32, then raise the dirty bit.
 *
 * The global is RE-READ before every store rather than cached in a local -- four
 * separate loads in the ROM. Holding it costs the match here, which is the
 * mirror image of the usual held-pointer lever. */
extern int func_0201e438(void);

typedef struct {
    unsigned int dwFlags;   /* +0 */
    int fxPitch;            /* +4 */
    int fxDistance;         /* +8 */
    int fxHeight;           /* +0xc */
} Ov002CameraState;

extern Ov002CameraState *data_ov002_0207f600;

void func_ov002_0205193c(void) {
    data_ov002_0207f600->fxDistance = func_0201e438() << 12;
    data_ov002_0207f600->fxHeight = 1 << 12;
    data_ov002_0207f600->fxPitch = 6 << 12;
    data_ov002_0207f600->dwFlags |= 2;
}
