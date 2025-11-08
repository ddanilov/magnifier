# Magnifier

Open-source magnifier app based on Qt framework.

## Building from source

Details may vary depending on your Qt version, host and target architecture etc.
Below an example how to build the app with Qt 6.9.3 for `arm64_v8a` target on `x86_64` Debian/Ubuntu system.

### Prerequisites

- Git Version Control
- CMake Build System
- Qt 6 SDK
- Java JDK
- Android Build Tools
- Android SDK
- Android NDK

Following commands will install Git, CMake, Java and Android dependencies

    sudo apt install git cmake default-jdk
    sudo apt install google-android-build-tools-35.0.1-installer
    sudo apt install google-android-platform-35-installer
    sudo apt install google-android-ndk-r27c-installer

For Qt SDK we are going to use `aqtinstall` from https://github.com/miurahr/aqtinstall in combination with `pipx`

    sudo apt install pipx
    pipx install aqtinstall

Install Qt SDK into a `<Qt-dir>` directory, we need both `gcc_64` and `arm64_v8a`

    ~/.local/bin/aqt install-qt --outputdir <Qt-dir> linux desktop 6.9.3 linux_gcc_64 -m qtmultimedia
    ~/.local/bin/aqt install-qt --outputdir <Qt-dir> linux android 6.9.3 android_arm64_v8a -m qtmultimedia

### Clone source code repository

    git clone https://codeberg.org/danilov/magnifier.git

### Configure CMake build directory

Create build directory `<build_dir>` and configure it with `qt-cmake` wrapper

    <Qt-dir>/6.9.3/android_arm64_v8a/bin/qt-cmake \
        -S <source_dir> -B <build_dir> \
        -DCMAKE_BUILD_TYPE=Release \
        -DQT_HOST_PATH=<Qt-dir>/6.9.3/gcc_64 \
        -DQT_HOST_PATH_CMAKE_DIR=<Qt-dir>/6.9.3/gcc_64/lib/cmake/ \
        -DANDROID_SDK_ROOT=/usr/lib/android-sdk \
        -DANDROID_NDK_ROOT=/usr/lib/android-ndk

### Build APK

    cmake --build <build_dir>

You will find the Android package at `<build_dir>/android-build` or `<build_dir>/android-build/build/outputs/apk`.

## License

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
