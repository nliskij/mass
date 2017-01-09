/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2014-2017. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <stdint.h>

#include <memory>
#include <string>

#include "HAL/AnalogOutput.h"
#if FULL_WPILIB
#include "LiveWindow/LiveWindowSendable.h"
#endif
#include "SensorBase.h"

namespace frc {

/**
 * MXP analog output class.
 */
class AnalogOutput : public SensorBase
#if FULL_WPILIB
                     ,
                     public LiveWindowSendable
#endif
                     {
 public:
  explicit AnalogOutput(int channel);
  virtual ~AnalogOutput();

  void SetVoltage(double voltage);
  double GetVoltage() const;
  int GetChannel();

#if FULL_WPILIB
  void UpdateTable() override;
  void StartLiveWindowMode() override;
  void StopLiveWindowMode() override;
  std::string GetSmartDashboardType() const override;
  void InitTable(std::shared_ptr<ITable> subTable) override;
  std::shared_ptr<ITable> GetTable() const override;
#endif

 protected:
  int m_channel;
  HAL_AnalogOutputHandle m_port;

#if FULL_WPILIB
  std::shared_ptr<ITable> m_table;
#endif
};

}  // namespace frc
