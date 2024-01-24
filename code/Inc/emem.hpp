#pragma once

#include "stdint.h"

#include "m24cxx.hpp"

class Emem
{
protected:
    Emem(){};
    static Emem *_emem;

private:
    struct MemStruct
    {
        uint8_t defaultTimeOff[3] = {0, 0, 0};
        uint8_t defaultTimeShutdown[3] = {0, 0, 0};
        bool defaultSound = true;
        uint8_t defualtCooling = 0; // 0 - always | 1 - ntc regulation
        uint8_t defaultNtc = 0; // 0 - none | 1 - 10K | 2 - 100K

        uint8_t t12MinTemp = 50;
        uint16_t t12MaxTemp = 360;
        uint16_t t12SetTemp = 50;
        int8_t t12Calibration = 0;
        float t12Kp = 800;
        float t12Ki = 1;
        float t12Kd = 1600;
        bool t12Sensor = false;
        uint8_t t12TimeSleep[3] = {0, 5, 0};
        uint16_t t12TempSleep = 100;
        uint8_t t12Ntc = 0; // 0 - none | 1 - 10K | 2 - 100K

        uint8_t hairMinTemp = 50;
        uint16_t hairMaxTemp = 360;
        uint16_t hairSetTemp = 50;
        int8_t hairCalibration = 0;
        float hairKp = 0.8;
        float hairKi =  0.0003;
        float hairKd = 10.25;
        uint8_t hairMinFlow = 10;
        uint16_t hairMaxFlow = 100;
        uint16_t hairSetFlow = 100;
        bool hairSensor = false;
        uint8_t hairNtc = 0; // 0 - none | 1 - 10K | 2 - 100K

        uint8_t ironMinTemp = 50;
        uint16_t ironMaxTemp = 360;
        uint16_t ironSetTemp = 50;
        int8_t ironCalibration = 0;
        float ironKp = 800;
        float ironKi = 1;
        float ironKd = 1600;
        bool ironSensor = false;
        uint8_t ironTimeSleep[3] = {0, 5, 0};
        uint16_t ironTempSleep = 100;
        uint8_t ironNtc = 0; // 0 - none | 1 - 10K | 2 - 100K
    } _memory;

    uint8_t _memorySize = sizeof(MemStruct);
    uint8_t _firstAddr = 4;
    uint8_t _structAddr = 32;
    bool _isFirst = true;

    qymos::driver::M24cxx *_m24cxx;

public:
    Emem(Emem &other) = delete;
    void operator=(const Emem &) = delete;
    static Emem *GetInstance()
    {
        if (_emem == nullptr)
            _emem = new Emem();
        return _emem;
    }
    void Initialize(qymos::driver::M24cxx *m24cxx)
    {
        _m24cxx = m24cxx;
        uint8_t first = 0;
        _m24cxx->ReadData(_firstAddr, &first, sizeof(first), 500);
        if (first != 0x21)
        {
            first = 0x21;
            _m24cxx->WriteData(_firstAddr, &first, sizeof(first), 500);
            _m24cxx->WriteData(_structAddr, (uint8_t *)&_memory, _memorySize, 500);
            return;
        }
        _m24cxx->ReadData(_structAddr, (uint8_t *)&_memory, _memorySize, 500);
    }
    MemStruct &Param() { return _memory; };
    bool Save() { return _m24cxx->WriteData(_structAddr, (uint8_t *)&_memory, _memorySize, 500); };
    void WriteDefault()
    {
        MemStruct def;
        _m24cxx->WriteData(_structAddr, (uint8_t *)&def, _memorySize, 500);
        _memory = def;
    };
};