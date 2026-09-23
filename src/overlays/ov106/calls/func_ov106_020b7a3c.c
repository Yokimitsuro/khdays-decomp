/* Interaction check of the ov106 scene: unless the scene is paused (field 0x248c clear while a player
 * is selected), with the ov022 camera, the ov002 scene, a player actor and its controller ready and
 * the selected player's entity present, an actor that is not free to act (ov022 02086620/02086888) is
 * left alone; otherwise its prompt is shown when the entity may act on its target (020b79dc), or hidden
 * while the prompt is up. */
typedef unsigned char u8;

extern int func_02023588(int flag);
extern u8 data_0204be04;
extern int func_ov022_02083f0c(void);
extern int func_ov002_0204cb18(void);
extern int func_ov022_02083f5c(void);
extern int func_ov022_02088338(void);
extern void *func_01fffde0(int nPlayer);
extern int func_ov022_02086620(int nHandle);
extern int func_ov022_02086888(int nHandle);
extern void func_ov022_02086834(int nHandle, int show);
extern int func_ov106_020b79dc(void *entity);

void func_ov106_020b7a3c(void)
{
    int actor;
    void *entity;

    if (func_02023588(0x248c) == 0 && data_0204be04 != 0) {
        return;
    }
    if (func_ov022_02083f0c() == 0) {
        return;
    }
    if (func_ov002_0204cb18() == 0) {
        return;
    }
    if ((actor = func_ov022_02083f5c()) == 0) {
        return;
    }
    if (func_ov022_02088338() == 0) {
        return;
    }
    if ((entity = func_01fffde0(data_0204be04)) == 0) {
        return;
    }
    if (func_ov022_02086620(actor) != 0 && func_ov022_02086888(actor) == 0) {
        return;
    }
    if (func_ov106_020b79dc(entity) != 0) {
        func_ov022_02086834(actor, 1);
    } else if (func_ov022_02086888(actor) != 0) {
        func_ov022_02086834(actor, 0);
    }
}
