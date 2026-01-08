//
// Created by 79933 on 2025/11/27.
//

#include "FlexRayConfig.h"

#include <sstream>

namespace FlexRay {
    FlexRayConfig::FlexRayConfig(const std::string &config) {
        errorString = "";
        errorFlag = !ParseDeviceData(config);
    }

    std::shared_ptr<FlexRayConfig> FlexRayConfig::Create(const std::string &json) {
        auto ptr = std::make_shared<FlexRayConfig>(json);
        return ptr;
    }

    bool FlexRayConfig::ParseDeviceData(const std::string &defaultStr) {
        auto data = std::make_unique<DeviceData>();
        rapidjson::Document doc;
        if (doc.Parse(defaultStr.c_str()).HasParseError()) {
            errorString = "JSON parsing failed";
            return false;
        }

        if (!doc.HasMember("DeviceInfo") || !doc["DeviceInfo"].IsObject()) {
            errorString = "Missing or invalid DeviceInfo";
            return false;
        }

        if (!ParseDeviceInfo(doc["DeviceInfo"], data->Info)) {
            errorString += "Failed to parse DeviceInfo";
            return false;
        }

        if (!doc.HasMember("DeviceConfig") || !doc["DeviceConfig"].IsObject()) {
            errorString = "Missing or invalid DeviceConfig";
            return false;
        }

        if (!ParseDeviceConfig(doc["DeviceConfig"], data->Config)) {
            errorString += "Failed to parse DeviceConfig";
            return false;
        }
        dataPtr = std::move(data);
        return true;
    }

    bool FlexRayConfig::ParseDeviceConfig(const rapidjson::Value &json, DeviceConfig &config) {
        if (!json.IsObject()) {
            errorString = "DeviceConfig is not an object";
            return false;
        }

        if (!json.HasMember("FlexRay") || !json["FlexRay"].IsString()) {
            errorString = "Missing or invalid device config FlexRay";
            return false;
        }
        config.FlexRay = json["FlexRay"].GetString();

        if (!json.HasMember("SerialNumber") || !json["SerialNumber"].IsString()) {
            errorString = "Missing or invalid device config SerialNumber";
            return false;
        }
        config.SerialNumber = json["SerialNumber"].GetString();

        if (!json.HasMember("ClusterConfig") || !json["ClusterConfig"].IsObject()) {
            errorString = "ClusterConfig";
            return false;
        }
        if (!ParseClusterConfig(json["ClusterConfig"], config.ClusterConfig)) {
            errorString += "Failed to parse Cluster Config";
            return false;
        }

//        if (!json.HasMember("EcuList") || !json["EcuList"].IsArray()) {
//            errorString = "Missing or invalid device config Channel List";
//            return false;
//        }
//        const rapidjson::Value &ecuList = json["EcuList"];
//        for (rapidjson::SizeType i = 0; i < ecuList.Size(); i++) {
//            Channel ecu;
//            if (!ParseChannel(ecuList[i], ecu)) {
//                errorString += "Failed to parse Channel";
//                return false;
//            }
//            if (i == 0)
//                config.Chn = ecu;
//            config.EcuList.push_back(ecu);
//        }


        if(!json.HasMember("Chn") || json["Chn"].IsObject()) {
            errorString = "Missing or invalid device config Chn";
            return false;
        }
        if (!ParseChannel(json["Chn"], config.Chn)) {
            errorString += "Failed to parse Channel";
            return false;
        }

        return true;
    }

