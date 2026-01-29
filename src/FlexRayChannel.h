//
// Created by 79933 on 2025/11/25.
//

#ifndef SERVERDEVICE_FLEXRAY_FLEXRAYCHANNEL_H
#define SERVERDEVICE_FLEXRAY_FLEXRAYCHANNEL_H

#include <set>
#include <unordered_map>

#include "flexraywrapper/flexraywrapper.h"
#include "varmanager/varmanager.h"
#include "bytedecoder/byte_decoder.h"
#include "Common/mtestserver_common.h"
#include "FlexRayConfig.h"
#include "FlexRayTools.h"

namespace FlexRay {
    struct FrameData {
        uint16_t slot;
        uint8_t cycle;
        uint8_t dataLength;
        uint8_t data[254]{};
        std::vector<FlexRayConfig::Signal> signals;

        FrameData(uint16_t slot, uint8_t cycle, uint8_t dataLength, std::vector<FlexRayConfig::Signal> &signals) :
                slot(slot), cycle(cycle), dataLength(dataLength), signals(std::move(signals)) {}
    };

    int32_t GetPath(char *libPath, char *logPath);

    class FlexRayChannel {
    private:
        void *con;
        void *channelPtr;
        std::shared_ptr<FlexRayConfig::Channel> channelConfig;
        std::vector<int> frameList; //message Config
        int32_t errorCode;
        uint8_t sendCycle = 0;

        std::unordered_map<uint16_t, FrameData> txFrames;
        std::unordered_map<uint16_t, FrameData> rxFrames;
        std::unordered_map<uint16_t, void *> txDecodePtr;
        std::unordered_map<uint16_t, void *> rxDecodePtr;
        std::vector<std::set<uint16_t>> sendList;
//        std::string txVars;
//        std::string rxVars;

        //uint is milliseconds
//        std::vector<uint32_t> txTerm;
        std::vector<uint32_t> rxTerm;
        uint32_t timePos = 1;

    public:
        explicit FlexRayChannel(void *con, char *deviceString, ClusterConfig *clusterConfig, FlexRayConfig::Channel *chnConfig);

        ~FlexRayChannel();

        int32_t SendMessage_();

        int32_t RecMessage();

        void AddTimePos();

        int32_t GetErrorCode() const;
    };
}


#endif //SERVERDEVICE_FLEXRAY_FLEXRAYCHANNEL_H
