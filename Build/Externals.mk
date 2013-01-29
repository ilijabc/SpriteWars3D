#
# Externals
#

SRC_EXTERNAL_BOX2D := \
    Source/External/Box2D/Collision/b2BroadPhase.cpp \
    Source/External/Box2D/Collision/b2CollideCircle.cpp \
    Source/External/Box2D/Collision/b2CollideEdge.cpp \
    Source/External/Box2D/Collision/b2CollidePolygon.cpp \
    Source/External/Box2D/Collision/b2Collision.cpp \
    Source/External/Box2D/Collision/b2Distance.cpp \
    Source/External/Box2D/Collision/b2DynamicTree.cpp \
    Source/External/Box2D/Collision/b2TimeOfImpact.cpp \
    Source/External/Box2D/Collision/Shapes/b2ChainShape.cpp \
    Source/External/Box2D/Collision/Shapes/b2CircleShape.cpp \
    Source/External/Box2D/Collision/Shapes/b2EdgeShape.cpp \
    Source/External/Box2D/Collision/Shapes/b2PolygonShape.cpp \
    Source/External/Box2D/Common/b2BlockAllocator.cpp \
    Source/External/Box2D/Common/b2Draw.cpp \
    Source/External/Box2D/Common/b2Math.cpp \
    Source/External/Box2D/Common/b2Settings.cpp \
    Source/External/Box2D/Common/b2StackAllocator.cpp \
    Source/External/Box2D/Common/b2Timer.cpp \
    Source/External/Box2D/Dynamics/b2Body.cpp \
    Source/External/Box2D/Dynamics/b2ContactManager.cpp \
    Source/External/Box2D/Dynamics/b2Fixture.cpp \
    Source/External/Box2D/Dynamics/b2Island.cpp \
    Source/External/Box2D/Dynamics/b2World.cpp \
    Source/External/Box2D/Dynamics/b2WorldCallbacks.cpp \
    Source/External/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
    Source/External/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
    Source/External/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
    Source/External/Box2D/Dynamics/Contacts/b2Contact.cpp \
    Source/External/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
    Source/External/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
    Source/External/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
    Source/External/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
    Source/External/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
    Source/External/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
    Source/External/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
    Source/External/Box2D/Dynamics/Joints/b2GearJoint.cpp \
    Source/External/Box2D/Dynamics/Joints/b2Joint.cpp \
    Source/External/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
    Source/External/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
    Source/External/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
    Source/External/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
    Source/External/Box2D/Dynamics/Joints/b2RopeJoint.cpp \
    Source/External/Box2D/Dynamics/Joints/b2WeldJoint.cpp \
    Source/External/Box2D/Dynamics/Joints/b2WheelJoint.cpp \
    Source/External/Box2D/Rope/b2Rope.cpp

SRC_EXTERNAL_INIPARSER := \
    Source/External/iniParser/dictionary.c \
    Source/External/iniParser/iniparser.c

SRC_EXTERNAL_LUA := \
	Source/External/Lua/lapi.c \
	Source/External/Lua/lauxlib.c \
	Source/External/Lua/lbaselib.c \
	Source/External/Lua/lbitlib.c \
	Source/External/Lua/lcode.c \
	Source/External/Lua/lcorolib.c \
	Source/External/Lua/lctype.c \
	Source/External/Lua/ldblib.c \
	Source/External/Lua/ldebug.c \
	Source/External/Lua/ldo.c \
	Source/External/Lua/ldump.c \
	Source/External/Lua/lfunc.c \
	Source/External/Lua/lgc.c \
	Source/External/Lua/linit.c \
	Source/External/Lua/liolib.c \
	Source/External/Lua/llex.c \
	Source/External/Lua/lmathlib.c \
	Source/External/Lua/lmem.c \
	Source/External/Lua/loadlib.c \
	Source/External/Lua/lobject.c \
	Source/External/Lua/lopcodes.c \
	Source/External/Lua/loslib.c \
	Source/External/Lua/lparser.c \
	Source/External/Lua/lstate.c \
	Source/External/Lua/lstring.c \
	Source/External/Lua/lstrlib.c \
	Source/External/Lua/ltable.c \
	Source/External/Lua/ltablib.c \
	Source/External/Lua/ltm.c \
	Source/External/Lua/lua.c \
	Source/External/Lua/luac.c \
	Source/External/Lua/lundump.c \
	Source/External/Lua/lvm.c \
	Source/External/Lua/lzio.c

SRC_EXTERNAL_MATHGL := \
	Source/External/MathGL/GLBernsteinPolynomial.cpp \
	Source/External/MathGL/GLFunctions.cpp \
	Source/External/MathGL/GLMatrix.cpp \
	Source/External/MathGL/GLVector.cpp \
	Source/External/MathGL/LinearPolynomial.cpp \
	Source/External/MathGL/Matrix.cpp

SRC_EXTERNAL_NANOSVG := \
    Source/External/NanoSVG/nanosvg.c

SRC_EXTERNAL_POLY2TRI := \
	Source/External/poly2tri/common/shapes.cc \
	Source/External/poly2tri/sweep/advancing_front.cc \
	Source/External/poly2tri/sweep/cdt.cc \
	Source/External/poly2tri/sweep/sweep_context.cc \
	Source/External/poly2tri/sweep/sweep.cc

SRC_EXTERNAL_TINYXML := \
    Source/External/TinyXML/tinyxml2.cpp
