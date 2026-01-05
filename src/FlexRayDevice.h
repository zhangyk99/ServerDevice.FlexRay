//
// Created by 79933 on 2025/11/25.
//

#ifndef SERVERDEVICE_FLEXRAY_FLEXRAYDEVICE_H
#define SERVERDEVICE_FLEXRAY_FLEXRAYDEVICE_H

#include <mutex>
#include "serverlogger/logger.h"
#include "FlexRayChannel.h"

#include "watchdog/mtestserver_watchdog.h"

namespace FlexRay {
    class FlexRayDevice {
    private:
        std::string deviceName;
        int errorCode;
        void *con;
        std::mutex mtx;
        void *wdPtr;

        std::shared_ptr<FlexRayConfig> deviceConfig;
        std::shared_ptr<FlexRayChannel> channelPtr;

        std::string libPath;
        std::string logPath;

    public:
        FlexRayDevice(const std::string &name, const std::string &config, void *con);

        ~FlexRayDevice();

        void DoStep();

        void DoFunction(const std::string &name, const std::string &data, std::string &result);

        void GetVariables(std::string &vars, std::string &des) const;

        void SetName(const std::string &name) { deviceName = name; }

        std::string GetName() const { return deviceName; }

        int GetErrorCode() const { return errorCode; }

        void GetTimingInfo(double &freq, int &processor, int &priority) const;

        static std::string GetVersion() { return "1.0.0"; }
    };
}

#endif //SERVERDEVICE_FLEXRAY_FLEXRAYDEVICE_H