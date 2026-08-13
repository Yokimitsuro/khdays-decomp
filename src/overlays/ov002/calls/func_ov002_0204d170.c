typedef unsigned int uint;
typedef unsigned short ushort;
typedef long long longlong;
typedef unsigned long long ulonglong;
typedef unsigned long long undefined8;
typedef unsigned int undefined4;
typedef unsigned short undefined2;
typedef int bool;
#define false 0
#define true 1
typedef struct { short nSin; short nCos; } FxSinCos;
typedef struct { int x; int y; int z; } VecFx32;
typedef struct {
  unsigned short x;
  unsigned short y;
  unsigned short kind;
  unsigned short state;
} Ov002RequestTuple;

typedef void (*Ov002NextFn)(void);

typedef struct {
  unsigned char unknown00[0x80];
  unsigned short angle;
} Ov002AngleSource;

typedef union {
  int words[0x40];
  struct {
    unsigned char unknown00[0x38];
    unsigned int flags;
    unsigned char unknown3c[0x68];
    int defaultSpeedX;
    int speedX;
    int speedY;
    unsigned char unknownb0[0x34];
    int minimumSpeed;
    int minimumSpeedX;
    int minimumSpeedY;
    unsigned int directionMask;
    Ov002RequestTuple request;
  } fields;
} Ov002WorldState;

typedef struct {
  unsigned long long flags;
  unsigned char unknown08[4];
  int kind;
  unsigned char unknown10[0x10];
  Ov002AngleSource *angleSource;
  unsigned char unknown24[0x2688];
  int heightBase;
} Ov022Entry;

static inline int FX_Mul(int a, int b)
{
  return (int)(((long long)a * b + 0x800) >> 12);
}

extern void *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov022_02083f5c(void);
extern unsigned short func_01fffe14(void);
extern void *func_ov022_020881f8(void);
extern Ov022Entry *func_01fffde0(uint);
extern int func_ov022_020881d8(void);
extern int func_ov022_02088338(void);
extern int func_ov002_02050a08(void);
extern int func_020208e0(void);
extern short func_02030788(void);
extern int func_02023c40(void);
extern unsigned long long func_ov022_02088314(uint);
extern void func_ov002_0204d0e0(void);
extern void func_ov002_0204d12c(void);
extern short func_02020a9c(void);
extern ushort *func_ov002_02057560(ushort *);
extern int FX_Inv(int,int);
extern void func_01ff8d18(uint *, int *);
extern void VEC_Subtract(int *,int *,int *);
extern uint VEC_DotProduct(int *,int *);
extern int func_ov022_02088d04(void);
extern void func_ov022_02088280(uint, int);
extern int func_ov002_02050b90(int);
extern int func_ov002_02050a54(int);
extern uint func_020235d0(int,int);
extern int func_ov002_02050b68(int);
extern int func_ov022_02088254(uint);
extern int func_ov022_020886d0(uint);
extern int func_ov022_02086620(undefined4);
extern void func_ov002_0204eee0(int *,uint *,int *,undefined4 *,int,int,int);
extern int func_02023bf0(void);
extern void func_ov002_0204ff18(int);
extern void func_ov002_0204fc54(void);
extern void func_ov002_0204f0a8(void);
extern void func_ov002_0204f7d4(void);
extern void func_ov002_0204fdc4(void);
extern unsigned char data_0204be04;
extern unsigned short data_0204c18c;
extern unsigned short data_0204c190;
extern unsigned char data_0204c240;
extern const short data_0203d210[];


/* WARNING: Removing unreachable block (ram,0x0204d280) */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

#pragma opt_dead_assignments off
Ov002NextFn func_ov002_0204d170(void)

