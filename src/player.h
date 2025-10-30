#pragma once
#include "vec.h"
#include <basetsd.h>
#include <cstdint>


struct CurrentWeapon {
    char pad_0000[0x48];        // 0x00 → 0x48
    int shootingSpeed;          // 0x48
    char pad_0054[0x60 - 0x4C]; // 0x4C → 0x62
    int noRecoil;           // 0x60
};

struct WeaponEntry {
    DWORD32 vftable;            // 0x00
    int id;                     // 0x04
    struct PlayerStruct* owner; // 0x08
    struct CurrentWeapon* currWeapon;// 0x0C
};

enum class Teams : int32_t
{
    Red = 0,
    Blue = 1,
    Unk1 = 2,
    Unk2 = 3,
    Spectator = 4
};

class playerEntity
{
public:
    void* vtable;
    Vector3 o; //0x0004
    Vector3 Velocity; //0x0010
    Vector3 N00000055; //0x001C
    Vector3 pos; //0x0028
    float yaw; //0x0034
    float pitch; //0x0038
    float roll; //0x003C
    char pad_0040[16]; //0x0040
    float eyeHeight; //0x0050
    char pad_0054[152]; //0x0054
    int32_t health; //0x00EC
    char pad_00F0[236]; //0x00F0
    int32_t kills; //0x01DC
    char pad_01E0[37]; //0x01E0
    char N000001CF[259]; //0x0205
    char pad_0308[4]; //0x0308
    int32_t team; //0x030C
    char pad_0310[44]; //0x0310
}; //Size: 0x0266 can the problem be because of my gencode?

class entityList {
public:
    playerEntity* players[64]; //0x0000 - 0x0400
};