    bool FlexRayConfig::ParseClusterConfig(const rapidjson::Value &json, ClusterConfig &cluster) {
        if (!json.IsObject()) {
            errorString = "Cluster Config is not an object";
            return false;
        }

        if (!json.HasMember("ChannelAConnectedNode") || !json["ChannelAConnectedNode"].IsUint()) {
            errorString = "Missing or invalid cluster config ChannelAConnectedNode";
            return false;
        }
        cluster.ChannelAConnectedNode = json["ChannelAConnectedNode"].GetUint();

        if (!json.HasMember("ChannelBConnectedNode") || !json["ChannelBConnectedNode"].IsUint()) {
            errorString = "Missing or invalid cluster config ChannelBConnectedNode";
            return false;
        }
        cluster.ChannelBConnectedNode = json["ChannelBConnectedNode"].GetUint();

        if (!json.HasMember("ChannelASymbolTransmitted") || !json["ChannelASymbolTransmitted"].IsUint()) {
            errorString = "Missing or invalid cluster config ChannelASymbolTransmitted";
            return false;
        }
        cluster.ChannelASymbolTransmitted = json["ChannelASymbolTransmitted"].GetUint();

        if (!json.HasMember("ChannelBSymbolTransmitted") || !json["ChannelBSymbolTransmitted"].IsUint()) {
            errorString = "Missing or invalid cluster config ChannelBSymbolTransmitted";
            return false;
        }
        cluster.ChannelBSymbolTransmitted = json["ChannelBSymbolTransmitted"].GetUint();

        if (!json.HasMember("Speed") || !json["Speed"].IsUint()) {
            errorString = "Missing or invalid cluster config Speed";
            return false;
        }
        cluster.Speed = json["Speed"].GetUint();

        if (!json.HasMember("ColdStartAttempts") || !json["ColdStartAttempts"].IsUint()) {
            errorString = "Missing or invalid cluster config ColdStartAttempts";
            return false;
        }
        cluster.ColdStartAttempts = json["ColdStartAttempts"].GetUint();

        if (!json.HasMember("ActionPointOffset") || !json["ActionPointOffset"].IsUint()) {
            errorString = "Missing or invalid cluster config ActionPointOffset";
            return false;
        }
        cluster.ActionPointOffset = json["ActionPointOffset"].GetUint();

        if (!json.HasMember("DynamicSlotIdlePhase") || !json["DynamicSlotIdlePhase"].IsUint()) {
            errorString = "Missing or invalid cluster config DynamicSlotIdlePhase";
            return false;
        }
        cluster.DynamicSlotIdlePhase = json["DynamicSlotIdlePhase"].GetUint();

        if (!json.HasMember("MiniSlot") || !json["MiniSlot"].IsUint()) {
            errorString = "Missing or invalid cluster config MiniSlot";
            return false;
        }
        cluster.MiniSlot = json["MiniSlot"].GetUint();

        if (!json.HasMember("MiniSlotActionPointOffset") || !json["MiniSlotActionPointOffset"].IsUint()) {
            errorString = "Missing or invalid cluster config MiniSlotActionPointOffset";
            return false;
        }
        cluster.MiniSlotActionPointOffset = json["MiniSlotActionPointOffset"].GetUint();

        if (!json.HasMember("NetworkIdleTime") || !json["NetworkIdleTime"].IsUint()) {
            errorString = "Missing or invalid cluster config NetworkIdleTime";
            return false;
        }
        cluster.NetworkIdleTime = json["NetworkIdleTime"].GetUint();

        if (!json.HasMember("SampleClockPeriod") || !json["SampleClockPeriod"].IsDouble()) {
            errorString = "Missing or invalid cluster config SampleClockPeriod";
            return false;
        }
        cluster.SampleClockPeriod = json["SampleClockPeriod"].GetDouble();

        if (!json.HasMember("StaticSlot") || !json["StaticSlot"].IsUint()) {
            errorString = "Missing or invalid cluster config StaticSlot";
            return false;
        }
        cluster.StaticSlot = json["StaticSlot"].GetUint();

        if (!json.HasMember("SymbolWindow") || !json["SymbolWindow"].IsUint()) {
            errorString = "Missing or invalid cluster config SymbolWindow";
            return false;
        }
        cluster.SymbolWindow = json["SymbolWindow"].GetUint();

        if (!json.HasMember("TimeSymbolStateTransmitter") || !json["TimeSymbolStateTransmitter"].IsUint()) {
            errorString = "Missing or invalid cluster config TimeSymbolStateTransmitter";
            return false;
        }
        cluster.TimeSymbolStateTransmitter = json["TimeSymbolStateTransmitter"].GetUint();

        if (!json.HasMember("WakeUpSymbolRXIdle") || !json["WakeUpSymbolRXIdle"].IsUint()) {
            errorString = "Missing or invalid cluster config WakeUpSymbolRXIdle";
            return false;
        }
        cluster.WakeUpSymbolRXIdle = json["WakeUpSymbolRXIdle"].GetUint();

        if (!json.HasMember("WakeUpSymbolRXLow") || !json["WakeUpSymbolRXLow"].IsUint()) {
            errorString = "Missing or invalid cluster config WakeUpSymbolRXLow";
            return false;
        }
        cluster.WakeUpSymbolRXLow = json["WakeUpSymbolRXLow"].GetUint();

        if (!json.HasMember("WakeUpSymbolRXWindow") || !json["WakeUpSymbolRXWindow"].IsUint()) {
            errorString = "Missing or invalid cluster config WakeUpSymbolRXWindow";
            return false;
        }
        cluster.WakeUpSymbolRXWindow = json["WakeUpSymbolRXWindow"].GetUint();

        if (!json.HasMember("WakeUpSymbolTXIdle") || !json["WakeUpSymbolTXIdle"].IsUint()) {
            errorString = "Missing or invalid cluster config WakeUpSymbolTXIdle";
            return false;
        }
        cluster.WakeUpSymbolTXIdle = json["WakeUpSymbolTXIdle"].GetUint();

        if (!json.HasMember("WakeUpSymbolTXLow") || !json["WakeUpSymbolTXLow"].IsUint()) {
            errorString = "Missing or invalid cluster config WakeUpSymbolTXLow";
            return false;
        }
        cluster.WakeUpSymbolTXLow = json["WakeUpSymbolTXLow"].GetUint();

        if (!json.HasMember("ListenNoise") || !json["ListenNoise"].IsUint()) {
            errorString = "Missing or invalid cluster config ListenNoise";
            return false;
        }
        cluster.ListenNoise = json["ListenNoise"].GetUint();

        if (!json.HasMember("MacroPerCycle") || !json["MacroPerCycle"].IsUint()) {
            errorString = "Missing or invalid cluster config MacroPerCycle";
            return false;
        }
        cluster.MacroPerCycle = json["MacroPerCycle"].GetUint();

        if (!json.HasMember("MacroTick") || !json["MacroTick"].IsDouble()) {
            errorString = "Missing or invalid cluster config MacroTick";
            return false;
        }
        cluster.MacroTick = json["MacroTick"].GetDouble();

        if (!json.HasMember("MaxInitializationError") || !json["MaxInitializationError"].IsDouble()) {
            errorString = "Missing or invalid cluster config MaxInitializationError";
            return false;
        }
        cluster.MaxInitializationError = json["MaxInitializationError"].GetDouble();

        if (!json.HasMember("MaxWithoutClockCorrectionFatal") || !json["MaxWithoutClockCorrectionFatal"].IsUint()) {
            errorString = "Missing or invalid cluster config MaxWithoutClockCorrectionFatal";
            return false;
        }
        cluster.MaxWithoutClockCorrectionFatal = json["MaxWithoutClockCorrectionFatal"].GetUint();

        if (!json.HasMember("MaxWithoutClockCorrectionPassive") || !json["MaxWithoutClockCorrectionPassive"].IsUint()) {
            errorString = "Missing or invalid cluster config MaxWithoutClockCorrectionPassive";
            return false;
        }
        cluster.MaxWithoutClockCorrectionPassive = json["MaxWithoutClockCorrectionPassive"].GetUint();

        if (!json.HasMember("NetworkManagementVectorLength") || !json["NetworkManagementVectorLength"].IsUint()) {
            errorString = "Missing or invalid cluster config NetworkManagementVectorLength";
            return false;
        }
        cluster.NetworkManagementVectorLength = json["NetworkManagementVectorLength"].GetUint();

        if (!json.HasMember("NumberOfMiniSlots") || !json["NumberOfMiniSlots"].IsUint()) {
            errorString = "Missing or invalid cluster config NumberOfMiniSlots";
            return false;
        }
        cluster.NumberOfMiniSlots = json["NumberOfMiniSlots"].GetUint();

        if (!json.HasMember("NumberOfStaticSlots") || !json["NumberOfStaticSlots"].IsUint()) {
            errorString = "Missing or invalid cluster config NumberOfStaticSlots";
            return false;
        }
        cluster.NumberOfStaticSlots = json["NumberOfStaticSlots"].GetUint();

        if (!json.HasMember("OffsetCorrectionStart") || !json["OffsetCorrectionStart"].IsUint()) {
            errorString = "Missing or invalid cluster config OffsetCorrectionStart";
            return false;
        }
        cluster.OffsetCorrectionStart = json["OffsetCorrectionStart"].GetUint();

        if (!json.HasMember("PayloadLengthStatic") || !json["PayloadLengthStatic"].IsUint()) {
            errorString = "Missing or invalid cluster config PayloadLengthStatic";
            return false;
        }
        cluster.PayloadLengthStatic = json["PayloadLengthStatic"].GetUint();

        if (!json.HasMember("SyncNodeMax") || !json["SyncNodeMax"].IsUint()) {
            errorString = "Missing or invalid cluster config SyncNodeMax";
            return false;
        }
        cluster.SyncNodeMax = json["SyncNodeMax"].GetUint();

        if (!json.HasMember("CasRXLowMax") || !json["CasRXLowMax"].IsUint()) {
            errorString = "Missing or invalid cluster config CasRXLowMax";
            return false;
        }
        cluster.CasRXLowMax = json["CasRXLowMax"].GetUint();

        if (!json.HasMember("CasRXLowMin") || !json["CasRXLowMin"].IsUint()) {
            errorString = "Missing or invalid cluster config CasRXLowMin";
            return false;
        }
        cluster.CasRXLowMin = json["CasRXLowMin"].GetUint();

        if (!json.HasMember("Bit") || !json["Bit"].IsDouble()) {
            errorString = "Missing or invalid cluster config Bit";
            return false;
        }
        cluster.Bit = json["Bit"].GetDouble();

        if (!json.HasMember("Cycle") || !json["Cycle"].IsUint()) {
            errorString = "Missing or invalid cluster config Cycle";
            return false;
        }
        cluster.Cycle = json["Cycle"].GetUint();

        if (!json.HasMember("ClusterDriftDamping") || !json["ClusterDriftDamping"].IsUint()) {
            errorString = "Missing or invalid cluster config ClusterDriftDamping";
            return false;
        }
        cluster.ClusterDriftDamping = json["ClusterDriftDamping"].GetUint();

        if (!json.HasMember("OffsetCorrectionMax") || !json["OffsetCorrectionMax"].IsDouble()) {
            errorString = "Missing or invalid cluster config OffsetCorrectionMax";
            return false;
        }
        cluster.OffsetCorrectionMax = json["OffsetCorrectionMax"].GetDouble();

        return true;
    }