{
  const short *pFVar3;
  ushort uVar4;
  undefined2 uVar1;
  longlong lVar2;
  short sVar5;
  short sVar6;
  uint uVar15;
  uint uVar14;
  register Ov002WorldState *state =
      (Ov002WorldState *)NNSi_FndGetCurrentRootHeap();
#define piVar7 state->words
  Ov002NextFn local_5c;
  undefined4 uVar8;
  undefined4 *puVar9;
  int iVar11;
  int iVar12;
  ushort *puVar13;
  uint uVar16;
  int iVar17;
  undefined4 extraout_r1;
  uint uVar18;
  int *piVar19;
  uint uVar20;
  uint idx;
  Ov022Entry *puVar10;
  bool bVar21;
  bool bVar22;
  undefined8 uVar23;
  uint uVar24;
  Ov002RequestTuple request;
  VecFx32 direction;
  VecFx32 delta;

  local_5c = 0;
  uVar8 = func_ov022_02083f5c();
  uVar20 = 0;
  uVar4 = func_01fffe14();
  idx = (uint)uVar4;
  puVar9 = (undefined4 *)func_ov022_020881f8();
  puVar10 = func_01fffde0(idx);
  uVar18 = piVar7[0x38];
  if (data_0204be04 != uVar18) {
    return 0;
  }
  if ((piVar7[0xe] & 4U) != 0) {
    return 0;
  }
  iVar11 = func_ov022_020881d8();
  sVar6 = (short)uVar18;
  if (iVar11 != 0) {
    return 0;
  }
  iVar11 = func_ov022_02088338();
  if (iVar11 == 0) {
    return 0;
  }
  uVar18 = func_ov002_02050a08();
  piVar7[0x29] = uVar18;
  uVar18 = func_ov002_02050a08();
  piVar7[0x2a] = uVar18;
  uVar18 = func_ov002_02050a08();
  piVar7[0x2b] = uVar18;
  iVar11 = func_020208e0();
  if ((iVar11 == 2) && (sVar5 = func_02030788(), sVar5 == 0))
  goto LAB_arm9_ov002__0204d9ac;
  bVar22 = false;
  if ((piVar7[0xf] & 0x20U) == 0) {
    if ((data_0204c18c & 0x100) != 0) {
      func_02023c40();
      iVar11 = func_02023c40() == 1;
      if (piVar7[0x36] + iVar11 != 0) {
        iVar11 = 0xcc;
      } else {
        iVar11 = 0x88;
      }
      if (iVar11 < 0) {
        iVar12 = 0;
      } else {
        iVar11 = func_02023c40() == 1;
        if (piVar7[0x36] + iVar11 != 0) {
          iVar12 = 0xcc;
        } else {
          iVar12 = 0x88;
        }
      }
      piVar7[0x36] += iVar12;
      if (0x800 < piVar7[0x36]) {
        if ((piVar7[0xf] & 1U) != 0) {
          piVar7[0xe] = piVar7[0xe] & 0xefffffff;
        }
        else {
          piVar7[0xe] = piVar7[0xe] | 0x10000000;
        }
      }
    } else {
      if ((piVar7[0xf] & 1U) != 0) {
        piVar7[0xe] = piVar7[0xe] | 0x10000000;
      }
      else {
        piVar7[0xe] = piVar7[0xe] & 0xefffffff;
      }
    }
  }
  if (((piVar7[0xe] & 0x200U) == 0 &&
       (data_0204c190 & 4) != 0 &&
       data_0204be04 == 0 &&
       (func_ov022_02088314(idx) & 0x400) == 0) ||
      (data_0204be04 != 0 && piVar7[0x3f] != 0)) {
    if ((piVar7[0xe] & 0x2000U) != 0) {
      bVar22 = true;
    } else if ((piVar7[0xe] & 0x10000U) != 0) {
      bVar22 = true;
    } else {
      piVar7[0xe] |= 0x2800;
      func_ov002_0204d0e0();
    }
  } else if ((func_ov022_02088314(idx) & 0x400) != 0 ||
             ((piVar7[0xe] & 0x2000U) != 0 &&
              (data_0204c190 & 0xf03) != 0)) {
    bVar22 = true;
  }
  if (bVar22) {
    func_ov002_0204d12c();
  }
  if ((piVar7[0xe] & 0x2000U) == 0)
    goto request_input;
  uVar4 = data_0204c18c;
  if ((uVar4 & 0x40) != 0) {
    uVar20 |= 2;
  } else if ((uVar4 & 0x80) != 0) {
    uVar20 |= 1;
  }
  if ((uVar4 & 0x20) != 0) {
    uVar20 |= 8;
  } else if ((uVar4 & 0x10) != 0) {
    uVar20 |= 4;
  }
  goto input_done;
request_input:
  {
    sVar5 = func_02020a9c();
    if (sVar5 == 0x2a)
      goto request_invalid;
    puVar13 = func_ov002_02057560(&request.x);
    if (puVar13 == (ushort *)0x0)
      goto request_invalid;
    {
      if (state->fields.request.kind == 1 &&
          state->fields.request.state == 0 &&
          request.kind == 1 && request.state == 0) {
        uVar18 = ((uint)request.x - (uint)state->fields.request.x) * 0x1000;
        uVar16 = ((uint)request.y - (uint)state->fields.request.y) * 0x1000;
        uVar14 = func_ov002_02050a08();
        uVar15 = func_ov002_02050a08();
        uVar15 = (uint)(int)uVar15;
        if (0x3000 < (int)uVar18) {
          if (((state->fields.directionMask & 8U) == 0) ||
              (((state->fields.directionMask & 8U) != 0 && (0x6000 < (int)uVar18)))) {
            iVar11 = func_02023c40();
            if (iVar11 == 1) {
              iVar11 = 0xf00;
            }
            else {
              iVar11 = 0xa00;
            }
            uVar24 = func_ov002_02050a08();
            iVar12 = FX_Inv(uVar18,0x4000);
            iVar12 = FX_Mul(iVar12, uVar24);
            if (iVar12 > iVar11) {
              iVar11 = func_02023c40();
              if (iVar11 == 1) {
                uVar14 = 0xf00;
              }
              else {
                uVar14 = 0xa00;
              }
            }
            else {
              uVar24 = func_ov002_02050a08();
              iVar11 = FX_Inv(uVar18,0x4000);
              uVar14 = func_ov002_02050a08();
              iVar11 = FX_Mul(iVar11, uVar24);
              if (iVar11 < (int)uVar14) {
                uVar14 = func_ov002_02050a08();
              }
              else {
                uVar24 = func_ov002_02050a08();
                iVar11 = FX_Inv(uVar18,0x4000);
                iVar11 = FX_Mul(iVar11, uVar24);
                uVar14 = iVar11;
              }
            }
            uVar20 |= 4;
          }
        }
        else {
          uVar18 = ~uVar18;
          if ((0x3000 < (int)uVar18) &&
             (((state->fields.directionMask & 4U) == 0 || (((state->fields.directionMask & 4U) != 0 && (0x6000 < (int)uVar18))))))
          {
            iVar11 = func_02023c40();
            if (iVar11 == 1) {
              iVar11 = 0xf00;
            }
            else {
              iVar11 = 0xa00;
            }
            uVar24 = func_ov002_02050a08();
            iVar12 = FX_Inv(uVar18,0x4000);
            iVar12 = FX_Mul(iVar12, uVar24);
            if (iVar12 > iVar11) {
              iVar11 = func_02023c40();
              if (iVar11 == 1) {
                uVar14 = 0xf00;
              }
              else {
                uVar14 = 0xa00;
              }
            }
            else {
              uVar24 = func_ov002_02050a08();
              iVar11 = FX_Inv(uVar18,0x4000);
              uVar14 = func_ov002_02050a08();
              iVar11 = FX_Mul(iVar11, uVar24);
              if (iVar11 < (int)uVar14) {
                uVar14 = func_ov002_02050a08();
              }
              else {
                uVar24 = func_ov002_02050a08();
                iVar11 = FX_Inv(uVar18,0x4000);
                iVar11 = FX_Mul(iVar11, uVar24);
                uVar14 = iVar11;
              }
            }
            uVar20 |= 8;
          }
        }
        if ((uVar20 & state->fields.directionMask & 0xc) != 0) {
          if ((int)uVar14 > state->fields.minimumSpeedX) {
            state->fields.speedX = uVar14;
          }
          else {
            state->fields.speedX = state->fields.minimumSpeedX;
          }
        }
        if (0x4000 < (int)uVar16) {
            iVar11 = func_02023c40();
            if (iVar11 == 1) {
              iVar11 = 0xf00;
            }
            else {
              iVar11 = 0xa00;
            }
            uVar18 = func_ov002_02050a08();
            iVar12 = FX_Inv(uVar16,0x4000);
            iVar12 = FX_Mul(iVar12, uVar18);
            if (iVar12 > iVar11) {
              iVar11 = func_02023c40();
              if (iVar11 == 1) {
                uVar15 = 0xf00;
              }
              else {
                uVar15 = 0xa00;
              }
            }
            else {
              uVar18 = func_ov002_02050a08();
              iVar11 = FX_Inv(uVar16,0x4000);
              uVar14 = func_ov002_02050a08();
              iVar11 = FX_Mul(iVar11, uVar18);
              if (iVar11 < (int)uVar14) {
                uVar15 = func_ov002_02050a08();
              }
              else {
                uVar18 = func_ov002_02050a08();
                iVar11 = FX_Inv(uVar16,0x4000);
                iVar11 = FX_Mul(iVar11, uVar18);
                uVar15 = iVar11;
              }
            }
          uVar20 = uVar20 | 1;
        }
        else {
          uVar16 = ~uVar16;
          if (0x4000 < (int)uVar16) {
            iVar11 = func_02023c40();
            if (iVar11 == 1) {
              iVar11 = 0xf00;
            }
            else {
              iVar11 = 0xa00;
            }
            uVar18 = func_ov002_02050a08();
            iVar12 = FX_Inv(uVar16,0x4000);
            iVar12 = FX_Mul(iVar12, uVar18);
            if (iVar12 > iVar11) {
              iVar11 = func_02023c40();
              if (iVar11 == 1) {
                uVar15 = 0xf00;
              }
              else {
                uVar15 = 0xa00;
              }
            }
            else {
              uVar18 = func_ov002_02050a08();
              iVar11 = FX_Inv(uVar16,0x4000);
              uVar14 = func_ov002_02050a08();
              iVar11 = FX_Mul(iVar11, uVar18);
              if (iVar11 < (int)uVar14) {
                uVar15 = func_ov002_02050a08();
              }
              else {
                uVar18 = func_ov002_02050a08();
                iVar11 = FX_Inv(uVar16,0x4000);
                iVar11 = FX_Mul(iVar11, uVar18);
                uVar15 = iVar11;
              }
            }
            uVar20 = uVar20 | 2;
          }
        }
        if ((state->fields.flags & 0x10000U) != 0) {
          uVar15 = (int)(((long long)(int)uVar15 + 0x800) >> 12);
        }
        if ((uVar20 & state->fields.directionMask & 3) != 0) {
          if ((int)uVar15 > state->fields.minimumSpeedY) {
            state->fields.speedY = uVar15;
          }
          else {
            state->fields.speedY = state->fields.minimumSpeedY;
          }
        }
        if (uVar20 == 0) {
          uVar20 = state->fields.directionMask;
          state->fields.defaultSpeedX = state->fields.minimumSpeed;
          state->fields.speedX = state->fields.minimumSpeedX;
          state->fields.speedY = state->fields.minimumSpeedY;
        }
      }
      state->fields.request = request;
    }
    goto input_done;
request_invalid:
    *(undefined2 *)((int)piVar7 + 0xfa) = 3;
  }
input_done:
  piVar7[0xe] = piVar7[0xe] & 0xfeffffff;
  uVar23 = func_ov022_02088314(idx);
  if ((uVar23 & 0x400) != 0) {
    iVar11 = (int)(puVar10->angleSource->angle - 0x8000 & 0xffff) >> 4;
    pFVar3 = data_0203d210;
    direction.x = -(int)pFVar3[iVar11 * 2];
    direction.y = 0;
    direction.z = -(int)pFVar3[iVar11 * 2 + 1];
    func_01ff8d18((uint *)&direction,(int *)&direction);
    VEC_Subtract(piVar7 + 5,piVar7 + 8,(int *)&delta);
    sVar6 = 0;
    delta.y = sVar6;
    func_01ff8d18((uint *)&delta,(int *)&delta);
    uVar18 = VEC_DotProduct((int *)&direction,(int *)&delta);
    if ((int)uVar18 < 0) {
      piVar7[0xe] = piVar7[0xe] | 0x1000000;
      iVar11 = func_02023c40();
      if (iVar11 == 1) {
        iVar11 = 0xf00;
      }
      else {
        iVar11 = 0xa00;
      }
      piVar7[0x2b] = iVar11;
    }
    uVar20 = 0;
  }
  piVar7[0x3c] = uVar20;
  piVar7[0x39] = piVar7[0x29];
  piVar7[0x3a] = piVar7[0x2a];
  piVar7[0x3b] = piVar7[0x2b];
LAB_arm9_ov002__0204d9ac:
  if ((piVar7[0xf] & 0x20U) == 0) {
    if (((piVar7[0xe] & 0x200U) == 0) && ((puVar10->flags & 0x800) == 0)) {
      iVar11 = func_020208e0();
      if (((iVar11 != 2) || (sVar5 = func_02030788(), sVar5 != 0)) &&
         (((data_0204c190 & 0x100) != 0 && ((data_0204c190 & 0x200) == 0))))
      {
        piVar7[0xe] = piVar7[0xe] | 8;
      }
      if ((piVar7[0xe] & 0x4000U) != 0) {
        piVar7[0x21] = 0x5000;
        piVar7[0x1f] = 0x8000;
        piVar7[0xe] = piVar7[0xe] & 0xffffbfff;
      }
    }
  }
  else {
    uVar4 = data_0204c18c;
    uVar18 = uVar4 & 0x100;
    if ((uVar18 != 0) && ((uVar4 & 0x200) == 0)) {
      uVar20 = uVar20 | 4;
    }
    if (((uVar4 & 0x200) != 0) && (uVar18 == 0)) {
      uVar20 = uVar20 | 8;
    }
    if (((piVar7[0xe] & 0x200U) == 0) && ((puVar10->flags & 0x800) == 0)) {
      iVar11 = func_020208e0();
      if (((iVar11 != 2) || (sVar5 = func_02030788(), sVar5 != 0)) &&
         ((data_0204c190 & 0x200) != 0)) {
        if (piVar7[0x35] <= 0) {
          piVar7[0x35] = 0x400;
        }
        else {
          piVar7[0xe] = piVar7[0xe] | 8;
          piVar7[0x35] = 0;
        }
      }
      if ((piVar7[0xe] & 0x4000U) != 0) {
        piVar7[0x21] = 0x5000;
        piVar7[0x1f] = 0x8000;
        piVar7[0xe] = piVar7[0xe] & 0xffffbfff;
      }
    }
    iVar11 = piVar7[0x34] - (func_02023c40() == 1 ? 0xcd : 0x89);
    if (iVar11 > 0x1000) {
      iVar11 = 0x1000;
    } else {
      iVar11 = piVar7[0x34] - (func_02023c40() == 1 ? 0xcd : 0x89);
      if (iVar11 < 0) {
        iVar11 = 0;
      } else {
        iVar11 = piVar7[0x34] - (func_02023c40() == 1 ? 0xcd : 0x89);
      }
    }
    piVar7[0x34] = iVar11;
    iVar11 = piVar7[0x35] - (func_02023c40() == 1 ? 0xcd : 0x89);
    if (iVar11 > 0x1000) {
      iVar11 = 0x1000;
    } else {
      iVar11 = piVar7[0x35] - (func_02023c40() == 1 ? 0xcd : 0x89);
      if (iVar11 < 0) {
        iVar11 = 0;
      } else {
        iVar11 = piVar7[0x35] - (func_02023c40() == 1 ? 0xcd : 0x89);
      }
    }
    piVar7[0x35] = iVar11;
  }
  uVar23 = (uint)func_ov022_02088314(idx);
  uVar16 = piVar7[0xe];
  if ((uVar23 & 0x400) != 0) {
    if ((uVar16 & 0x10) == 0) {
      piVar7[0xe] = (uVar16 | 0x18) & 0xfffffdff;
    }
    uVar20 = 0;
  }
  else {
    piVar7[0xe] = uVar16 & 0xffffffef;
  }
  iVar11 = func_ov022_020886d0(idx);
  if (iVar11 != 0) {
    if ((data_0204c240 & 4) == 0) {
      piVar7[0xe] = piVar7[0xe] | 0x400;
    }
    else {
      func_ov002_0204d12c();
    }
  }
  if ((piVar7[0xe] & 0x800U) != 0) {
    iVar12 = func_02023c40();
    iVar11 = 0xe39;
    iVar17 = iVar12 == 1 ? 0x1e0 : 0x140;
    if (0xe39 <= (int)(uint)*(ushort *)(piVar7 + 0x28)) {
      *(ushort *)(piVar7 + 0x28) = *(ushort *)(piVar7 + 0x28) - iVar17;
      *(ushort *)((int)piVar7 + 0xa2) = *(ushort *)((int)piVar7 + 0xa2) - iVar17;
      if ((int)(uint)*(ushort *)(piVar7 + 0x28) < iVar11) {
        uVar1 = (undefined2)iVar11;
        *(undefined2 *)(piVar7 + 0x28) = uVar1;
        *(undefined2 *)((int)piVar7 + 0xa2) = uVar1;
        piVar7[0xe] = piVar7[0xe] & 0xfffff7ff;
      }
      *piVar7 = data_0203d210[((int)(uint)*(ushort *)(piVar7 + 0x28) >> 4) * 2];
      piVar7[1] = data_0203d210[((int)(uint)*(ushort *)((int)piVar7 + 0xa2) >> 4) * 2 + 1];
    }
  }
  else if ((piVar7[0xe] & 0x1000U) != 0) {
    iVar11 = func_02023c40();
    uVar18 = 0x1555;
    iVar17 = iVar11 == 1 ? 0x1e0 : 0x140;
    *(ushort *)(piVar7 + 0x28) = *(ushort *)(piVar7 + 0x28) + iVar17;
    *(ushort *)((int)piVar7 + 0xa2) = *(ushort *)((int)piVar7 + 0xa2) + iVar17;
    if (uVar18 < *(ushort *)(piVar7 + 0x28)) {
      uVar1 = (undefined2)uVar18;
      *(undefined2 *)(piVar7 + 0x28) = uVar1;
      *(undefined2 *)((int)piVar7 + 0xa2) = uVar1;
      piVar7[0xe] = piVar7[0xe] & 0xffffefff;
    }
    *piVar7 = data_0203d210[((int)(uint)*(ushort *)(piVar7 + 0x28) >> 4) * 2];
    piVar7[1] = data_0203d210[((int)(uint)*(ushort *)((int)piVar7 + 0xa2) >> 4) * 2 + 1];
  }
  if ((piVar7[0xe] & 0x200U) == 0) {
    if ((piVar7[0xe] & 2U) != 0) {
      iVar11 = func_ov022_02088d04();
      if (((((uVar20 & 4) != 0) && ((piVar7[0xf] & 0x10U) == 0)) ||
          (((uVar20 & 8) != 0 && ((piVar7[0xf] & 0x10U) != 0)))) &&
         (uVar16 = piVar7[0x20],
          uVar16 -= piVar7[0x2a],
          uVar16 &= 0xffff,
          piVar7[0x20] = uVar16,
          (piVar7[0xe] & 0x10000U) != 0)) {
        func_ov022_02088280(idx, uVar16);
      }
      if (((((uVar20 & 8) != 0) && ((piVar7[0xf] & 0x10U) == 0)) ||
          (((uVar20 & 4) != 0 && ((piVar7[0xf] & 0x10U) != 0)))) &&
         (uVar16 = piVar7[0x20],
          uVar16 += piVar7[0x2a],
          uVar16 &= 0xffff,
          piVar7[0x20] = uVar16,
          (piVar7[0xe] & 0x10000U) != 0)) {
        func_ov022_02088280(idx, uVar16);
      }
      iVar12 = func_ov002_02050b90(piVar7[0x11]);
      iVar17 = func_ov002_02050b90(0);
      {
      int fxRatio;
      fxRatio = FX_Inv(iVar12,iVar17);
      iVar12 = FX_Inv(piVar7[0x21],0xa000);
      if (iVar12 < 0) {
        iVar12 = -iVar12;
      }
      if (((((uVar20 & 1) != 0) && ((piVar7[0xf] & 8U) == 0)) ||
          (((uVar20 & 2) != 0 && ((piVar7[0xf] & 8U) != 0)))) &&
         (iVar17 = FX_Mul(fxRatio, 0x3400), iVar17 > piVar7[0x21])) {
        piVar7[0x21] = piVar7[0x21] + (piVar7[0x2b] + iVar12);
      }
      if (((((uVar20 & 2) != 0) && ((piVar7[0xf] & 8U) == 0)) ||
          (((uVar20 & 1) != 0 && ((piVar7[0xf] & 8U) != 0)))) &&
         (iVar17 = FX_Mul(fxRatio, -0x2000), iVar17 < piVar7[0x21])) {
        piVar7[0x21] = piVar7[0x21] - (piVar7[0x2b] + iVar12);
      }
      }
      if ((piVar7[0xe] & 0x1000000U) != 0) {
        iVar12 = puVar10->heightBase + 0x400;
      }
      else {
        iVar12 = func_ov002_02050a54(piVar7[0x11]);
      }
      piVar7[0x22] = iVar12;
      if (uVar20 != 0)
        goto camera_input_inactive;
      iVar12 = func_020208e0();
      if (iVar12 == 2) {
        sVar6 = func_02030788();
        if (sVar6 == 0)
          goto camera_input_inactive;
      }
      if (((uVar18 = func_020235d0(0x37c6,1), uVar18 != 0 ||
           (((data_0204c18c & 0x400) == 0 || (*(char *)(iVar11 + 1) != '\x02')))) &&
          ((((puVar10->flags & 0x800) == 0 &&
            (uVar23 = func_ov022_02088314(idx), (uVar23 & 0x3710) == 0)) &&
           ((((uVar4 = data_0204c18c, (uVar4 & 0x40) != 0 || ((uVar4 & 0x80) != 0)) ||
             ((uVar4 & 0x20) != 0)) || ((uVar4 & 0x10) != 0))))))) {
        iVar11 = func_ov002_02050b68(piVar7[0x11]);
        piVar7[0x21] = iVar11;
        iVar11 = func_ov002_02050a54(piVar7[0x11]);
        piVar7[0x22] = iVar11;
        iVar11 = func_ov002_02050b90(piVar7[0x11]);
        piVar7[0x1f] = iVar11;
        uVar18 = func_ov002_02050a08();
        piVar7[0x2a] = uVar18;
        if (((piVar7[0xe] & 0x10000000U) == 0) &&
           (((data_0204c18c & 0x20) != 0 || ((data_0204c18c & 0x10) != 0))))
        {
          func_02023c40();
          iVar11 = piVar7[0x37] + (func_02023c40() == 1 ? 0xcd : 0x89);
          if (iVar11 < 0) {
            iVar11 = 0;
          } else {
            iVar11 = piVar7[0x37] + (func_02023c40() == 1 ? 0xcd : 0x89);
          }
          piVar7[0x37] = iVar11;
          if (iVar11 > 0x333) {
            iVar12 = piVar7[0x16];
            if ((data_0204c18c & 0x20) != 0) {
              piVar7[0x20] = iVar12 + 0x300U & 0xffff;
            }
            else {
              piVar7[0x20] = iVar12 - 0x300U & 0xffff;
            }
          }
        }
        goto camera_input_done;
      }
camera_input_inactive:
      piVar7[0x37] = 0;
camera_input_done:
      ;
    }
    if (((piVar7[0xe] & 8U) != 0) && ((piVar7[0xe] & 0x20008000U) == 0)) {
      local_5c = func_ov002_0204fc54;
      iVar11 = func_ov022_02088254(idx);
      piVar7[0x14] = iVar11;
      piVar7[0x37] = 0;
    }
    piVar7[0xe] = piVar7[0xe] & 0xfffffff7;
  bVar22 = false;
    iVar11 = func_ov022_020886d0(idx);
    if (iVar11 != 0)
      goto handler_bool_false;
    if ((piVar7[0xe] & 0x2000U) != 0)
      goto handler_bool_false;
    if ((piVar7[0xe] & 0x20008000U) == 0)
      goto handler_bool_eval;
handler_bool_false:
    bVar22 = false;
    goto handler_bool_done;
handler_bool_eval:
    iVar11 = func_ov022_02086620(uVar8);
    if (iVar11 != 0) {
      bVar22 = true;
      goto handler_bool_done;
    }
    if (piVar7[0x10] == 4) {
      bVar22 = true;
      piVar7[0xe] = piVar7[0xe] | 0x100;
    }
handler_bool_done:
    if (bVar22) {
      local_5c = func_ov002_0204f0a8;
      piVar7[0xe] = piVar7[0xe] | 0x60;
    }
    if ((piVar7[0xe] & 0x8000U) != 0) {
      piVar7[0x13] = 0;
      local_5c = func_ov002_0204f7d4;
      piVar7[0xe] = piVar7[0xe] & 0xffff7fff;
    }
    else {
      if (((piVar7[0xe] & 0x20000000U) != 0) && (puVar10->kind == 2 || puVar10->kind == 9)) {
        piVar7[0x12] = piVar7[0x11];
        if (puVar10->kind == 2) {
          piVar7[0x11] = 0x10;
        }
        piVar7[0x13] = 4;
        piVar7[0x37] = 0;
        local_5c = func_ov002_0204f7d4;
        piVar7[0xe] = piVar7[0xe] & 0xffff7fff;
      }
    }
    if ((piVar7[0xe] & 0x400U) != 0) {
      piVar7[0x11] = piVar7[0x12];
      piVar7[0x37] = 0;
      local_5c = func_ov002_0204fdc4;
      piVar7[0xe] = piVar7[0xe] & 0xfffffbff;
    }
  }
  iVar11 = func_ov002_02050b90(piVar7[0x11]);
  piVar19 = piVar7 + 0x1f;
  func_ov002_0204eee0
            (piVar7 + 0x1c,(uint *)(piVar7 + 0x19),piVar19,puVar9,piVar7[0x16],iVar11,piVar7[0x1f]);
  func_ov002_0204ff18(func_02023bf0());
  return local_5c;
}
#undef piVar7
#pragma opt_dead_assignments on
