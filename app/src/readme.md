#!/bin/bash
#ndk 主目录
NDKROOT=/home/ubuntu/android-ndk-r17c

#TOOLCHAIN 变量指向ndk中的交叉编译gcc所在目录
TOOLCHAIN=$NDKROOT/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/

#FLAGS和INCLUDES变量 可以在 AS NDK工程中的.cxx\cmake\debug\armeabi-v7a\build.ninja拷贝,需要注意的修改地址
#替换ndk主目录
#删除-IE:/AndroidStudioprojects/NDKExampl/app/src/main/cpp/inc和-LE:/AndroidStudioprojects/NDKExampl/app/src/main/cpp/../jniLibs/armeabi-v7a

FLAGS = "-isystem $NDKROOT/sysroot/usr/include/arm-linux-androideabi -D__ANDROID_API__=21 -g -DANDROID -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -mthumb -Wa,--noexecstack -Wformat -Werror=format-security -std=c++11 -O0 -fno-limit-debug-info  -fPIC"
INCLUDES = ""-isystem $NDKROOT/sources/cxx-stl/llvm-libc++/include -isystem $NDKROOT/sources/android/support/include -isystem $NDKROOT/sources/cxx-stl/llvm-libc++abi/include"

#执行./confiure 脚本，用于生成makefile
#--prefix  ： 安装目录
#--enable--small 优化大小
#--disable-programs  不编译ffmpeg程序（命令行工具），我们是需要获得静态（动态）库
#--disable-avdevice  关闭avdevice模块，此模块在android中无用
#--disable-encoders  关闭所有编码器（播放器不需要编码）
#--disable-muxers    关闭所有复用器（封装器），不需要生成mp4这样的文件，所以关闭
#--disable-filters   关闭视频滤镜（抖音那种开启）
#--enable-cross-compile  开启交叉编译（ffmpeg比较 跨平台 并不是所有库都有这么happy的选项）
#--cross-prefix
#--disable-shared --enable-static
#--sysroot
#--extra-cflags 会传值给gcc的参数
#--arch
#--target-os


PREFIX=./android/armeabi-v7a2
./confiure \
--prefix=$PREFIX \
--enable--small \
--disable-programs \
--disable-avdevice \
--disable-encoders \
--disable-muxers \
--disable-filters \
--enable-cross-compile \
--cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi- \
--disable-shared \
--enable-static \
--sysroot=$NDKROOT/platforms/android-21/arch-arm \
--extra-cflags="$FLAGS $INCLUDES" \
--extra-cflags=" -isystem $NDKROOT/sysroot" \
--arch=arm \
--target-os=android

make clean
make install

/home/ubuntu/android-ndk-r17c/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-clang is unable to create an executable file.
C compiler test failed.

/home/ubuntu/android-ndk-r17c/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-clang

python3 /home/ubuntu/android-ndk-r17c/build/tools/make_standalone_toolchain.py --arch arm --api 21 --install-dir /tmp/ffmpeg-android-toolchain


官方地址：https://developer.android.com/ndk/guides/standalone_toolchain
替换：androideabi-4.9/prebuilt/linux-x86_64/bin/目录的


配置环境变量
vim ~/.bashrc

PATH="$PATH:/usr/local/ffmepg/bin"
export JAVA_HOME=/home/ubuntu/jdk1.8.0_92
export JRE_HOME=${JAVA_HOME}/jre
export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib
export PATH=${JAVA_HOME}/bin:$PATH
export NDKROOT=/home/ubuntu/android-ndk-r17c
export PATH=$PATH:$NDKROOT

source ~/.bashrc



#!/bin/bash
#libavformat：用于各种音视频封装格式的生成和解析，包括获取解码所需信息以生成解码上下文结构
#和读取音视频帧等功能；
#libavcodec：用于各种类型声音/图像编解码；
#libavutil：包含一些公共的工具函数；
#libswscale：用于视频场景比例缩放、色彩映射转换；
#libpostproc：用于后期效果处理；
#ffmpeg：该项目提供的一个工具，可用于格式转换、解码或电视卡即时编码等；
#ffsever：一个 HTTP 多媒体即时广播串流服务器；
#ffplay：是一个简单的播放器，使用ffmpeg 库解析和解码，通过SDL显示；

make clean
#ndk 主目录
NDKROOT=/home/ubuntu/android-ndk-r17c

