# ========================================================
# ===================== CMake Settings ===================
# ========================================================
cmake_minimum_required(VERSION 2.8.4)
cmake_policy(SET CMP0042 NEW)

project(  ElisaKora )

set( OF_DIRECTORY_BY_USER ../../../../ )


include_directories( shared )


add_subdirectory( main/TalkingEliza )


# =========================================================================
# ============================== OpenFrameworks ===========================
# =========================================================================
#include( ${OF_DIRECTORY_BY_USER}/addons/ofxCMake/modules/main.cmake )
# =========================================================================
