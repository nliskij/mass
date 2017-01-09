licenses(['notice'])

_header_dirs = [
    'wpilibc/shared/include',
    'wpilibc/athena/include',
    'hal/include',
    'hal/lib/athena',
]

_excluded_devices = [
    'ADXL345_I2C',
    'GearTooth',
    'Ultrasonic',
    'Victor',
    'TalonSRX',
    'CANTalon',
    'CANJaguar',
    'PIDController',
    'Spark',
    'Servo',
    'VictorSP',
    'SD540',
    'RobotDrive',
    'Jaguar',
    'ADXL345_SPI',
    'DoubleSolenoid',
    'AnalogPotentiometer',
    'ADXL362',
    'AnalogGyro',
    'AnalogAccelerometer',
    'CameraServer',
]

_excluded_shared_directories = [
    'SmartDashboard',
    'LiveWindow',
    'Commands',
    'Buttons',
    'Filters',
]

_bad_hdrs = ([
  'wpilibc/athena/include/WPILib.h',
  'hal/include/HAL/cpp/Semaphore.h',
] + ['wpilibc/shared/include/%s/**/*' % d
     for d in _excluded_shared_directories] +
 ['wpilibc/*/include/%s.h' % d for d in _excluded_devices])
_h_hdrs = glob([d + '/**/*.h' for d in _header_dirs], _bad_hdrs)
_hpp_hdrs = glob([d + '/**/*.hpp' for d in _header_dirs], _bad_hdrs)

cc_library(
 name = 'wpilib',
 visibility = ['//third_party:__pkg__'],
 srcs = glob([
   'wpilibc/athena/src/*.cpp',
   'wpilibc/athena/src/Internal/*.cpp',
   'wpilibc/shared/src/**/*.cpp',

   'hal/lib/athena/*.cpp',
   'hal/lib/athena/cpp/*.cpp',
   'hal/lib/athena/ctre/*.cpp',
   'hal/lib/shared/*.cpp',
 ], (['wpilibc/shared/src/%s/**/*' % d for d in _excluded_shared_directories] +
     ['wpilibc/*/src/%s.cpp' % d for d in _excluded_devices] +
     ['hal/lib/athena/cpp/Semaphore.cpp'])),
 copts = [
   '-Wno-unused-parameter',
   '-Wno-switch-enum',
   '-Wno-attributes',
   '-Wno-cast-align',
   '-Wno-cast-qual',
   '-Wno-deprecated-declarations',
   '-Wno-error',
 ],
 deps = [
   '//external:ni-libraries',
   '//third_party/ntcore_2017:ntcore',
 ],

 hdrs = _h_hdrs + _hpp_hdrs,
 includes = _header_dirs,
 linkopts = [
   '-lpthread',
 ],
)
