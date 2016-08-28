# Mass

Mass is the central repository for all of FRC Team Valkyrie's code. Eventually there will be more documentation files scattered throughout which document the purpose of each folder

## Building the Code

Currently, the code has been tested (and works) on x64_86 Debian Jessie, and x64_84 Ubuntu Trusty. If you get it working anywhere else, please contact us with the operating system and the method you used. It can concievably work in any 64-bit Linux system, but distros which don't follow the same file-tree approach as Debian will require massive symlinks or something.

Sometime in the future, Bazel may do a better job of auto-detecting file paths, in which case this information will change.

Steps to set-up _your_ (Debian Jessie) computer to build the code:
  0. Set up the APT repositories:
    Create a file in /etc/apt/sources.list.d/valkyrie.list and add the following content:
    ```
    deb http://http.debian.net/debian jessie-backports main
    deb http://llvm.org/apt/jessie/ llvm-toolchain-jessie-3.6 main
    deb-src http://llvm.org/apt/jessie/ llvm-toolchain-jessie-3.6 main
    deb http://llvm.org/apt/jessie/ llvm-toolchain-jessie-3.7 main
    deb-src http://llvm.org/apt/jessie/ llvm-toolchain-jessie-3.7 main
    ```
  1. Install the dependencies:
    ```console
    apt-get install python libpython-dev clang-format-3.5 clang-3.6 gfortran libblas-dev liblapack-dev python-scipy python-matplotlib
    ```
  2. Install our Bazel version:
    ```console
    tools/bazel
    ```
  3. Symlink Bazel into your /usr/bin folder:
    ```console
    ln -s /home/vagrant/mass/bazel-downloads/201607271609+da8331d-v1/usr/bin/bazel /usr/bin/bazel
    ```
  4. Build and run all tests:
    ```console
    bazel test //...
    ```
    
