#include "nitro/types.h"
#include "nitro/fx_types.h"

#include "game/class_descriptor.h"
/* main .rodata 0x0204208c-0x02042124: NNS G3D material masks, matrix/quaternion helper constants
 * and the class descriptor of the session's transfer-channel task. */

typedef struct VecFx16 {
    fx16 x, y, z;
    fx16 pad;
} VecFx16;

/* Quaternion as the game stores it: w first, then the vector part. */
typedef struct Quat {
    fx32 w, x, y, z;
} Quat;

extern void ContextEntry_Set(void);
extern void func_0203123c(void);
extern int data_0204c024;

/* NitroSystem G3D material SBC (NNSi_G3dFuncSbc_MAT): the diffuse/ambient colour-field mask selected by
 * the material's three flag bits. */
const u32 data_0204208c[8] = {
    0x00000000, 0x00007fff, 0x7fff0000, 0x7fff7fff,
    0x00008000, 0x0000ffff, 0x7fff8000, 0x7fffffff,
};

/* For each element of a 3x3 matrix, the four element indices (row-major) of its 2x2 minor:
 * the cofactor walk of the 3x3 inverse (func_01ffae5c, NNSi_G3dFuncSbc_NODEDESC, NNSi_G3dGetMdlRot). */
const u8 data_020420ac[9][4] = {
    { 4, 5, 7, 8 }, { 3, 5, 6, 8 }, { 3, 4, 6, 7 },
    { 1, 2, 7, 8 }, { 0, 2, 6, 8 }, { 0, 1, 6, 7 },
    { 1, 2, 4, 5 }, { 0, 2, 3, 5 }, { 0, 1, 3, 4 },
};

/* The unit Y axis as a VecFx16 (RoomPoly_BuildPlanesVertical). */
const VecFx16 data_020420d0 = { 0, 0x1000, 0, 0 };

/* Rotation quaternion {w 0, x sqrt(1/2), y sqrt(1/2), z 0}: half a turn about the (1, 1, 0)
 * diagonal, applied by Mtx33_ApplyFixedRotation. */
const Quat data_020420d8 = { 0, 0xb50, 0xb50, 0 };

/* The -Z unit vector (CamAnim_ApplyPosition). */
const VecFx32 data_020420e8 = { 0, 0, -0x1000 };

/* Cyclic successor of each axis {1, 2, 0} for the matrix-to-quaternion conversion
 * (Quat_FromMtx33, j/k from i). */
const u8 data_020420f4[4] = { 1, 2, 0, 0 };

/* The identity quaternion {w 1.0, 0, 0, 0}: default orientation of transforms and rigs. */
const Quat data_020420f8 = { 0x1000, 0, 0, 0 };

/* Handle ids patched into the transfer descriptor for its two channels (MsgQueue_Init_2). */
const int data_02042108[2] = { 15, 17 };

/* Class descriptor of the transfer-channel task MsgQueue_Init_2 instantiates twice
 * (InstantiateClass): class 2, group 0xf, constructor 02031228, method 0203123c, a 4-byte state,
 * arena data_0204c024. */
const GameClassDescriptor data_02042110 = {
    2, 0xf, ContextEntry_Set, func_0203123c, 4, &data_0204c024,
};
