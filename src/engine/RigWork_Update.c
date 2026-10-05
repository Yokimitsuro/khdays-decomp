/* Per-frame update of a camera/actor rig workspace: publishes the shared matrix pointer
 * (data_02042510) to the render state (+0xe8), samples the +8 source's two frames (NNSi_G3dAnmCalcNsBca
 * 0 and 1) into the down-direction (CamAnim_ApplyPosition) and anchor (CamAnim_ApplyFovy) stages, refreshes the
 * +0x10 block (Camera_CommitMatrices) and finishes with AnimStream_Advance. */
typedef struct {
    char data[0x58];
} Frame;

extern int data_02042510;
extern char *NNS_G3dRS;
extern void NNSi_G3dAnmCalcNsBca(Frame *out, int src, int which);
extern void CamAnim_ApplyPosition(char *self, Frame *src);
extern void CamAnim_ApplyFovy(char *self, Frame *src);
extern void Camera_CommitMatrices(void *block);
extern void AnimStream_Advance(char *self, int arg);

void RigWork_Update(char *self, int arg)
{
    Frame second;
    Frame first;

    *(int *)(NNS_G3dRS + 0xe8) = data_02042510;
    NNSi_G3dAnmCalcNsBca(&first, *(int *)(self + 8), 0);
    NNSi_G3dAnmCalcNsBca(&second, *(int *)(self + 8), 1);
    CamAnim_ApplyPosition(self, &first);
    CamAnim_ApplyFovy(self, &second);
    Camera_CommitMatrices(self + 0x10);
    AnimStream_Advance(self, arg);
}
