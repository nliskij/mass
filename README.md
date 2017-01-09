# wpiutil

[![Travis CI Build Status](https://travis-ci.org/wpilibsuite/wpiutil.svg?branch=master)](https://travis-ci.org/wpilibsuite/wpiutil)
[![Appveyor Build status](https://ci.appveyor.com/api/projects/status/j6k1apuix04m41ch?svg=true)](https://ci.appveyor.com/project/frcjenkins/wpiutil)


wpiutil is a C++ utility library containing useful C++ classes broadly applicable across the WPI libraries suite.  Classes include select data structure and utility classes from LLVM such as StringRef and SmallVector and a cross-platform TCP sockets library.

## Build Requirements
To build wpiutil, a few requirements must be met:

- Platform Native Toolchain - You must have a toolchain for your native platform installed if you wish to build wpiutil for your machine. On Windows, this is Visual Studio. On Mac, this is Clang, and on Linux, this is GCC. Your toolchain must support the `-std=c++11` language flag.
- ARM Toolchain - To crosscompile wpiutil for the roboRIO, you must have the FRC ARM toolchain installed, which can be found [here](http://first.wpi.edu/FRC/roborio/toolchains/).

## Building
Gradle is the main build system used by wpiutil. All tasks are run with the `gradlew` wrapper, which is included in the root of the repository. All targets that can be accomplished by Gradle are referred to as tasks. The main task available is `build`. To run Gradle, cd into the build directory and run:

```bash
./gradlew build
```

To build just the Native or ARM version, you must access the approriate subproject and build just that version. For example:

```bash
./gradlew :arm:build # Builds just the arm version of wpiutil
./gradlew :native:build # Builds just the native version of wpiutil
```

If you are building the native version on a 64 bit Linux computer, use a GCC installation which has multilib support enabled (it can compile both 32 and 64 bit programs). The package providing that support on most Linux distributions is called `gcc-multilib`.

If you do not have the ARM toolchain installed on your computer, you will run into build issues. To disable the ARM platform entirely, run with the flag `-PskipArm`, and it will be entirely skipped.

```bash
./gradlew build -PskipArm # Builds native, disables the ARM project
```

The native version of wpiutil will run tests on build. The ARM version will not, as the current platform likely does not allow running of an ARM binary.


### Custom Cross Compilers
By default, the ARM version of wpiutil uses the FRC cross compiler, which has the prefix `arm-frc-linux-gnueabi-`. If you want to cross compile with a different ARM toolchain, you can specify the `-PcompilerPrefix=prefix-string` flag. For example, to compile with `arm-linux-gnueabi-gcc`, you would run:

```bash
./gradlew :arm:build -PcompilerPrefix=arm-linux-gnueabi-
```

Keeping the full prefix is important: if you do not specify this correctly, Gradle will likely fail with an error that looks like this:

```Shell
wpiutil master* $ ./gradlew :arm:build -PcompilerPrefix=doesnotexist
Defining custom 'check' task when using the standard Gradle lifecycle plugins has been deprecated and is scheduled to be removed in Gradle 3.0
:arm:processResources UP-TO-DATE
:arm:compileWpiutilSharedLibraryWpiutilCpp FAILED

FAILURE: Build failed with an exception.

* What went wrong:
Execution failed for task ':arm:compileWpiutilSharedLibraryWpiutilCpp'.
> No tool chain is available to build for platform 'arm':
    - Tool chain 'gcc' (GNU GCC): Could not find C compiler 'gcc' in system path.
    - Tool chain 'macGcc' (Clang): Could not find C compiler 'clang' in system path.

* Try:
Run with --stacktrace option to get the stack trace. Run with --info or --debug option to get more log output.

BUILD FAILED

Total time: 2.441 secs
```

## Testing
By default, tests will be built for the x86 and x64 versions of wpiutil, and will be run during any execution of the `build` or `publish` tasks. To skip building and running the tests, use the `-PwithoutTests` command line flag when running Gradle.

## Publishing
To use wpiutil in downstream projects as a Maven-style dependency, use the `publish` command. This will publish four artifacts, where platform_name is your current platform (windows, mac, linux):

- edu.wpi.first.wpilib.networktables.cpp:NetworkTables:3.0.0-SNAPSHOT:arm@zip
- edu.wpi.first.wpilib.networktables.cpp:NetworkTables:3.0.0-SNAPSHOT:platform_name@zip
- edu.wpi.first.wpilib.networktables.java:NetworkTables:3.0.0-SNAPSHOT:arm
- edu.wpi.first.wpilib.networktables.java:NetworkTables:3.0.0-SNAPSHOT:platform_name

These are published to ~/releases/maven/development. To publish to a different repo, specify the `-Prepo=repo_name` flag. Valid repos are:

- development - The default repo.
- beta - Publishes to ~/releases/maven/beta.
- stable - Publishes to ~/releases/maven/stable.
- release - Publishes to ~/releases/maven/release.

Most downstream projects that run on the desktop do not depend on the `platform_name` classifier version of wpiutil. Rather, they depend on a version with the `desktop` classifier. Normally, this is a version of wpiutil built by the FRC Build server that includes binaries for the 3 major operating systems (Windows, Mac, Linux) and 2 major CPU architectures (x86, x86_64). However, if you are locally testing changes to wpiutil, you may want to build a version with the `:desktop` classifier for use on your current platform. To do this, specify the `-PmakeDesktop` flag when publishing. For example:

```bash
./gradlew publish -PmakeDesktop
```

When you do a publish of wpiutil locally, regardless of whether `-PmakeDesktop` is found, the locally built copy will override all references to networktables dependencies from the FRC Maven server. To undo this, you must delete `~/releases/maven/<repo>/edu/wpi/first/wpilib/networktables`.