#TOOLCHAIN 变量指向ndk中的交叉编译gcc所在目录
TOOLCHAIN=$NDKROOT/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64

#FLAGS和INCLUDES变量 可以在 AS NDK工程中的.cxx\cmake\debug\armeabi-v7a\build.ninja拷贝,需要注意的修改地址
#替换ndk主目录
#删除-IE:/AndroidStudioprojects/NDKExampl/app/src/main/cpp/inc和-LE:/AndroidStudioprojects/NDKExampl/app/src/main/cpp/../jniLibs/armeabi-v7a

FLAGS=" -isystem $NDKROOT/sysroot/usr/include/arm-linux-androideabi -D__ANDROID_API__=21 -g -DANDROID -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -mthumb -Wa,--noexecstack -Wformat -Werror=format-security -O0 -fno-limit-debug-info  -fPIC"
INCLUDES=" -isystem $NDKROOT/sources/android/support/include"


#执行./confiure 脚本，用于生成makefile
#--prefix  ： 安装目录
#--enable--small 优化大小
#--disable-programs  不编译ffmpeg程序（命令行工具），我们是需要获得静态（动态）库
#--disable-avdevice  关闭avdevice模块，此模块在android中无用
#--disable-encoders  关闭所有编码器（播放器不需要编码）
#--disable-muxers    关闭所有复用器（封装器），不需要生成mp4这样的文件，所以关闭
#--disable-filters   关闭视频滤镜（抖音那种开启）
#--enable-cross-compile  开启交叉编译（ffmpeg比较 跨平台 并不是所有库都有这么happy的选项）
#--cross-prefix
#--disable-shared --enable-static
#--sysroot
#--extra-cflags 会传值给gcc的参数
#--arch
#--target-os



#!/bin/bash
make clean

#ndk 主目录
NDKROOT=/home/ubuntu/android-ndk-r17c

#TOOLCHAIN 变量指向ndk中的交叉编译gcc所在目录
TOOLCHAIN=$NDKROOT/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64

INCLUDES=" -isystem $NDKROOT/sources/android/support/include"

PREFIX=./android/armeabi-v7a2
CPU=arm-linux-androideabi-
./configure \

--prefix=$PREFIX \
--enable-small \
--disable-programs \
--disable-avdevice \
--disable-encoders \
--disable-muxers \
--disable-filters \
--enable-cross-compile \
--cc=$TOOLCHAIN/bin/arm-linux-androideabi-gcc \
--enable-neon \
--cc=$TOOLCHAIN/bin/arm-linux-androideabi-gcc \
--cross-prefix=$TOOLCHAIN/bin/$CPU \
--disable-shared \
--enable-static \
--sysroot=$NDKROOT/platforms/android-21/arch-arm \
--extra-cflags="$FLAGS $INCLUDES" \
--extra-cflags=" -isystem $NDKROOT/sysroot/" \
--arch=arm \
--target-os=android

#gcc-asan, clang-asan, gcc-msan, clang-msan,
#                           gcc-tsan, clang-tsan, gcc-usan, clang-usan,
#                          valgrind-massif, valgrind-memcheck,
#                           msvc, icl, gcov, llvm-cov, hardened


#执行清理
make clean
#执行脚本生成的 makefile
make -j4 &&  install






# 编译配置详解答
# 设置编译针对的系统，网上查到很多资料说编译前需要修改configure文件，设置这项后就不用修改了，系统会自动修改，效果一样。
#--target-os=android \

# 编译后文件的输出目录
#--prefix=$PREFIX \
#开启编译器
#--enable-cross-compile \

# 编译动态库，shared和static的开关是相对的。
#--enable-static \
#--disable-shared \

# 生成文档，以及相关的功能模块
#--disable-doc \

# 禁止编译可执行文件
#--disable-programs
#--disable-ffmpeg \
#--disable-ffplay \
#--disable-ffprobe \
#--disable-avdevice \
#--disable-doc \
#--disable-symver \

# 设置交叉编译器，按照实际路径修改就可以了。
#--cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi- \
# 设置编译器，不然会报错，系统默认会使用arm-linux-androideabi-clang，但是此编译器在NDK不存在，导致编译失败
#--cc=$TOOLCHAIN/bin/arm-linux-androideabi-gcc \
#--nm=$TOOLCHAIN/bin/arm-linux-androideabi-nm \

