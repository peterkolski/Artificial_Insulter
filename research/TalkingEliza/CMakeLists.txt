
set( APP_NAME   TalikngEliza )


# --------------------- Source Files ---------------------
set( ${APP_NAME}_SOURCE_FILES
        src/main.cpp
        src/testApp.cpp
        )

# ------------------------ Shared ------------------------
#list( APPEND ${APP_NAME}_SOURCE_FILES
#        ../../shared/XXX.cpp
#        )

# ------------------------ AddOns ------------
set( OFX_ADDONS_ACTIVE
        ofxEliza
        )

# =========================================================================
# ============================== OpenFrameworks ===========================
# =========================================================================
include( ${OF_DIRECTORY_BY_USER}/addons/ofxCMake/modules/main.cmake )
# =========================================================================
