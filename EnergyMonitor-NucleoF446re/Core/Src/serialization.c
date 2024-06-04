#include "serialization.h"

#include "hc05_bluetooth.h"
#include <stdio.h>

void bl_serialize(meterData* pData){

    const char* data;

    sprintf(&data, "K,%.3d,%.3d,%.2d,%.1d",
        pData->voltage, 
        pData->current_mA, 
        pData->frequency, 
        1
    );

    hc05_send_data(data);
}