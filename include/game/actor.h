#ifndef GAME_ACTOR_H
#define GAME_ACTOR_H

/* The enemy actor: the object every enemy overlay (ov117..ov301) builds its enemies on and the
 * enemy framework (ov107) runs. This is the part they all share, 0x000..0x38b; each family keeps
 * its own fields after it (`struct { Actor base; ... }`).
 *
 * Names come from what the code does with a field: the handler slots from the functions the
 * constructors install in them and from the code that calls them. A field only named by its
 * offset (`field_XXX`) is used but not understood yet.
 *
 * Some fields are unions of the ways the code reads them: mwcc emits different code for a
 * halfword read and a bitfield read of the same flags, so each form the ROM needs is kept. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;

/* The collision sphere: centre and radius. */
typedef struct ActorSphere {
    VecFx32 center;                 /* 0x00 */
    fx32 radius;                    /* 0x0c */
} ActorSphere;

/* Scale, rotation and translation of the model, copied into its render nodes. */
typedef struct ActorSrt {
    fx32 rotation[4];               /* 0x00: quaternion */
    VecFx32 translation;            /* 0x10 */
    fx32 scale[3];                  /* 0x1c */
    u8 flags;                       /* 0x28 */
    u8 pad29[3];
} ActorSrt;

/* Axis-aligned bounds. */
typedef struct ActorBox {
    VecFx32 min;                    /* 0x00 */
    VecFx32 max;                    /* 0x0c */
} ActorBox;

/* A list kept sorted by key: List_InsertSorted links a new node before the first node of +0x04
 * with a larger key and counts it at +0x20. */
typedef struct ActorList {
    u8 pad00[4];
    void *pHead;                    /* 0x04 */
    u8 pad08[0x18];
    int count;                      /* 0x20 */
    u8 pad24[4];
} ActorList;

/* +0x060: the actor flags, read as a halfword or as its two bytes (bitfields of the halfword). */
typedef union ActorFlags60 {
    u16 raw;
    struct {
        u16 lo : 8;
        u16 hi : 8;
    } bits;
} ActorFlags60;

/* +0x17a / +0x17c: contact flags, whole or bit by bit. */
typedef union ActorContactFlags {
    u8 raw;
    struct {
        u8 bit0 : 1;
        u8 bit1 : 1;
        u8 bit2 : 1;
        u8 bit3 : 1;
        u8 bits4 : 4;
    } bits;
    struct {
        u8 bit0 : 1;
        u8 rest : 7;
    } head;
} ActorContactFlags;

struct Actor {
    u16 flags;                      /* 0x000 */
    u16 id;                         /* 0x002 */
    void *pScene;                   /* 0x004 */

    /* Handler slots, installed by each enemy's constructor. */
    void (*pfnDestroy)();           /* 0x008: tear the actor down */
    void (*pfnTick)();              /* 0x00c: per-frame update */
    void (*pfnPose)();              /* 0x010: set up / refresh the model pose */
    void (*pfnSetEnabled)();        /* 0x014: (actor, enabled) */
    void (*pfnSetVisible)();        /* 0x018: (actor, visible) */
    void (*pfnHandleMessage)();     /* 0x01c: (actor, message, arg) */
    void (*pfnSendStatus)();        /* 0x020 */
    void (*pfnPostMessage)();       /* 0x024: (actor, message, size) -- what others call */
    void (*pfnForwardEvent)();      /* 0x028 */
    void (*pfnNotify)();            /* 0x02c */
    void (*pfnCreateTask)();        /* 0x030: create the actor's registry entry / AI task */
    void (*pfnPostTick)();          /* 0x034 */
    void (*pfnConfigure)();         /* 0x038: (actor, size, data) */

