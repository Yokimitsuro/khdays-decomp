/* Draw handler for a script entity. Nothing is drawn until the entity has been
 * bound, and nothing is drawn while the shared ov022 slot reports -1.
 *
 * It swaps in the entity's own camera, set to an orthographic box of
 * +/-0x3b33 by +/-0x4d9a -- a 4:3 ratio, the screen's -- renders the scene
 * node into the context the ov002 getter returned, then restores the camera the
 * scene had. The result is always 0.
 */
struct Ov020Entity {
    char pad00[0x12];
    unsigned short hBindFlags12;            /* 0x12 */
    char pad14[8];
    unsigned short aNode1c[1];              /* 0x1c */
    char pad1e[0x106];
    char aCamera124[4];                     /* 0x124 */
};

extern void *func_ov002_0207687c(void);
extern int func_ov022_02083f0c(void);
extern void *func_ov002_0204cb68(void);
extern void func_02023d70(void *camera, int top, int bottom, int left, int right);
extern void func_0202a818(unsigned short *node, void *context);
extern void func_0202aa9c(unsigned short *node);
extern void func_02023cc0(void *camera);

int func_ov020_0207fbdc(struct Ov020Entity *entity)
{
    void *context;
    void *scene_camera;

    context = func_ov002_0207687c();
    if ((entity->hBindFlags12 & 4) != 0) {
        if (func_ov022_02083f0c() == -1) {
            return 0;
        }

        scene_camera = func_ov002_0204cb68();
        func_02023d70(entity->aCamera124, 0x3b33, -0x3b33, -0x4d9a, 0x4d9a);
        func_0202a818(entity->aNode1c, context);
        func_0202aa9c(entity->aNode1c);
        func_02023cc0(scene_camera);
    }
    return 0;
}
