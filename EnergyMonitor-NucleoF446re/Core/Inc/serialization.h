#pragma once
// 8 byte struct
typedef struct meterData{
    int voltage;
    int current_mA;
    int frequency;
    float potFact;
} meterData;

void bl_serialize(meterData* pData);