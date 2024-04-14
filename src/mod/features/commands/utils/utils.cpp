#include "externals/il2cpp-api.h"


#include "logger/logger.h"

float ConvertToFloat(int32_t value)
{
    float fresult;
    std::memcpy(&fresult, &value, sizeof(value));
    return fresult;
}







