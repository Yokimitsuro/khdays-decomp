typedef unsigned int uint;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern int func_0201653c(const VecFx32 *, int *, int *);
extern void VEC_Subtract(const VecFx32 *, const VecFx32 *, VecFx32 *);
extern int VEC_Mag(const VecFx32 *);
extern int func_01ff8d18(const VecFx32 *, VecFx32 *);
extern int VEC_DotProduct(const VecFx32 *, const VecFx32 *);
extern VecFx32 data_020475ac[];
extern VecFx32 data_020475c4;

int func_ov002_0204e2e0(uint *directionMask, const VecFx32 *position,
                        int horizontalMargin, int verticalMargin)
{
    int projectionResult;
    int screenX;
    int screenY;
    uint mask = 0;
    VecFx32 toPosition;
    VecFx32 viewDirection;
    uint cameraAddress = (uint)data_020475ac;

    projectionResult = func_0201653c(position, &screenX, &screenY);
    VEC_Subtract(position, (const VecFx32 *)cameraAddress, &toPosition);
    VEC_Subtract(&data_020475c4, (const VecFx32 *)cameraAddress, &viewDirection);
    if (VEC_Mag(&toPosition) != 0) {
        func_01ff8d18(&toPosition, &toPosition);
    }
    if (VEC_Mag(&viewDirection) != 0) {
        func_01ff8d18(&viewDirection, &viewDirection);
    }
    if (VEC_DotProduct(&viewDirection, &toPosition) < 0) {
        screenX = -screenX;
        screenY = -screenY;
        projectionResult = -1;
    }
    if (0xff - horizontalMargin < screenX) {
        mask |= 2;
        projectionResult = -1;
    }
    if (horizontalMargin > screenX) {
        mask |= 1;
        projectionResult = -1;
    }
    if (verticalMargin > screenY) {
        mask |= 4;
        projectionResult = -1;
    }
    if (0xc0 - verticalMargin < screenY) {
        mask |= 8;
        mask |= screenX < 0x80 ? 1 : 2;
        projectionResult = -1;
    }
    *directionMask = mask;
    return projectionResult != -1;
}
