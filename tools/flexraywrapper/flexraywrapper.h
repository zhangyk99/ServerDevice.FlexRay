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
    uint8_t ChannelAConnectedNode;                   //succ1     // Enable ChannelA: 0: Disable 1: Enable
    uint8_t ChannelBConnectedNode;                   //succ1     // Enable ChannelB: 0: Disable 1: Enable
    uint8_t ChannelASymbolTransmitted;               //succ1     // Enable Symble Transmit function of Channel A: 0: Disable 1: Enable
    uint8_t ChannelBSymbolTransmitted;               //succ1     // Enable Symble Transmit function of Channel B: 0: Disable 1: Enable
    uint32_t Speed;                              //prct1      // 0 for 10m, 1 for 5m, 2 for 2.5m, convert from Database
    //允许簇内节点通过启动调度同步尝试启动簇的最大次数，有效值为 2~31 次。
    uint8_t ColdStartAttempts;                       //succ1
    //动作点偏离静态时隙或符号窗的起始点的宏节拍数量，有效值为 1~63MT。
    uint8_t ActionPointOffset;                               //gtu09
    //一个动态时隙内的空闲阶段持续时间，有效值为 0~2 个微时隙
    uint8_t DynamicSlotIdlePhase;                            //gtu09
    //微时隙的持续时间，有效值为 2~63MT。
    uint8_t MiniSlot;                                       //gtu08
    //微时隙动作点偏离微时隙起始点的宏节拍数量，有效值为 1~31MT。
    uint8_t MiniSlotActionPointOffset;                       //gtu09
    uint16_t NetworkIdleTime;                            //gtu04
    double SampleClockPeriod;                             //NOTE: no use
    //静态时隙的持续时间，有效值为 4~661MT。
    uint16_t StaticSlot;                                   //gtu07
    //符号窗的持续时间，有效值为 0~142MT。
    uint8_t SymbolWindow;                                //NOTE: no use
    //传输起始序列（TSS）的位数，有效值为 3~15gdBit。
    uint16_t TimeSymbolStateTransmitter;        //prtc1

    //节点对收到唤醒符号的“空闲”部分持续时间进行测试时所使用的位数。持续时间 等于(gdWakeupSymbolTxIdle-gdWakeupSymbolTxLow)/2 再减去一个安全部分，有效值为 14~59gdBit。
    uint8_t WakeUpSymbolRXIdle;                  //ptrc2
    //节点对收到唤醒符号的 LOW 部分进行测试时所使用的位数。这是接收器为检测LOW 部分必须接收到的零的位数。该持续时间等于 gdWakeupSymbolTxLow 减去一个安全部分，有效值为 11~59gdBit。
    uint8_t WakeUpSymbolRXLow;                   //ptrc2
    //检测唤醒所使用的窗口的大小。唤醒检测需要一段 LOW 和空闲时间(从一个 WUS)，在这个大小的窗口内，能够完整检测一段 LOW 的时间(另一个 WUS)。这个持续时间等于 gdWakeupSymbolTxIdle+2×gdWakeupSymbolTxLow，再加上一个安全部分，有效值为 76~301gdBit。
    uint16_t WakeUpSymbolRXWindow;              //ptrc1
    //节点发送唤醒符的“空闲”部分所使用的位数，持续时间等于 18μs，有效值为45~180gdBit。
    uint8_t WakeUpSymbolTXIdle;                  //ptrc2
    //节点发送唤醒符的“LOW”部分所使用的位数。持续时间等于 6μs，有效值为15~60gdBit。
    uint8_t WakeUpSymbolTXLow;                   //ptrc2

    //在存在噪声的情况下，启动监听超时值和唤醒监听超时值的上限。它是节点参数pdListenTimeout 的倍数，有效值为 2~16。
    uint8_t ListenNoise;                             //succ2
    //一个通信周期的总宏节拍数量，有效值为 10~16000MT。
    uint16_t MacroPerCycle;                             //gtu02
    double MacroTick;                                      //NOTE: no use
    double MaxInitializationError;                         //NOTE: no use
    //定义缺失时钟修正项的连续偶/奇循环对数目，缺失时钟修正项将导致协议从正常有源状态或正常无源状态过渡到停止状态，有效值为 1~15 个偶/奇循环对。
    uint8_t MaxWithoutClockCorrectionFatal;           //succ3
    //定义缺失时钟修正项的连续偶/奇循环对数目，缺失时钟修正项将导致协议从正常有源状态过渡到正常无源状态。需要注意的是gMaxWithoutClockCorrectionPassive≤gMaxWithoutClockCorrectionFatal，有效值为 1~15 个偶/奇循环对。
    uint8_t MaxWithoutClockCorrectionPassive;         //succ3
    //网络管理向量的长度，有效值为 0~12 字节。
    uint8_t NetworkManagementVectorLength;    //head
    //动态段的微时隙数，有效值为 0~7986 个。
    uint16_t NumberOfMiniSlots;                             //gtu08
    //静态段的静态时隙数，有效值为 2~1023 个。
    uint16_t NumberOfStaticSlots;                           //gtu07
    //NIT 内偏差修正相位的起点，表示周期开始后的第几个宏节拍开始修正，有效值9~15999MT。
    uint16_t OffsetCorrectionStart;                      //gtu04
    //静态帧的有效负载长度，有效值为 0~127 个字。
    uint8_t PayloadLengthStatic;              //head
    //可发送“同步帧指示位设置为 1”的帧的最大节点数量，有效值为 2~15 个。
    uint8_t SyncNodeMax;                               //gtu02
    //CAS 接收窗口上限，有效值为 67~99gdBit。
    uint8_t CasRXLowMax;                       //prtc1
    uint8_t CasRXLowMin;                                  //NOTE: no use
    double Bit;                                           //NOTE: no use
    uint32_t Cycle;                                       //NOTE: no use
    uint8_t ClusterDriftDamping;                          //NOTE:
    double OffsetCorrectionMax;                           //NOTE: no use
};

