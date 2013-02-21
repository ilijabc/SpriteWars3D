#
# Frameworks
#

SRC_FRAMEWORK_ALPLUS := \
    Source/Frameworks/ALPlus/ALContext.cpp

SRC_FRAMEWORK_APP := \
	Source/Frameworks/App/AppClient.cpp \
	Source/Frameworks/App/AppServer.cpp

SRC_FRAMEWORK_COMMON := \
	Source/Frameworks/Common/BaseNode.cpp \
	Source/Frameworks/Common/Color.cpp \
	Source/Frameworks/Common/common.cpp \
	Source/Frameworks/Common/FileObject.cpp \
	Source/Frameworks/Common/matrix4.cpp \
	Source/Frameworks/Common/mymath.cpp \
	Source/Frameworks/Common/mystring.cpp \
	Source/Frameworks/Common/quat.cpp \
	Source/Frameworks/Common/String.cpp

SRC_FRAMEWORK_GAME := \
    Source/Frameworks/Game/GameObject.cpp \
    Source/Frameworks/Game/GameScene.cpp \
    Source/Frameworks/Game/GameTerrain.cpp

SRC_FRAMEWORK_GLPLUS := \
    Source/Frameworks/GLPlus/Utils/BMFont.cpp \
    Source/Frameworks/GLPlus/Utils/DFSprite.cpp \
    Source/Frameworks/GLPlus/Utils/stb_image.c \
    Source/Frameworks/GLPlus/GLCamera.cpp \
    Source/Frameworks/GLPlus/GLFont.cpp \
    Source/Frameworks/GLPlus/GLMaterial.cpp \
    Source/Frameworks/GLPlus/GLMath.cpp \
    Source/Frameworks/GLPlus/GLModel.cpp \
    Source/Frameworks/GLPlus/GLNode.cpp \
    Source/Frameworks/GLPlus/GLParticleSystem.cpp \
    Source/Frameworks/GLPlus/GLPlus.cpp \
    Source/Frameworks/GLPlus/GLSprite.cpp \
	Source/Frameworks/GLPlus/GLTerrain.cpp \
    Source/Frameworks/GLPlus/GLTexture.cpp \
    Source/Frameworks/GLPlus/GLView.cpp

SRC_FRAMEWORK_GUI := \
	Source/Frameworks/GUI/GUIButton.cpp \
	Source/Frameworks/GUI/GUIControl.cpp \
	Source/Frameworks/GUI/GUIEventListener.cpp \
	Source/Frameworks/GUI/GUIForm.cpp \
	Source/Frameworks/GUI/GUIScrollBar.cpp

SRC_FRAMEWORKS := \
	$(SRC_FRAMEWORK_ALPLUS) \
	$(SRC_FRAMEWORK_APP) \
	$(SRC_FRAMEWORK_GAME) \
	$(SRC_FRAMEWORK_GLPLUS) \
	$(SRC_FRAMEWORK_GUI)

