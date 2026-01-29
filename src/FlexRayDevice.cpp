//
// Created by 79933 on 2025/11/25.
//

#include "FlexRayDevice.h"

namespace FlexRay{
    FlexRayDevice::FlexRayDevice(const std::string &name, const std::string &config, void *con) : deviceName(name), con(con){
        deviceConfig = FlexRayConfig::Create(config);
        auto parseErrorString = deviceConfig->GetErrorString();
        if(!parseErrorString.empty())
            msg_log_error("Device parse error: " + parseErrorString, deviceName);
        auto &chn = deviceConfig->GetDataPtr()->Config.Chn;

        std::vector<std::set<uint16_t>> sendList;
        sendList.resize(64);
        for(auto &it : chn.Frames)
            for(int i = 0; i < 64; i++)
                if(i > it.BaseCycle && (i - it.BaseCycle) % it.BaseCycle == 0)
                    sendList[i].insert(it.SlotID);

        //get path
        char lib[200]{};
        char log[200]{};
        errorCode = GetPath(lib, log);
        libPath = lib;
        logPath = log;

        auto wdVar = chn.WatchDog;
        //set watchdog;
        wd_create(chn.WatchDog.data(), 0, &wdPtr);

        //device channel index
        channelPtr = std::make_shared<FlexRayChannel>(con, deviceConfig->GetDataPtr()->Config.Chn.Name.data(), &deviceConfig->GetDataPtr()->Config.ClusterConfig, &deviceConfig->GetDataPtr()->Config.Chn, sendList);
    }

    FlexRayDevice::~FlexRayDevice(){
        wd_free();
    }

    void FlexRayDevice::DoStep(){
        std::lock_guard<std::mutex> lock(mtx);

        //receive data by frequency
        if (!channelPtr->RecMessage())
            //reset watchdog
            wd_reset(wdPtr, 0);

        //send data by frequency
        if(!channelPtr->SendMessage())
            return;

        channelPtr->AddTimePos();
    }

    void FlexRayDevice::DoFunction(const std::string &name, const std::string &data, std::string &result) {
        if(name == "Restart") {
            //close
            auto devName = deviceConfig->GetDataPtr()->Config.FlexRay.data();
            auto clusterConfig = &deviceConfig->GetDataPtr()->Config.ClusterConfig;
            auto ecuPtr = &deviceConfig->GetDataPtr()->Config.Chn;
            auto &chn = deviceConfig->GetDataPtr()->Config.Chn;
            std::vector<std::set<uint16_t>> sendList;
            sendList.resize(64);
            for(auto &it : chn.Frames)
                for(int i = 0; i < 64; i++)
                    if(i > it.BaseCycle && (i - it.BaseCycle) % it.BaseCycle == 0)
                        sendList[i].insert(it.SlotID);
            channelPtr = std::make_shared<FlexRayChannel>(con, devName, clusterConfig, ecuPtr, sendList);
        }
    }

    void FlexRayDevice::GetVariables(std::string &vars, std::string &des) const {
        //watchdog
        auto watchdogName = deviceConfig->GetDataPtr()->Config.Chn.WatchDog;
        if(!watchdogName.empty()) {
            vars += watchdogName + ',';
            des += watchdogName + ',';
        }
        //signal
        for(const auto &msg : deviceConfig->GetDataPtr()->Config.Chn.Frames)
            for(const auto &sign : msg.Signals){
                if(!sign.Variable.empty()) {
                    vars += sign.Variable + ',';
                    des += sign.Variable + ',';
                }
            }

    }

    void FlexRayDevice::GetTimingInfo(double &freq, int &processor, int &priority) const {

    }
}