struct ECUConfig{
    //用于发送启动帧、同步帧或指定单时隙帧的时隙标识符（ID），有效值为 1~1023时隙。
    uint8_t StartUpSync;                                 //NOTE: no use
    //动态帧的最大有效负载长度，有效值为 0~127 个字。
    uint8_t MaxDynamicPayloadLength;                     //NOTE: no use
    //本地用于速率修正的簇漂移阻尼系数，有效值为 0~20μT。
    uint8_t ClusterDriftDamping;                        //gtu05
    //接收器用于计算主时间基准点和次级时间基准点之间差异的值，有效值为14~143μT。
    uint8_t DecodingCorrection;                         //gtu05
    //启动监听超时和唤醒监听超时值，有效值为 1284~1283846μT。
    uint32_t ListenTimeout;                       //succ2
    //两个节点以非同步时钟运行一个通信周期以上时，两者之间的最大漂移偏差，有效值为 2~1923μT。
    uint16_t MaxDrift;                                   //gut06
    //进行主机请求的外部偏差修正时，NIT 加上或减去的微节拍数，有效值为 0~7μT。
    uint8_t ExternOffsetCorrection;                         //gtu11
    //进行主机请求的外部速率修正时，周期加上或减去的微节拍数，有效值为0~7μT。
    uint8_t ExternRateCorrection;                           //gtu11
    //在动态段最后可以开始帧发送的微时隙数，有效值为 0~7980。
    uint16_t LatestTX;                        //head
    //一个通信周期的总微节拍数量。需要注意的是 pMicroPerCycle= gMacroPerCycle* pMicroPerMacroNom，有效值为 640~640000μT。
    uint32_t MicroPerCycle;                        //gtu01
    //允许最大偏差修正值的大小，有效值为 2~1923μT。
    uint16_t OffsetCorrectionOut;                         //gtu10
    //允许最大速率修正值的大小，有效值为 2~1923μT。
    uint16_t RateCorrectionOut;                           //gtu10
    uint8_t SamplesPerMicroTick;                          //NOTE: no use
    //用来补偿 A 通道接收延迟的值。它覆盖了高达 2.5μs 的假定传播延迟，有效值为 0~200μT。
    uint8_t DelayCompensationA;                         //gtu05
    //用来补偿 B 通道接收延迟的值。它覆盖了高达 2.5μs 的假定传播延迟，有效值为 0~200μT。
    uint8_t DelayCompensationB;                         //gtu05
    //当节点进入唤醒发送状态时，形成唤醒模式的唤醒符号重复次数，有效值为 2~63次。
    uint8_t WakeUpPattern;                     //prct1
    //允许时钟同步错误过渡到停止状态标志位，有效值为 0 和 1，1 为允许。
    uint8_t AllowHaltDueToClock;                 //succ1
    //在正常无源状态到正常有源状态的过渡之前，必须要有的有效时钟修正项的连续偶/奇循环对数量。设置为 0 表示不允许从正常无源状态过渡到正常有源状态，有效值为 0~31 个偶/奇循环对。
    uint8_t AllowPassiveToAction;                //succ1
    //集成过程中，启动帧所允许的、经扩展的测量时钟偏差范围，有效值为0~1875μT。
    uint16_t AcceptedStartUpRange;                         //gtu06
    //A 通道静态时隙边界和第二个时间基准点的下一个宏节拍边界之间的宏节拍数，有效值为 2~68MT。
    uint8_t MacroInitialOffsetA;                      //gtu 03
    //B 通道静态时隙边界和第二个时间基准点的下一个宏节拍边界之间的宏节拍数，有效值为 2~68MT。
    uint8_t MacroInitialOffsetB;                      //gtu 03
    //由 pMacroInitialOffset[CH]描述的最接近的宏节拍边界和第二时间基准点之间的微节拍数，有效值为 0~239μT。
    uint8_t MicroInitialOffsetA;                      //gtu 03
    //由 pMacroInitialOffset[CH]描述的最接近的宏节拍边界和第二时间基准点之间的微节拍数，有效值为 0~239μT。
    uint8_t MircoInitialOffsetB;                      //gtu 03
    //启动后节点是否将进入单时隙模式标志位，有效值为 0 和 1。
    uint8_t SingleSlotEnabled;                   //succ1     // FALSE_0, TRUE_1
    double MicroTick;                                   //NOTE: no use

    //KeySlotUsedForStartup
    //指 示 关 键 时 隙 是 否 用 于 发 送 启 动 帧 的 标 志 ， 有 效 值 为 0 和 1 ， 若pKeySlotUsedForStartup 设置为 1，则 pKeySlotUsedForSync 也必须设置为 1。
    //pKeySlotUsedForSync
    //指 示 关 键 时 隙 是 否 用 于 发 送 同 步 帧 的 标 志 ， 有 效 值 为 0 和 1 ， 若pKeySlotUsedForStartup 设置为 1，则 pKeySlotUsedForSync 也必须设置为 1。
    //pMicroPerMacroNom
    //一个宏节拍包含的微节拍数量，有效值为 40~240μT。
    //pWakeupChannel
    //节点用于发送唤醒模式的通道，0 为 A 通道，1 为 B 通道。
    //keySlotHeaderCrc
    //关键帧头 CRC 校验和，应用本模块时填写 0 即可，实际校验和由设备软件自动计算。
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
