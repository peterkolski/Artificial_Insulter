
set( APP_NAME   TalkingEliza )


# --------------------- Source Files ---------------------
set( ${APP_NAME}_SOURCE_FILES
        src/main.cpp
        src/ofBitchSkeletonApp.cpp
        ../../shared/TalkerEliza.cpp
        ../../shared/ConversationEliza.cpp
        ../../shared/ConversationOSC.cpp
        ../../shared/bitcherOSC.cpp
        )

# ------------------------ Shared ------------------------
#list( APPEND ${APP_NAME}_SOURCE_FILES
#        ../../shared/XXX.cpp
#        )

# ------------------------ AddOns ------------
set( OFX_ADDONS_ACTIVE
        ofxSoundProcessor
        ofxEliza
        ofxUI
        ofxXmlSettings
        ofxOsc
        )

# =========================================================================
# ============================== OpenFrameworks ===========================
# =========================================================================
include( ${OF_DIRECTORY_BY_USER}/addons/ofxCMake/modules/main.cmake )
# =========================================================================
