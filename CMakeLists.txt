cmake_minimum_required(VERSION 3.21)
project(dashboard-app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# macOS用のrpath設定
if(APPLE)
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    set(CMAKE_INSTALL_RPATH "@executable_path;@executable_path/../lib")
endif()

# Slintをダウンロードして利用
include(FetchContent)
FetchContent_Declare(
    Slint
    GIT_REPOSITORY https://github.com/slint-ui/slint.git
    GIT_TAG v1.14.1
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(Slint)

# 実行ファイルを作成
add_executable(dashboard-app src/main.cpp)

# Slint UIファイルをコンパイル
slint_target_sources(dashboard-app ui/appwindow.slint)

# Slintライブラリをリンク
target_link_libraries(dashboard-app PRIVATE Slint::Slint)

# C++20の機能を有効化
target_compile_features(dashboard-app PRIVATE cxx_std_20)