# 设置编译so库的架构，当前设置为arm，可以根据实际需求修改
#--arch=arm \

# 设置编译针对的平台，可以根据实际需求进行设置，当前设置为最低支持android-21版本，arm架构。
#--sysroot=$SYSROOT \
#--extra-cflags="-I$ASM -isysroot $ISYSROOT -D__ANDROID_API__=21 -U_FILE_OFFSET_BITS -Os -fPIC -DANDROID -Wno-deprecated -mfloat-abi=softfp -marm" \

#--extra-ldflags="$ADDI_LDFLAGS" \


/home/ubuntu/android-ndk-r17c/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin
/arm-linux-androideabi-gcc
 --sysroot=/home/ubuntu/android-ndk-r17c/platforms/android-21/arch-arm
 -isystem /home/ubuntu/android-ndk-r17c/sysroot/usr/include/arm-linux-androideabi
 -D__ANDROID_API__=21 -g -DANDROID -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -mthumb -Wa,--noexecstack -Wformat -Werror=format-security -O0 -fno-limit-debug-info -fPIC -isystem /home/ubuntu/android-ndk-r17c/sources/android/support/include -isystem /home/ubuntu/android-ndk-r17c/sysroot/ -mcpu= -c -o /tmp/ffconf.DYke6X5w/test.o /tmp/ffconf.DYke6X5w/test.c
arm-linux-androideabi-gcc: error: missing argument to '-mcpu='
arm-linux-androideabi-gcc: error: unrecognized command line option '-fno-limit-debug-info'
C compiler test failed.

FLAGS=" -isystem $NDKROOT/sysroot/usr/include/arm-linux-androideabi -D__ANDROID_API__=21 -g -DANDROID -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -mthumb -Wa,--noexecstack -Wformat -Werror=format-security -O0 -fno-limit-debug-info  -fPIC"



FLAGS = -isystem $NDKROOT/sysroot/usr/include/arm-linux-androideabi -D__ANDROID_API__=21 -g -DANDROID -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -mthumb -Wa,--noexecstack -Wformat -Werror=format-security -std=c++11 -O0 -fno-limit-debug-info  -fPIC
INCLUDES = -isystem $NDKROOT/sources/cxx-stl/llvm-libc++/include -isystem $NDKROOT/sources/android/support/include -isystem $NDKROOT/sources/cxx-stl/llvm-libc++abi/include


linux-x86_64/bin/arm-linux-androideabi-ar




正常的

#!/bin/bash
sudo make clean
#ndk 主目录
NDKROOT=/home/ubuntu/android-ndk-r17c
#TOOLCHAIN 变量指向ndk中的交叉编译gcc所在目录
TOOLCHAIN=$NDKROOT/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64
ISYSROOT=$NDKROOT/sysroot
ASM=$ISYSROOT/usr/include/arm-linux-androideabi
ADDI_CFLAGS="-marm"
FLAGS=" -I$ASM -isysroot $ISYSROOT -D__ANDROID_API__=21 -U_FILE_OFFSET_BITS -Os -fPIC -DANDROID -Wno-deprecated -mfloat-abi=softfp -marm"
INCLUDES=" -isystem $NDKROOT/sources/android/support/include"
PREFIX=./android/armeabi-v7a
CPU=arm-linux-androideabi-
echo -e "\033[32m build start \033[0m"
./configure \
--prefix=$PREFIX \
--enable-small \
--disable-programs \
--disable-avdevice \
--disable-encoders \
--disable-muxers \
--disable-filters \
--disable-doc \
--enable-cross-compile \
--cc=$TOOLCHAIN/bin/arm-linux-androideabi-gcc \
--enable-neon \
--cross-prefix=$TOOLCHAIN/bin/$CPU \
--disable-shared \
--enable-static \
--sysroot=$NDKROOT/platforms/android-21/arch-arm \
--extra-cflags="-I$ASM -isysroot $ISYSROOT -D__ANDROID_API__=21 -U_FILE_OFFSET_BITS -Os -fPIC -DANDROID -Wno-deprecated -mfloat-abi=softfp -marm" \
--extra-ldflags="$ADDI_LDFLAGS" \
--arch=arm \
--target-os=android
#执行清理
sudo make clean
#执行脚本生成的 makefile
sudo make -j16
sudo make install
echo -e "\033[32m build successful \033[0m"





