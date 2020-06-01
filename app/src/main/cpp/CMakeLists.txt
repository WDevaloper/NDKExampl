#需要区别jni和ndk是没有任何关系的
#但是你要是想使用Java调用c的功能就需要jni
#就好比我想使用FFmpeg，那么我们把FFmpeg编译成.so库，然后我们还需要定义jni，从jni调用FFmpeg函数功能
#就比如native-lib只是为了调用SignTool的功能，而我们就需要定义jni暴露接口给java使用，就相当一个中介者。

#指定cmake 最低支持的版本
cmake_minimum_required(VERSION 3.4.1)

#设置头文件目录
include_directories(${CMAKE_SOURCE_DIR}/inc)


#创建一个静态或者动态库，并提供其关联的源文件路径，开发者可以定义多个库，CMake会自动去构建它们。Gradle可以自动将它们打包进APK中。
#第一个参数——native-lib：是库的名称,生成如.so的名字
#第二个参数——SHARED：是库的类别，是SHARED的还是STATIC的
#第三个参数——src/main/cpp/native-lib.cpp：是库的源文件的路径
#如果想构建多个库，可以添加多个吧ing指定源码
set(srcList native-lib.cpp;Demo.cpp;NewTest.cpp)
add_library(native-lib SHARED ${srcList})
#add_library(Color SHARED Color.cpp)


#找到一个预编译的库，并作为一个变量保存起来。
#注意：由于CMake在搜索库路径的时候会包含系统库，并且CMake会检查它自己之前编译的库的名字，所以开发者需要保证开发者自行添加的库的名字的独特性。
#比如log库是属于系统库的，cmake会自动找log.so，--->ndk\21.1.6352462\platforms\android-29\arch-arm\usr\lib
#第一个参数——log-lib：设置路径变量的名称
#第一个参数—— log：指定NDK库的名子，这样CMake就可以找到这个库
find_library(log-lib log)


#CMake在搜索库路径的时候会包含系统库,那么如果想要导入第三方库，我们应该怎么做呢？
#引入动态库,,必须指定cmake去寻找需要导入的动态目录
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}")


#指定CMake链接到目标库。开发者可以链接多个库，比如开发者可以在此定义库的构建脚本，并且预编译第三方库或者系统库。
#第一个参数——native-lib：指定的目标库
#第一个参数——${log-lib}：将目标库链接到NDK中的日志库
#你可以同时依赖多个库，如：target_link_libraries(native-lib log log2...)
target_link_libraries(
        native-lib
        ${log-lib}
        Test
        fmod
        fmodL
)
