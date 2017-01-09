/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008-2017. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <stdint.h>

#include <memory>
#include <string>

#include "DigitalSource.h"
#if FULL_WPILIB
#include "LiveWindow/LiveWindowSendable.h"
#endif

namespace frc {

class DigitalGlitchFilter;

/**
 * Class to read a digital input.
 * This class will read digital inputs and return the current value on the
 * channel. Other devices such as encoders, gear tooth sensors, etc. that are
 * implemented elsewhere will automatically allocate digital inputs and outputs
 * as required. This class is only for devices like switches etc. that aren't
 * implemented anywhere else.
 */
class DigitalInput : public DigitalSource
#if FULL_WPILIB
                     ,
                     public LiveWindowSendable
#endif
                     {
 public:
  explicit DigitalInput(int channel);
  virtual ~DigitalInput();
  bool Get() const;
  int GetChannel() const override;

  // Digital Source Interface
  HAL_Handle GetPortHandleForRouting() const override;
  AnalogTriggerType GetAnalogTriggerTypeForRouting() const override;
  bool IsAnalogTrigger() const override;

#if FULL_WPILIB
  void UpdateTable();
  void StartLiveWindowMode();
  void StopLiveWindowMode();
  std::string GetSmartDashboardType() const;
  void InitTable(std::shared_ptr<ITable> subTable);
  std::shared_ptr<ITable> GetTable() const;
#endif

 private:
  int m_channel;
  HAL_DigitalHandle m_handle;

#if FULL_WPILIB
  std::shared_ptr<ITable> m_table;
#endif
  friend class DigitalGlitchFilter;
};

}  // namespace frc
