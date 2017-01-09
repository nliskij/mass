/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2014-2017. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <memory>
#include <string>

#if FULL_WPILIB
#include "LiveWindow/LiveWindowSendable.h"
#endif
#include "SensorBase.h"

namespace frc {

/**
 * Class for getting voltage, current, temperature, power and energy from the
 * CAN PDP.
 */
class PowerDistributionPanel : public SensorBase
#if FULL_WPILIB
                               ,
                               public LiveWindowSendable
#endif
                               {
 public:
  PowerDistributionPanel();
  explicit PowerDistributionPanel(int module);

  double GetVoltage() const;
  double GetTemperature() const;
  double GetCurrent(int channel) const;
  double GetTotalCurrent() const;
  double GetTotalPower() const;
  double GetTotalEnergy() const;
  void ResetTotalEnergy();
  void ClearStickyFaults();

#if FULL_WPILIB
  void UpdateTable() override;
  void StartLiveWindowMode() override;
  void StopLiveWindowMode() override;
  std::string GetSmartDashboardType() const override;
  void InitTable(std::shared_ptr<ITable> subTable) override;
  std::shared_ptr<ITable> GetTable() const override;
#endif

 private:
#if FULL_WPILIB
  std::shared_ptr<ITable> m_table;
#endif
  int m_module;
};

}  // namespace frc