#-----------------------NDK r21---------------------
编译工具链目录：
toolchains/llvm/prebuilt/linux-x86_64/bin
交叉编译环境目录：
toolchains/llvm/prebuilt/linux-x86_64/sysroot

本文选择 CPU 架构 armv7a，Android版本 21:
armv7a-linux-androideabi21-clang
armv7a-linux-androideabi21-clang++




#!/bin/bash
#构建日志输出文件
LOG_FILE=./android/config.log
#ndk 主目录，如果已经配置了环境变量，可以直接引用环境变量即可
NDKROOT=/home/ubuntu/android-ndk-r21
#TOOLCHAIN 变量指向ndk中的交叉编译gcc所在目录
TOOLCHAIN=$NDKROOT/toolchains/llvm/prebuilt/linux-x86_64
ISYSROOT=$NDKROOT/sysroot
ASM=$ISYSROOT/usr/include/arm-linux-androideabi
ADDI_CFLAGS=" -marm"
PREFIX=./android2/armeabi-v7a
echo "NDKROOT=$NDKROOT,TOOLCHAIN=$TOOLCHAIN"
FLAGS=" -I$ASM -isysroot $ISYSROOT -D__ANDROID_API__=21 -U_FILE_OFFSET_BITS -Os -fPIC -DANDROID -Wno-deprecated -mfloat-abi=softfp -marm"

echo -e "\033[32m build start \033[0m"

./configure \
--prefix=$PREFIX \
--enable-small \
--disable-programs \
--disable-avdevice \
--disable-encoders \
--disable-muxers \
--disable-filters \
--disable-doc \
--enable-cross-compile \
--cc=$TOOLCHAIN/bin/armv7a-linux-androideabi21-clang \
--cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi- \
--enable-neon \
--enable-static \
--disable-shared \
--sysroot="$TOOLCHAIN/sysroot" \
--extra-cflags="$FLAGS" \
--extra-ldflags="$ADDI_LDFLAGS" \
--arch=arm \
--target-os=android
#执行清理
sudo make clean
#执行脚本生成的 makefile
sudo make -j8
sudo make install
echo -e "\033[32m build successful\033[0m"


注意ndk-r21 已经把sysroot移动到 $TOOLCHAIN/sysroot，而r17c sysroot还在 $NDKROOT/platforms/android-21/arch-arm
注意ndk-r21中 --cc也是要指定的，因为他的cross-prefix命名规则不一样了：
比如：--cc=$TOOLCHAIN/bin/armv7a-linux-androideabi21-clang和cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi-
明显不一样了


ndk r21版本-----------------------默认的 cc ar nm 路径前缀是一样的但是在r21之后NDK的ar/nm 和 cc的前缀是不一样了
工具链：/home/ubuntu/android-ndk-r21/toolchains/llvm/prebuilt/linux-x86_64/bin

1、构建armeabi64-v8a:
aarch64-linux-android-ar
aarch64-linux-android-nm
aarch64-linux-android21-clang

2、构建armeabi-v7a:
arm-linux-androideabi-ar
arm-linux-androideabi-nm
armv7a-linux-androideabi21-clang


这个问题怎么解决，网上有人说修改ffmpeg的configure文件增加corss-prefix-clang命令，是可以解决这个问题，但是我们有更简单的？
这个时候就需要：
指定C的编译工具 --cc=$TOOLCHAIN/bin/armv7a-linux-androideabi21-clang
指定交叉编译工具前缀而这个前缀 会匹配到ar、nm等编译工具--cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi-


来看源码：
ar_default="ar"
cc_default="gcc"
cxx_default="g++"
host_cc_default="gcc"
doxygen_default="doxygen"


//如果是android 那么就是clang
set_default target_os
if test "$target_os" = android; then
    cc_default="clang"
fi

//cross_prefix默认是[] 意思是"",所以一般我们都需要指定cross_prefix
ar_default="${cross_prefix}${ar_default}"
cc_default="${cross_prefix}${cc_default}"
nm_default="${cross_prefix}${nm_default}"


看到了不？ar/nm 和 cc的前缀是不一样的，前者是 arm-linux-androideabi- ， 后者是 armv7a-linux-androideabi16-。
所以我们直接在命令中直接修改覆盖了默认的值：
--cc=$TOOLCHAIN/bin/armv7a-linux-androideabi21-clang 覆盖默认值姐可以了
那么ar和nm我们可以使用默认值