    bool FlexRayConfig::ParseDeviceInfo(const rapidjson::Value &json, DeviceInfo &info) {
        if (!json.IsObject()) {
            errorString = "DeviceInfo is not an object";
            return false;
        }

        if (!json.HasMember("DeviceName") || !json["DeviceName"].IsString()) {
            errorString = "Missing or invalid DeviceName";
            return false;
        }
        info.DeviceName = json["DeviceName"].GetString();

        if (!json.HasMember("DeviceID") || !json["DeviceID"].IsInt()) {
            errorString = "Missing or invalid DeviceID";
            return false;
        }
        info.DeviceID = json["DeviceID"].GetInt();

        if (!json.HasMember("DeviceType") || json["DeviceType"].IsString()) {
            errorString = "Missing or invalid DeviceType";
            return false;
        }
        info.DeviceType = json["DeviceType"].GetString();

        if (!json.HasMember("DeviceDes") || !json["DeviceDes"].IsString()) {
            errorString = "Missing or invalid DeviceDes";
            return false;
        }
        info.DeviceDes = json["DeviceDes"].GetString();

        if (!json.HasMember("Version") || !json["Version"].IsInt()) {
            errorString = "Missing or invalid Version";
            return false;
        }
        info.Version = json["Version"].GetInt();

        if (!json.HasMember("Author") || !json["Author"].IsString()) {
            errorString = "Missing or invalid Author";
            return false;
        }
        info.Author = json["Author"].GetString();

        if (!json.HasMember("CreateTime") || !json["CreateTime"].IsString()) {
            errorString = "Missing or invalid CreateTime";
            return false;
        }
        info.CreateTime = json["CreateTime"].GetString();

        if (!json.HasMember("Reviser") || !json["Reviser"].GetString()) {
            errorString = "Missing or invalid Reviser";
            return false;
        }
        info.Reviser = json["Reviser"].GetString();

        if (!json.HasMember("ModifyTime") || !json["ModifyTime"].IsString()) {
            errorString = "Missing or invalid ModifyTime";
            return false;
        }
        info.ModifyTime = json["ModifyTime"].GetString();

        return true;
    }

