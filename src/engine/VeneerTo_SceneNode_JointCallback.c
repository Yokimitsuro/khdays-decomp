/* Interworking tail-call veneer (`ldr ip,[pc] ; bx ip`): forwards to SceneNode_JointCallback. */
extern void *SceneNode_JointCallback();

void *VeneerTo_SceneNode_JointCallback(void *rs) {
    return SceneNode_JointCallback(rs);
}
