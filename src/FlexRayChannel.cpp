//
// Created by 79933 on 2025/11/25.
//
#include "FlexRayChannel.h"

namespace FlexRay {
    int32_t GetPath(char *libPath_, char *logPath_){
        char path[200];
        int32_t size = 200;
        auto res = mtest_config_get(CFG_BIN_PATH, path, &size);
        if(!res)
            return -1;
        std::string libPath = path;
        if(libPath.empty())
            libPath = R"(D:\Github\MTestServer\Library\FlexRayPack\FlexRayWrapper\wrapper)";
        else{
            auto pt = SplitPath(libPath);
            if(pt.second != "Bin") {
                libPath = pt.first + "/FlexRayPack/FlexRayWrapper/wrapper";
            }
        }

        res = mtest_config_get(CFG_BIN_PATH, path, &size);
        if (!res)
            return -2;
        std::string logPath = NormalizePath(path);
        libPath.copy(libPath_, libPath.length());
        logPath.copy(logPath_, logPath.length());
        return res;
    }

    FlexRayChannel::FlexRayChannel(void *con, char *deviceString, ClusterConfig *clusterConfig, FlexRayConfig::Channel *ecuConfig) : con(con), channelConfig(ecuConfig) {
        auto &frames = ecuConfig->Frames;
        std::vector<uint16_t> frameConfig;
        frameConfig.emplace_back(0);
        //set channel param;
        std::string txName{};
        std::string rxName{};
        for(auto &f : frames){
            if(f.TxOrRx) {
                txFrames.emplace_back(f.Sold, f.CycleRepetition + f.BaseCycle, f.PayloadLength, f.Signals);
                txTerm.emplace_back(1000/f.Frequency);
                frameConfig.emplace_back(f.Sold);
                frameConfig.emplace_back(f.CycleRepetition + f.BaseCycle);
                frameConfig.emplace_back(f.Config);
                frameConfig.emplace_back(f.PayloadLength);
                frameConfig[0]++;
                for(auto &sign : f.Signals)
                    txName += sign.Variable + ',';
                txName.pop_back();
                auto ptr = create_signal_decoder(con, txName.data(), 0, 0);
                txDecodePtr.push_back(ptr);
            } else {
                rxFrames.emplace_back(f.Sold, f.CycleRepetition + f.BaseCycle, f.PayloadLength, f.Signals);
                rxTerm.emplace_back(1000/f.Frequency);
                for(auto &sign : f.Signals)
                    rxName += sign.Variable + ',';
                rxName.pop_back();
                auto ptr = create_signal_decoder(con, rxName.data(), 0, 0);
                rxDecodePtr.push_back(ptr);
            }
        }

        auto res = fr_set_channel_config(&channelPtr, deviceString, frameConfig.data(), clusterConfig, &ecuConfig->EcuConfig);
        if (!res)
            errorCode = -5001;
        res = fr_open_channel(channelPtr);
        if (!res)
            errorCode = -5002;
    }

    FlexRayChannel::~FlexRayChannel() {
        for(auto &ptr : txDecodePtr)
            free_signal_decoder(ptr);
        for(auto &ptr : rxDecodePtr)
            free_signal_decoder(ptr);
        fr_close_channel(channelPtr);
    }

    int32_t FlexRayChannel::SendMessage() {
        //process frames
        uint8_t data[254]{};
        double value = 0;
        uint16_t pos = 0;
        for (uint32_t i = 0; i < txFrames.size(); i++){
            if(!(timePos%txTerm[i])){
                //encode
                signal_decoder(txDecodePtr[i], data, txFrames[i].dataLength);
                if(fr_set_message(channelPtr, txFrames[i].slot, txFrames[i].cycle, txFrames[i].dataLength, data, 100))
                    return -1;
            }
        }
        return 0;
    }

    int32_t FlexRayChannel::RecMessage() {
        uint16_t item = 0;
        uint16_t slot[100];
        uint8_t cycle[100];
        uint8_t dataLength[100];
        uint8_t data[25400]{};

        if(fr_get_messages(channelPtr, &item, slot, cycle, dataLength, data, 100))
            return -1;

        for(uint32_t i = 0; i < item; i++){
            for(uint32_t j = 0; j < rxFrames.size(); j++){
                if(rxFrames[j].slot == slot[i])
                    signal_decoder(rxDecodePtr[j], rxFrames[j].data, rxFrames[j].dataLength);
            }
        }
        return 0;
    }

    void FlexRayChannel::AddTimePos() {
        timePos++;
        if(timePos > 1000)
            timePos = 1;
    }

    int32_t FlexRayChannel::GetErrorCode() const { return errorCode; }
}