    bool FlexRayConfig::ParseChannel(const rapidjson::Value &json, Channel &chn) {
        if (!json.IsObject()) {
            errorString = "Channel is not an object";
            return false;
        }

        if (!json.HasMember("Name") || !json["Name"].IsString()) {
            errorString = "Missing or invalid Channel Name";
            return false;
        }
        chn.Name = json["Name"].GetString();

        if (!json.HasMember("ID") || !json["ID"].IsInt()) {
            errorString = "Missing or invalid Channel ID";
            return false;
        }
        chn.ID = json["ID"].GetInt();

        if (!json.HasMember("UseDefault") || !json["UseDefault"].IsBool()) {
            errorString = "Missing or invalid Channel Use Default";
            return false;
        }
        chn.UseDefault = json["UseDefault"].GetBool();

        if (!json.HasMember("UseMaxMin") || !json["UseMaxMin"].IsBool()) {
            errorString = "Missing or invalid Channel Use Max or Min";
            return false;
        }
        chn.UseMaxMin = json["UseMaxMin"].GetBool();

        if (!json.HasMember("BridgePattern") || !json["BridgePattern"].IsBool()) {
            errorString = "Missing or invalid Channel Bridge Pattern";
            return false;
        }
        chn.BridgePattern = json["BridgePattern"].GetBool();

        if (!json.HasMember("Termination") || !json["Termination"].IsBool()) {
            errorString = "Missing or invalid Channel Termination";
            return false;
        }
        chn.Termination = json["Termination"].GetBool();

        if (!json.HasMember("HardwareTiming") || !json["HardwareTiming"].IsBool()) {
            errorString = "Missing or invalid Channel Hardware Timing";
            return false;
        }
        chn.HardwareTiming = json["HardwareTiming"].GetBool();


        if (!json.HasMember("Description") || !json["Description"].IsString()) {
            errorString = "Missing or invalid Channel Description";
            return false;
        }
        chn.Description = json["Description"].GetString();

        if (!json.HasMember("WatchDog") || !json["WatchDog"].IsString()) {
            errorString = "Missing or invalid Channel WatchDog";
            return false;
        }
        chn.WatchDog = json["WatchDog"].GetString();

        if (!json.HasMember("Frames") || !json["Frames"].IsArray()) {
            errorString = "Missing or invalid Frames";
            return false;
        }

        const rapidjson::Value &messages = json["messages"];
        for (rapidjson::SizeType i = 0; i < messages.Size(); i++) {
            Frame message;
            if (!ParseFrame(messages[i], message)) {
                errorString += "Failed to parse message";
                return false;
            }
            chn.Frames.push_back(message);
        }

        return true;
    }

