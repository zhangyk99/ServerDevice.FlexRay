//
// Created by 79933 on 2025/11/27.
//

#ifndef MTESTSERVER_DEVICE_FLEXRAY_FLEXRAYCONFIG_H
#define MTESTSERVER_DEVICE_FLEXRAY_FLEXRAYCONFIG_H

#include <string>
#include <vector>
#include <memory>
#include "rapidjson/document.h"
#include "flexraywrapper/flexraywrapper.h"

namespace FlexRay {
    class FlexRayConfig {
    public:
        explicit FlexRayConfig(const std::string &config);

        static std::shared_ptr<FlexRayConfig> Create(const std::string &json);

        struct DeviceInfo {
            std::string DeviceName;
            int DeviceID;
            std::string DeviceType;
            std::string DeviceDes;
            int Version;
            std::string Author;
            std::string CreateTime;
            std::string Reviser;
            std::string ModifyTime;
        };

        struct Signal {
            int16_t ID;
            std::string Name;
            std::string Variable;
            std::string Unit;
            int8_t Gain;
            int8_t Offset;
            int8_t StartBit;
            int8_t NumBits;
            double DefaultValue;
            double MaxValue;
            double MinValue;
            bool ByteOrder;
            int8_t DataType;
            int8_t SignalType;
            int8_t ModeValue;
            std::string Comment;
        };

        struct Frame {
            uint16_t ID;
            std::string Name;
            bool TxOrRx;    // true: transform  false: receive
            uint16_t Frequency;
            uint8_t Type;
            uint16_t Sold;
            uint8_t CycleRepetition;
            uint8_t BaseCycle;
            uint8_t InCycleRepetition;
            uint8_t Config;
            uint8_t PayloadLength;
            std::string Description;
            std::vector<Signal> Signals;
        };

        struct Channel {
            std::string Name;
            uint16_t ID;
            bool UseDefault;
            bool UseMaxMin;
            bool BridgePattern;
            bool Termination;
            bool HardwareTiming;
            ECUConfig EcuConfig;
            std::string Description;
            std::string WatchDog;
            std::vector<Frame> Frames;
        };

        struct DeviceConfig {
            std::string FlexRay;
            std::string SerialNumber;
            ClusterConfig ClusterConfig;
//            std::vector<Channel> ChannelList;
            Channel Chn;
        };

        struct DeviceData {
            DeviceInfo Info;
            DeviceConfig Config;
        };

        [[nodiscard]] std::string GetErrorString() const { return errorString; }

        [[nodiscard]] bool GetErrorFlag() const { return errorFlag; }

        [[nodiscard]] std::shared_ptr<DeviceData> GetDataPtr() const { return dataPtr; };

    private:
        std::string errorString;
        bool errorFlag;
        std::shared_ptr<DeviceData> dataPtr;

        bool ParseDeviceData(const std::string &defaultStr);

        bool ParseDeviceConfig(const rapidjson::Value &jsonStr, DeviceConfig &config);

        bool ParseClusterConfig(const rapidjson::Value &jsonStr, ClusterConfig &cluster);

        bool ParseDeviceInfo(const rapidjson::Value &jsonStr, DeviceInfo &info);

        bool ParseChannel(const rapidjson::Value &json, Channel &chn);

        bool ParseChannelConfig(const rapidjson::Value &jsonStr, ECUConfig &chnConfig);

        bool ParseFrame(const rapidjson::Value &json, Frame &message);

        bool ParseSignal(const rapidjson::Value &jsonStr, Signal &signal);
    };
}


#endif //MTESTSERVER_DEVICE_FLEXRAY_FLEXRAYCONFIG_H
