#
# Test Package
#

# Package
SRCS += \
	Source/Packages/Test/AppMain.cpp \
	Source/Packages/Test/TestClient.cpp

# Frameworks
SRCS += \
	$(SRC_FRAMEWORK_ALPLUS) \
	$(SRC_FRAMEWORK_APP) \
	$(SRC_FRAMEWORK_COMMON) \
	$(SRC_FRAMEWORK_GAME) \
	$(SRC_FRAMEWORK_GLPLUS) \
	$(SRC_FRAMEWORK_GUI)

# Externals
SRCS += \
	$(SRC_EXTERNAL_INIPARSER) \
	$(SRC_EXTERNAL_TINYXML)

#OPT += -fpermissive
