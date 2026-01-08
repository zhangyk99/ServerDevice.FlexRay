//
// Created by 79933 on 2025/12/3.
//

#ifndef FLEXRAYWRAPPER_FLEXRAYWRAPPER_H
#define FLEXRAYWRAPPER_FLEXRAYWRAPPER_H

#ifndef FLEXRAYDLL
#ifdef __linux__
#define FLEXRAYDLL __attribute__((visibility("default")))
#else
#define FLEXRAYDLL __declspec(dllexport)
#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

struct ClusterConfig{
    uint8_t ChannelAConnectedNode;
    uint8_t ChannelBConnectedNode;
    uint8_t ChannelASymbolTransmitted;
    uint8_t ChannelBSymbolTransmitted;
    uint32_t Speed;
    uint8_t ColdStartAttempts;
    uint8_t ActionPointOffset;
    uint8_t DynamicSlotIdlePhase;
    uint8_t MiniSlot;
    uint8_t MiniSlotActionPointOffset;
    uint16_t NetworkIdleTime;
    double SampleClockPeriod;
    uint16_t StaticSlot;
    uint8_t SymbolWindow;
    uint16_t TimeSymbolStateTransmitter;

    uint8_t WakeUpSymbolRXIdle;
    uint8_t WakeUpSymbolRXLow;
    uint16_t WakeUpSymbolRXWindow;
    uint8_t WakeUpSymbolTXIdle;
    uint8_t WakeUpSymbolTXLow;

    uint8_t ListenNoise;
    uint16_t MacroPerCycle;
    double MacroTick;
    double MaxInitializationError;
    uint8_t MaxWithoutClockCorrectionFatal;
    uint8_t MaxWithoutClockCorrectionPassive;
    uint8_t NetworkManagementVectorLength;
    uint16_t NumberOfMiniSlots;
    uint16_t NumberOfStaticSlots;
    uint16_t OffsetCorrectionStart;
    uint8_t PayloadLengthStatic;
    uint8_t SyncNodeMax;
    uint8_t CasRXLowMax;
    uint8_t CasRXLowMin;
    double Bit;
    uint32_t Cycle;
    uint8_t ClusterDriftDamping;
    double OffsetCorrectionMax;
};

struct ECUConfig{
    uint8_t StartUpSync;
    uint8_t MaxDynamicPayloadLength;
    uint8_t ClusterDriftDamping;
    uint8_t DecodingCorrection;
    uint32_t ListenTimeout;
    uint16_t MaxDrift;
    uint8_t ExternOffsetCorrection;
    uint8_t ExternRateCorrection;
    uint16_t LatestTX;
    uint32_t MicroPerCycle;
    uint16_t OffsetCorrectionOut;
    uint16_t RateCorrectionOut;
    uint8_t SamplesPerMicroTick;
    uint8_t DelayCompensationA;
    uint8_t DelayCompensationB;
    uint8_t WakeUpPattern;
    uint8_t AllowHaltDueToClock;
    uint8_t AllowPassiveToAction;
    uint16_t AcceptedStartUpRange;
    uint8_t MacroInitialOffsetA;
    uint8_t MacroInitialOffsetB;
    uint8_t MicroInitialOffsetA;
    uint8_t MircoInitialOffsetB;
    uint8_t SingleSlotEnabled;
    double MicroTick;
};

FLEXRAYDLL int32_t fr_find_all_channels(char *str, int32_t *chnCount);

FLEXRAYDLL int32_t fr_get_error_code(char* error, int32_t *eventNum);

FLEXRAYDLL int32_t fr_set_channel_config(void **channel, char *device, uint16_t *channelConfig, ClusterConfig *clusterConfig, ECUConfig *ecuConfig);

FLEXRAYDLL int32_t fr_open_channel(void *channel);

FLEXRAYDLL int32_t fr_close_channel(void *channel);

FLEXRAYDLL int32_t fr_set_message(void *channel, uint16_t sold, uint8_t cycle, uint8_t dataLength, uint8_t *data, int32_t timeout);

FLEXRAYDLL int32_t fr_set_messages(void *channel, uint16_t item, uint16_t *sold, uint8_t *cycle, uint8_t *dataLength, uint8_t *data, int32_t timeout);

FLEXRAYDLL int32_t fr_get_message(void *channel, uint16_t *sold, uint8_t *cycle, uint8_t *dataLength, uint8_t *data, int32_t timeout);

FLEXRAYDLL int32_t fr_get_messages(void *channel, uint16_t *item, uint16_t *sold, uint8_t *cycle, uint8_t *dataLength, uint8_t *data, int32_t timeout);

}


#endif //FLEXRAYWRAPPER_FLEXRAYWRAPPER_H