    bool FlexRayConfig::ParseChannelConfig(const rapidjson::Value &jsonStr, ECUConfig &chnConfig) {
        if (!jsonStr.IsObject()) {
            errorString = "ECUConfig is not an object";
            return false;
        }

        if (!jsonStr.HasMember("StartUpSync") || !jsonStr["StartUpSync"].IsUint()) {
            errorString = "Missing or invalid Channel Config StartUpSync";
            return false;
        }
        chnConfig.StartUpSync = jsonStr["StartUpSync"].GetUint();

        if (!jsonStr.HasMember("MaxDynamicPayloadLength") || !jsonStr["MaxDynamicPayloadLength"].IsUint()) {
            errorString = "Missing or invalid Channel Config MaxDynamicPayloadLength";
            return false;
        }
        chnConfig.MaxDynamicPayloadLength = jsonStr["MaxDynamicPayloadLength"].GetUint();

        if (!jsonStr.HasMember("ClusterDriftDamping") || !jsonStr["ClusterDriftDamping"].IsUint()) {
            errorString = "Missing or invalid Channel Config ClusterDriftDamping";
            return false;
        }
        chnConfig.ClusterDriftDamping = jsonStr["ClusterDriftDamping"].GetUint();

        if (!jsonStr.HasMember("DecodingCorrection") || !jsonStr["DecodingCorrection"].IsUint()) {
            errorString = "Missing or invalid Channel Config DecodingCorrection";
            return false;
        }
        chnConfig.DecodingCorrection = jsonStr["DecodingCorrection"].GetUint();

        if (!jsonStr.HasMember("ListenTimeout") || !jsonStr["ListenTimeout"].IsUint()) {
            errorString = "Missing or invalid Channel Config ListenTimeout";
            return false;
        }
        chnConfig.ListenTimeout = jsonStr["ListenTimeout"].GetUint();

        if (!jsonStr.HasMember("MaxDrift") || !jsonStr["MaxDrift"].IsUint()) {
            errorString = "Missing or invalid Channel Config MaxDrift";
            return false;
        }
        chnConfig.MaxDrift = jsonStr["MaxDrift"].GetUint();

        if (!jsonStr.HasMember("ExternOffsetCorrection") || !jsonStr["ExternOffsetCorrection"].IsUint()) {
            errorString = "Missing or invalid Channel Config ExternOffsetCorrection";
            return false;
        }
        chnConfig.ExternOffsetCorrection = jsonStr["ExternOffsetCorrection"].GetUint();

        if (!jsonStr.HasMember("ExternRateCorrection") || !jsonStr["ExternRateCorrection"].IsUint()) {
            errorString = "Missing or invalid Channel Config ExternRateCorrection";
            return false;
        }
        chnConfig.ExternRateCorrection = jsonStr["ExternRateCorrection"].GetUint();

        if (!jsonStr.HasMember("LatestTX") || !jsonStr["LatestTX"].IsUint()) {
            errorString = "Missing or invalid Channel Config LatestTX";
            return false;
        }
        chnConfig.LatestTX = jsonStr["LatestTX"].GetUint();

        if (!jsonStr.HasMember("MicroPerCycle") || !jsonStr["MicroPerCycle"].IsUint()) {
            errorString = "Missing or invalid Channel Config MicroPerCycle";
            return false;
        }
        chnConfig.MicroPerCycle = jsonStr["MicroPerCycle"].GetUint();

        if (!jsonStr.HasMember("OffsetCorrectionOut") || !jsonStr["OffsetCorrectionOut"].IsUint()) {
            errorString = "Missing or invalid Channel Config OffsetCorrectionOut";
            return false;
        }
        chnConfig.OffsetCorrectionOut = jsonStr["OffsetCorrectionOut"].GetUint();

        if (!jsonStr.HasMember("RateCorrectionOut") || !jsonStr["RateCorrectionOut"].IsUint()) {
            errorString = "Missing or invalid Channel RateCorrectionOut";
            return false;
        }
        chnConfig.RateCorrectionOut = jsonStr["RateCorrectionOut"].GetUint();

        if (!jsonStr.HasMember("SamplesPerMicroTick") || !jsonStr["SamplesPerMicroTick"].IsUint()) {
            errorString = "Missing or invalid Channel SamplesPerMicroTick";
            return false;
        }
        chnConfig.SamplesPerMicroTick = jsonStr["SamplesPerMicroTick"].GetUint();

        if (!jsonStr.HasMember("DelayCompensationA") || !jsonStr["DelayCompensationA"].IsUint()) {
            errorString = "Missing or invalid Channel DelayCompensationA";
            return false;
        }
        chnConfig.DelayCompensationA = jsonStr["DelayCompensationA"].GetUint();

        if (!jsonStr.HasMember("DelayCompensationB") || !jsonStr["DelayCompensationB"].IsUint()) {
            errorString = "Missing or invalid Channel DelayCompensationB";
            return false;
        }
        chnConfig.DelayCompensationB = jsonStr["DelayCompensationB"].GetUint();

        if (!jsonStr.HasMember("WakeUpPattern") || !jsonStr["WakeUpPattern"].IsUint()) {
            errorString = "Missing or invalid Channel Config WakeUpPattern";
            return false;
        }
        chnConfig.WakeUpPattern = jsonStr["WakeUpPattern"].GetUint();

        if (!jsonStr.HasMember("AllowHaltDueToClock") || !jsonStr["AllowHaltDueToClock"].IsUint()) {
            errorString = "Missing or invalid Channel Config AllowHaltDueToClock";
            return false;
        }
        chnConfig.AllowHaltDueToClock = jsonStr["AllowHaltDueToClock"].GetUint();

        if (!jsonStr.HasMember("AllowPassiveToAction") || !jsonStr["AllowPassiveToAction"].IsUint()) {
            errorString = "Missing or invalid Channel Config AllowPassiveToAction";
            return false;
        }
        chnConfig.AllowPassiveToAction = jsonStr["AllowPassiveToAction"].GetUint();

        if (!jsonStr.HasMember("AcceptedStartUpRange") || !jsonStr["AcceptedStartUpRange"].IsUint()) {
            errorString = "Missing or invalid Channel Config AcceptedStartUpRange";
            return false;
        }
        chnConfig.AcceptedStartUpRange = jsonStr["AcceptedStartUpRange"].GetUint();

        if (!jsonStr.HasMember("MacroInitialOffsetA") || !jsonStr["MacroInitialOffsetA"].IsUint()) {
            errorString = "Missing or invalid Channel Config MacroInitialOffsetA";
            return false;
        }
        chnConfig.MacroInitialOffsetA = jsonStr["MacroInitialOffsetA"].GetUint();

        if (!jsonStr.HasMember("MacroInitialOffsetB") || !jsonStr["MacroInitialOffsetB"].IsUint()) {
            errorString = "Missing or invalid Channel Config MacroInitialOffsetB";
            return false;
        }
        chnConfig.MacroInitialOffsetB = jsonStr["MacroInitialOffsetB"].GetUint();

        if (!jsonStr.HasMember("MicroInitialOffsetA") || !jsonStr["MicroInitialOffsetA"].IsUint()) {
            errorString = "Missing or invalid Channel Config MicroInitialOffsetA";
            return false;
        }
        chnConfig.MicroInitialOffsetA = jsonStr["MicroInitialOffsetA"].GetUint();

        if (!jsonStr.HasMember("MircoInitialOffsetB") || !jsonStr["MircoInitialOffsetB"].IsUint()) {
            errorString = "Missing or invalid Channel Config MircoInitialOffsetB";
            return false;
        }
        chnConfig.MircoInitialOffsetB = jsonStr["MircoInitialOffsetB"].GetUint();

//        if (!jsonStr.HasMember("SingleSlotEnabled") || !jsonStr["SingleSlotEnabled"].IsUint()) {
//            errorString = "Missing or invalid Channel Config SingleSlotEnabled";
//            return false;
//        }
//        chnConfig.SingleSlotEnabled = jsonStr["SingleSlotEnabled"].GetUint();

        if (!jsonStr.HasMember("MicroTick") || !jsonStr["MicroTick"].IsDouble()) {
            errorString = "Missing or invalid Channel Config MicroTick";
            return false;
        }
        chnConfig.MicroTick = jsonStr["MicroTick"].GetDouble();

        return true;
    }

