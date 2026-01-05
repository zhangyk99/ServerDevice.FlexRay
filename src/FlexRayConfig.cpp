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
//            errorString = "Missing or invalid device config ECU List";
//            return false;
//        }
//        const rapidjson::Value &ecuList = json["EcuList"];
//        for (rapidjson::SizeType i = 0; i < ecuList.Size(); i++) {
//            ECU ecu;
//            if (!ParseECU(ecuList[i], ecu)) {
//                errorString += "Failed to parse ECU";
//                return false;
//            }
//            if (i == 0)
//                config.Ecu = ecu;
//            config.EcuList.push_back(ecu);
//        }


        if(!json.HasMember("Ecu") || json["Ecu"].IsObject()) {
            errorString = "Missing or invalid device config Ecu";
            return false;
        }
        if (!ParseECU(json["Ecu"], config.Ecu)) {
            errorString += "Failed to parse ECU";
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

        if (!json.HasMember("T_S_S_TRANSMITTER") || !json["T_S_S_TRANSMITTER"].IsUint()) {
            errorString = "Missing or invalid cluster config T_S_S_TRANSMITTER";
            return false;
        }
        cluster.T_S_S_TRANSMITTER = json["T_S_S_TRANSMITTER"].GetUint();

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

    bool FlexRayConfig::ParseECU(const rapidjson::Value &json, ECU &ecu) {
        if (!json.IsObject()) {
            errorString = "ECU is not an object";
            return false;
        }

        if (!json.HasMember("Name") || !json["Name"].IsString()) {
            errorString = "Missing or invalid ECU Name";
            return false;
        }
        ecu.Name = json["Name"].GetString();

        if (!json.HasMember("ID") || !json["ID"].IsInt()) {
            errorString = "Missing or invalid ECU ID";
            return false;
        }
        ecu.ID = json["ID"].GetInt();

        if (!json.HasMember("UseDefault") || !json["UseDefault"].IsBool()) {
            errorString = "Missing or invalid ECU Use Default";
            return false;
        }
        ecu.UseDefault = json["UseDefault"].GetBool();

        if (!json.HasMember("UseMaxMin") || !json["UseMaxMin"].IsBool()) {
            errorString = "Missing or invalid ECU Use Max or Min";
            return false;
        }
        ecu.UseMaxMin = json["UseMaxMin"].GetBool();

        if (!json.HasMember("BridgePattern") || !json["BridgePattern"].IsBool()) {
            errorString = "Missing or invalid ECU Bridge Pattern";
            return false;
        }
        ecu.BridgePattern = json["BridgePattern"].GetBool();

        if (!json.HasMember("Termination") || !json["Termination"].IsBool()) {
            errorString = "Missing or invalid ECU Termination";
            return false;
        }
        ecu.Termination = json["Termination"].GetBool();

        if (!json.HasMember("HardwareTiming") || !json["HardwareTiming"].IsBool()) {
            errorString = "Missing or invalid ECU Hardware Timing";
            return false;
        }
        ecu.HardwareTiming = json["HardwareTiming"].GetBool();


        if (!json.HasMember("Description") || !json["Description"].IsString()) {
            errorString = "Missing or invalid ECU Description";
            return false;
        }
        ecu.Description = json["Description"].GetString();

        if (!json.HasMember("WatchDog") || !json["WatchDog"].IsString()) {
            errorString = "Missing or invalid ECU WatchDog";
            return false;
        }
        ecu.WatchDog = json["WatchDog"].GetString();

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
            ecu.Frames.push_back(message);
        }

        return true;
    }

    bool FlexRayConfig::ParseECUConfig(const rapidjson::Value &json, ECUConfig &ecuConfig) {
        if (!json.IsObject()) {
            errorString = "ECUConfig is not an object";
            return false;
        }

        if (!json.HasMember("StartUpSync") || !json["StartUpSync"].IsUint()) {
            errorString = "Missing or invalid ECU Config StartUpSync";
            return false;
        }
        ecuConfig.StartUpSync = json["StartUpSync"].GetUint();

        if (!json.HasMember("MaxDynamicPayloadLength") || !json["MaxDynamicPayloadLength"].IsUint()) {
            errorString = "Missing or invalid ECU Config MaxDynamicPayloadLength";
            return false;
        }
        ecuConfig.MaxDynamicPayloadLength = json["MaxDynamicPayloadLength"].GetUint();

        if (!json.HasMember("ClusterDriftDamping") || !json["ClusterDriftDamping"].IsUint()) {
            errorString = "Missing or invalid ECU Config ClusterDriftDamping";
            return false;
        }
        ecuConfig.ClusterDriftDamping = json["ClusterDriftDamping"].GetUint();

        if (!json.HasMember("DecodingCorrection") || !json["DecodingCorrection"].IsUint()) {
            errorString = "Missing or invalid ECU Config DecodingCorrection";
            return false;
        }
        ecuConfig.DecodingCorrection = json["DecodingCorrection"].GetUint();

        if (!json.HasMember("ListenTimeout") || !json["ListenTimeout"].IsUint()) {
            errorString = "Missing or invalid ECU Config ListenTimeout";
            return false;
        }
        ecuConfig.ListenTimeout = json["ListenTimeout"].GetUint();

        if (!json.HasMember("MaxDrift") || !json["MaxDrift"].IsUint()) {
            errorString = "Missing or invalid ECU Config MaxDrift";
            return false;
        }
        ecuConfig.MaxDrift = json["MaxDrift"].GetUint();

        if (!json.HasMember("ExternOffsetCorrection") || !json["ExternOffsetCorrection"].IsUint()) {
            errorString = "Missing or invalid ECU Config ExternOffsetCorrection";
            return false;
        }
        ecuConfig.ExternOffsetCorrection = json["ExternOffsetCorrection"].GetUint();

        if (!json.HasMember("ExternRateCorrection") || !json["ExternRateCorrection"].IsUint()) {
            errorString = "Missing or invalid ECU Config ExternRateCorrection";
            return false;
        }
        ecuConfig.ExternRateCorrection = json["ExternRateCorrection"].GetUint();

        if (!json.HasMember("LatestTX") || !json["LatestTX"].IsUint()) {
            errorString = "Missing or invalid ECU Config LatestTX";
            return false;
        }
        ecuConfig.LatestTX = json["LatestTX"].GetUint();

        if (!json.HasMember("MicroPerCycle") || !json["MicroPerCycle"].IsUint()) {
            errorString = "Missing or invalid ECU Config MicroPerCycle";
            return false;
        }
        ecuConfig.MicroPerCycle = json["MicroPerCycle"].GetUint();

        if (!json.HasMember("OffsetCorrectionOut") || !json["OffsetCorrectionOut"].IsUint()) {
            errorString = "Missing or invalid ECU Config OffsetCorrectionOut";
            return false;
        }
        ecuConfig.OffsetCorrectionOut = json["OffsetCorrectionOut"].GetUint();

        if (!json.HasMember("RateCorrectionOut") || !json["RateCorrectionOut"].IsUint()) {
            errorString = "Missing or invalid ECU RateCorrectionOut";
            return false;
        }
        ecuConfig.RateCorrectionOut = json["RateCorrectionOut"].GetUint();

        if (!json.HasMember("SamplesPerMicroTick") || !json["SamplesPerMicroTick"].IsUint()) {
            errorString = "Missing or invalid ECU SamplesPerMicroTick";
            return false;
        }
        ecuConfig.SamplesPerMicroTick = json["SamplesPerMicroTick"].GetUint();

        if (!json.HasMember("DelayCompensationA") || !json["DelayCompensationA"].IsUint()) {
            errorString = "Missing or invalid ECU DelayCompensationA";
            return false;
        }
        ecuConfig.DelayCompensationA = json["DelayCompensationA"].GetUint();

        if (!json.HasMember("DelayCompensationB") || !json["DelayCompensationB"].IsUint()) {
            errorString = "Missing or invalid ECU DelayCompensationB";
            return false;
        }
        ecuConfig.DelayCompensationB = json["DelayCompensationB"].GetUint();

        if (!json.HasMember("WakeUpPattern") || !json["WakeUpPattern"].IsUint()) {
            errorString = "Missing or invalid ECU Config WakeUpPattern";
            return false;
        }
        ecuConfig.WakeUpPattern = json["WakeUpPattern"].GetUint();

        if (!json.HasMember("AllowHaltDueToClock") || !json["AllowHaltDueToClock"].IsUint()) {
            errorString = "Missing or invalid ECU Config AllowHaltDueToClock";
            return false;
        }
        ecuConfig.AllowHaltDueToClock = json["AllowHaltDueToClock"].GetUint();

        if (!json.HasMember("AllowPassiveToAction") || !json["AllowPassiveToAction"].IsUint()) {
            errorString = "Missing or invalid ECU Config AllowPassiveToAction";
            return false;
        }
        ecuConfig.AllowPassiveToAction = json["AllowPassiveToAction"].GetUint();

        if (!json.HasMember("AcceptedStartUpRange") || !json["AcceptedStartUpRange"].IsUint()) {
            errorString = "Missing or invalid ECU Config AcceptedStartUpRange";
            return false;
        }
        ecuConfig.AcceptedStartUpRange = json["AcceptedStartUpRange"].GetUint();

        if (!json.HasMember("MacroInitialOffsetA") || !json["MacroInitialOffsetA"].IsUint()) {
            errorString = "Missing or invalid ECU Config MacroInitialOffsetA";
            return false;
        }
        ecuConfig.MacroInitialOffsetA = json["MacroInitialOffsetA"].GetUint();

        if (!json.HasMember("MacroInitialOffsetB") || !json["MacroInitialOffsetB"].IsUint()) {
            errorString = "Missing or invalid ECU Config MacroInitialOffsetB";
            return false;
        }
        ecuConfig.MacroInitialOffsetB = json["MacroInitialOffsetB"].GetUint();

        if (!json.HasMember("MicroInitialOffsetA") || !json["MicroInitialOffsetA"].IsUint()) {
            errorString = "Missing or invalid ECU Config MicroInitialOffsetA";
            return false;
        }
        ecuConfig.MicroInitialOffsetA = json["MicroInitialOffsetA"].GetUint();

        if (!json.HasMember("MircoInitialOffsetB") || !json["MircoInitialOffsetB"].IsUint()) {
            errorString = "Missing or invalid ECU Config MircoInitialOffsetB";
            return false;
        }
        ecuConfig.MircoInitialOffsetB = json["MircoInitialOffsetB"].GetUint();

        if (!json.HasMember("SingleSlotEnabled") || !json["SingleSlotEnabled"].IsUint()) {
            errorString = "Missing or invalid ECU Config SingleSlotEnabled";
            return false;
        }
        ecuConfig.SingleSlotEnabled = json["SingleSlotEnabled"].GetUint();

        if (!json.HasMember("MicroTick") || !json["MicroTick"].IsDouble()) {
            errorString = "Missing or invalid ECU Config MicroTick";
            return false;
        }
        ecuConfig.MicroTick = json["MicroTick"].GetDouble();

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