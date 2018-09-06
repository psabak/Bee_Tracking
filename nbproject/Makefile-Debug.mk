#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=c++
CXX=c++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Blob.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/main2.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/C/Apps/opencv/release/lib -lopencv_calib3d342.dll -lopencv_calib3d_pch_dephelp -lopencv_core342.dll -lopencv_core_pch_dephelp -lopencv_dnn342.dll -lopencv_dnn_pch_dephelp -lopencv_features2d342.dll -lopencv_features2d_pch_dephelp -lopencv_flann342.dll -lopencv_flann_pch_dephelp -lopencv_highgui342.dll -lopencv_highgui_pch_dephelp -lopencv_imgcodecs342.dll -lopencv_imgcodecs_pch_dephelp -lopencv_imgproc342.dll -lopencv_imgproc_pch_dephelp -lopencv_ml342.dll -lopencv_ml_pch_dephelp -lopencv_objdetect342.dll -lopencv_objdetect_pch_dephelp -lopencv_photo342.dll -lopencv_photo_pch_dephelp -lopencv_shape342.dll -lopencv_shape_pch_dephelp -lopencv_stitching342.dll -lopencv_stitching_pch_dephelp -lopencv_superres342.dll -lopencv_superres_pch_dephelp -lopencv_video342.dll -lopencv_video_pch_dephelp -lopencv_videoio_pch_dephelp -lopencv_videostab342.dll -lopencv_videostab_pch_dephelp

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bees.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bees.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bees ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Blob.o: Blob.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/Apps/opencv/build/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Blob.o Blob.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/Apps/opencv/build/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/main2.o: main2.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/Apps/opencv/build/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main2.o main2.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