    int taskList;                   /* 0x03c: the task list its AI tasks run in (game/ai_task.h) */
    u32 field_040;                  /* 0x040 */
    u8 pad044[0xc];
    int mode;                       /* 0x050 */
    int field_054;                  /* 0x054 */
    int field_058;                  /* 0x058 */
    int field_05c;                  /* 0x05c */
    ActorFlags60 flags60;           /* 0x060 */
    u16 field_062;                  /* 0x062 */
    int camera[4];                  /* 0x064 */
    ActorSphere sphere;             /* 0x074 */
    u8 pad084[0x18];
    void *pSubscribers;             /* 0x09c */
    ActorSrt srt;                   /* 0x0a0 */
    u8 padcc[0x24];
    VecFx32 vPendingMove;           /* 0x0f0 */
    VecFx32 field_0fc;              /* 0x0fc */
    u8 pad108[0xc];
    VecFx32 vContactNormal;         /* 0x114 */
    int field_120;                  /* 0x120 */
    VecFx32 vDirection;             /* 0x124 */
    int field_130;                  /* 0x130 */
    int field_134;                  /* 0x134 */
    int field_138;                  /* 0x138 */
    int field_13c;                  /* 0x13c */
    void *field_140;                /* 0x140 */
    ActorList list144;              /* 0x144 */
    VecFx32 field_16c;              /* 0x16c */
    s8 field_178;                   /* 0x178 */
    u8 field_179;                   /* 0x179 */
    ActorContactFlags contact17a;   /* 0x17a */
    u8 field_17b;                   /* 0x17b */
    ActorContactFlags contact17c;   /* 0x17c */
    u8 pad17d[3];
    VecFx32 field_180;              /* 0x180 */
    void *field_18c;                /* 0x18c */
    VecFx32 vChaseTarget;           /* 0x190 */
    u8 field_19c;                   /* 0x19c */
    u8 nLevel;                      /* 0x19d: an enemy's level (Ov107_AiState_LoadStats) */
    u8 field_19e;                   /* 0x19e */
    u8 field_19f;                   /* 0x19f */
    void *field_1a0;                /* 0x1a0 */
    u32 texAddr;                    /* 0x1a4: its texture's VRAM address (Ov107_PackTextureHandle) */
    void *field_1a8;                /* 0x1a8 */
    u16 field_1ac;                  /* 0x1ac */
    u16 flags1ae;                   /* 0x1ae */
    u16 field_1b0;                  /* 0x1b0 */
    u16 field_1b2;                  /* 0x1b2 */
    u8 kind;                        /* 0x1b4 */
    u8 pad1b5[7];
    int field_1bc;                  /* 0x1bc */
    int field_1c0;                  /* 0x1c0 */
    u8 flags1c4;                    /* 0x1c4 */
    u8 field_1c5;                   /* 0x1c5 */
    s8 state;                       /* 0x1c6: current action state */
    s8 nextState;                   /* 0x1c7: requested state, -1 when none */
    u8 field_1c8;                   /* 0x1c8 */
    s8 field_1c9;                   /* 0x1c9 */
    u8 pad1ca[2];
    void (*pfnAction)();            /* 0x1cc */
    void (*pfnOnHit)();             /* 0x1d0 */
    void (*pfnOnDefeat)();          /* 0x1d4 */
    void (*pfnSetAttackPower)();    /* 0x1d8: sets an attack's power (Ov107_SetAttackPower) */
    void (*pfnPlayAnim)();          /* 0x1dc */
    void (*pfnRequestSubState)();   /* 0x1e0 */
    void (*pfnRequestSubStateIfIdle)(); /* 0x1e4 */
    void (*pfnOnRetired)();         /* 0x1e8 */
    void (*pfnLoadStats)();         /* 0x1ec: loads the stats of a level (Ov107_AiState_LoadStats) */
    void (*pfnLoadMsUpRecord)();    /* 0x1f0: Ov107_LoadMsUpRecord */
    void (*pfnSetHomeAndReach)();   /* 0x1f4: Ov107_SetHomeAndReach, the spawner's */
    void *field_1f8;                /* 0x1f8 */
    ActorBox bounds;                /* 0x1fc */
    void *pAiState;                 /* 0x214: state block of the AI task +0x030 creates */
    s16 hitPointsCap;               /* 0x218 */
    s16 hitPoints;                  /* 0x21a */
    u8 pad21c[4];
    int field_220;                  /* 0x220 */
    int field_224;                  /* 0x224 */
    int field_228;                  /* 0x228 */
    ActorList list22c;              /* 0x22c */
    int field_254;                  /* 0x254 */
    int field_258;                  /* 0x258 */
    void *field_25c;                /* 0x25c */
    ActorList list260;              /* 0x260: Ov107_EnqueueValue queues values here */
    u8 pad288[4];
    u8 pad28c[0x30];                /* 0x28c: eight 6-byte hit slots */
    s16 field_2bc[8];               /* 0x2bc */
    void *field_2cc;                /* 0x2cc */
    u32 field_2d0;                  /* 0x2d0 */
    void *pSpawner;                 /* 0x2d4 */
    int range;                      /* 0x2d8 */
    s16 field_2dc;                  /* 0x2dc */
    s16 field_2de;                  /* 0x2de */
    int field_2e0;                  /* 0x2e0 */
    int field_2e4;                  /* 0x2e4 */
    int field_2e8;                  /* 0x2e8 */
    int field_2ec;                  /* 0x2ec */
    int field_2f0;                  /* 0x2f0 */
    int field_2f4;                  /* 0x2f4 */
    int field_2f8;                  /* 0x2f8 */
    VecFx32 field_2fc;              /* 0x2fc */
    int field_308;                  /* 0x308 */
    int field_30c;                  /* 0x30c */
    s8 mode310;                     /* 0x310 */
    ActorContactFlags flags311;     /* 0x311 */
    u8 pad312[2];
    u8 pad314[0x3c];                /* 0x314: five 12-byte thresholds */
    void *slots350[8];              /* 0x350 */
    s16 field_370[10];              /* 0x370 */
    void *pSubitem;                 /* 0x384 */
    void *pPoolEntry;               /* 0x388 */
};

#endif /* GAME_ACTOR_H */