    bool FlexRayConfig::ParseFrame(const rapidjson::Value &json, Frame &message) {
        if (!json.IsObject()) {
            errorString = "Frame is not an object";
            return false;
        }

        if (!json.HasMember("ID") || !json["ID"].IsUint()) {
            errorString = "Missing or invalid is Frame ID";
            return false;
        }
        message.ID = json["ID"].GetUint();

        if (!json.HasMember("Name") || !json["Name"].IsString()) {
            errorString = "Missing or invalid is Frame Name";
            return false;
        }
        message.Name = json["Name"].GetString();

        if (!json.HasMember("TxOrRx") || !json["TxOrRx"].IsBool()) {
            errorString = "Missing or invalid is Frame Tx or Rx";
            return false;
        }
        message.TxOrRx = json["TxOrRx"].GetBool();

        if (!json.HasMember("Frequency") || !json["Frequency"].IsUint()) {
            errorString = "Missing or invalid is Frame Frequency";
            return false;
        }
        message.Frequency = json["Frequency"].GetUint();

        if (!json.HasMember("Type") || !json["Type"].IsUint()) {
            errorString = "Missing or invalid is Frame Type";
            return false;
        }
        message.Type = json["Type"].GetUint();

        if (!json.HasMember("Sold") || !json["Sold"].IsUint()) {
            errorString = "Missing or invalid is Frame Sold";
            return false;
        }
        message.Sold = json["Sold"].GetUint();

        if (!json.HasMember("CycleRepetition") || !json["CycleRepetition"].IsUint()) {
            errorString = "Missing or invalid is Frame Cycle Repetition";
            return false;
        }
        message.CycleRepetition = json["CycleRepetition"].GetUint();

        if (!json.HasMember("BaseCycle") || !json["BaseCycle"].IsUint()) {
            errorString = "Missing or invalid is Frame Base Base Cycle";
            return false;
        }
        message.BaseCycle = json["BaseCycle"].GetUint();

        if (!json.HasMember("InCycleRepetition") || !json["InCycleRepetition"].IsUint()) {
            errorString = "Missing or invalid is Frame Base In Cycle Repetition";
            return false;
        }
        message.InCycleRepetition = json["InCycleRepetition"].GetUint();

        if (!json.HasMember("PayloadLength") || !json["PayloadLength"].IsUint()) {
            errorString = "Missing or invalid is Frame Data Payload Length";
            return false;
        }
        message.PayloadLength = json["PayloadLength"].GetUint();

        if (!json.HasMember("Description") || !json["HasMember"].IsString()) {
            errorString = "Missing or invalid is Frame Description";
            return false;
        }
        message.Description = json["Description"].GetString();

        if (!json.HasMember("Signals") || !json["Signals"].IsArray()) {
            errorString = "Missing or invalid is Frame Signals";
            return false;
        }
        const rapidjson::Value &signals = json["Signals"];
        for (rapidjson::SizeType i = 0; i < signals.Size(); i++) {
            Signal signal;
            if (!ParseSignal(signals[i], signal)) {
                errorString += "Failed to parse Signal";
                return false;
            }
            message.Signals.push_back(signal);
        }
        return true;
    }

