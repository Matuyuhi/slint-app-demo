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

# Slintをリンク
target_link_libraries(dashboard-app PRIVATE Slint::Slint)

# 実体ターゲット(slnt_cpp-shared or slint_cpp-static)を条件分岐で拾う
set(_slint_libdir "$<IF:$<TARGET_EXISTS:slint_cpp-shared>,\
$<TARGET_FILE_DIR:slint_cpp-shared>,\
$<TARGET_FILE_DIR:slint_cpp-static>>")
set(_slint_libfile "$<IF:$<TARGET_EXISTS:slint_cpp-shared>,\
$<TARGET_FILE:slint_cpp-shared>,\
$<TARGET_FILE:slint_cpp-static>>")

# 1) ビルドツリーで実行できるよう RPATH を埋める
set_target_properties(dashboard-app PROPERTIES
  BUILD_RPATH "${_slint_libdir}"
)

# 2) 併せて .dylib/.a を実行ファイルの横へコピー（任意だが便利）
add_custom_command(TARGET dashboard-app POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "${_slint_libfile}"
          "$<TARGET_FILE_DIR:dashboard-app>"
)

# macOS で横置き解決したいなら（任意）
set_target_properties(dashboard-app PROPERTIES
  BUILD_RPATH "@loader_path"
)