    bool FlexRayConfig::ParseSignal(const rapidjson::Value &json, Signal &signal) {
        if (!json.IsObject()) {
            errorString = "Signal is not an object";
            return false;
        }

        if (!json.HasMember("ID") || !json["ID"].IsInt()) {
            errorString = "Missing or invalid is Signal ID";
            return false;
        }
        signal.ID = json["ID"].GetInt();

        if (!json.HasMember("Name") || !json["Name"].IsString()) {
            errorString = "Missing or invalid is Signal Name";
            return false;
        }
        signal.Name = json["Name"].GetString();

        if (!json.HasMember("Variable") || !json["Variable"].IsString()) {
            errorString = "Missing or invalid is Signal Variable";
            return false;
        }
        signal.Variable = json["Variable"].GetString();

        if (!json.HasMember("Unit") || !json["Unit"].IsString()) {
            errorString = "Missing or invalid is Signal Unit";
            return false;
        }
        signal.Unit = json["Unit"].GetString();

        if (!json.HasMember("Gain") || !json["Gain"].IsInt()) {
            errorString = "Missing or invalid is Signal Gain";
            return false;
        }
        signal.Gain = json["Gain"].GetInt();

        if (!json.HasMember("Offset") || !json["Offset"].IsInt()) {
            errorString = "Missing or invalid is Signal Offset";
            return false;
        }
        signal.Offset = json["Offset"].GetInt();

        if (!json.HasMember("StartBit") || !json["StartBit"].IsInt()) {
            errorString = "Missing or invalid is Signal StartBit";
            return false;
        }
        signal.StartBit = json["StartBit"].GetInt();

        if (!json.HasMember("NumBits") || !json["NumBits"].IsInt()) {
            errorString = "Missing or invalid is Signal NumBits";
            return false;
        }
        signal.NumBits = json["NumBits"].GetInt();

        if (!json.HasMember("DefaultValue") || !json["DefaultValue"].IsDouble()) {
            errorString = "Missing or invalid is Signal DefaultValue";
            return false;
        }
        signal.DefaultValue = json["DefaultValue"].GetDouble();

        if (!json.HasMember("MaxValue") || !json["MaxValue"].IsDouble()) {
            errorString = "Missing or invalid is Signal MaxValue";
            return false;
        }
        signal.MaxValue = json["MaxValue"].GetDouble();

        if (!json.HasMember("MinValue") || !json["MinValue"].IsDouble()) {
            errorString = "Missing or invalid is Signal MinValue";
            return false;
        }
        signal.MinValue = json["MinValue"].GetDouble();

        if (!json.HasMember("ByteOrder") || !json["ByteOrder"].IsBool()) {
            errorString = "Missing or invalid is Byte Order";
            return false;
        }
        signal.ByteOrder = json["ByteOrder"].GetBool();

        if (!json.HasMember("DataType") || !json["DataType"].IsInt()) {
            errorString = "Missing or invalid is Signal DataType";
            return false;
        }
        signal.DataType = json["DataType"].GetInt();

        if (!json.HasMember("SignalType") || !json["SignalType"].IsInt()) {
            errorString = "Missing or invalid is Signal SignalType";
            return false;
        }
        signal.SignalType = json["SignalType"].GetInt();

        if (!json.HasMember("ModeValue") || !json["ModeValue"].IsInt()) {
            errorString = "Missing or invalid is Signal ModeValue";
            return false;
        }
        signal.ModeValue = json["ModeValue"].GetInt();

        if (!json.HasMember("Comment") || !json["Comment"].IsString()) {
            errorString = "Missing or invalid is Signal Comment";
            return false;
        }
        signal.Comment = json["Comment"].GetString();

        return true;
    }

}