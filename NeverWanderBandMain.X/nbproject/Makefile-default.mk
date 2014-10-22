#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBandMain.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBandMain.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../../../../../ece3724/pic24_code_examples/lib/common/pic24_clockfreq.c ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_configbits.c ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_util.c ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_uart.c ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_serial.c ../NeverWanderBand.c ../screen_module.c ../glcdfont.c ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_spi.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o ${OBJECTDIR}/_ext/1270305794/pic24_configbits.o ${OBJECTDIR}/_ext/1270305794/pic24_util.o ${OBJECTDIR}/_ext/1270305794/pic24_uart.o ${OBJECTDIR}/_ext/1270305794/pic24_serial.o ${OBJECTDIR}/_ext/1472/NeverWanderBand.o ${OBJECTDIR}/_ext/1472/screen_module.o ${OBJECTDIR}/_ext/1472/glcdfont.o ${OBJECTDIR}/_ext/1270305794/pic24_spi.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o.d ${OBJECTDIR}/_ext/1270305794/pic24_configbits.o.d ${OBJECTDIR}/_ext/1270305794/pic24_util.o.d ${OBJECTDIR}/_ext/1270305794/pic24_uart.o.d ${OBJECTDIR}/_ext/1270305794/pic24_serial.o.d ${OBJECTDIR}/_ext/1472/NeverWanderBand.o.d ${OBJECTDIR}/_ext/1472/screen_module.o.d ${OBJECTDIR}/_ext/1472/glcdfont.o.d ${OBJECTDIR}/_ext/1270305794/pic24_spi.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o ${OBJECTDIR}/_ext/1270305794/pic24_configbits.o ${OBJECTDIR}/_ext/1270305794/pic24_util.o ${OBJECTDIR}/_ext/1270305794/pic24_uart.o ${OBJECTDIR}/_ext/1270305794/pic24_serial.o ${OBJECTDIR}/_ext/1472/NeverWanderBand.o ${OBJECTDIR}/_ext/1472/screen_module.o ${OBJECTDIR}/_ext/1472/glcdfont.o ${OBJECTDIR}/_ext/1270305794/pic24_spi.o

# Source Files
SOURCEFILES=../../../../../../ece3724/pic24_code_examples/lib/common/pic24_clockfreq.c ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_configbits.c ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_util.c ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_uart.c ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_serial.c ../NeverWanderBand.c ../screen_module.c ../glcdfont.c ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_spi.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBandMain.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24HJ32GP202
MP_LINKER_FILE_OPTION=,--script="..\..\..\..\..\..\ece3724\pic24_code_examples\lib\lkr\p24HJ32GP202_bootldr.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o: ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_clockfreq.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270305794 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o.ok ${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o.err 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o.d" -o ${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_clockfreq.c    
	
${OBJECTDIR}/_ext/1270305794/pic24_configbits.o: ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_configbits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270305794 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_configbits.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_configbits.o.ok ${OBJECTDIR}/_ext/1270305794/pic24_configbits.o.err 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_configbits.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270305794/pic24_configbits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1270305794/pic24_configbits.o.d" -o ${OBJECTDIR}/_ext/1270305794/pic24_configbits.o ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_configbits.c    
	
${OBJECTDIR}/_ext/1270305794/pic24_util.o: ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270305794 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_util.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_util.o.ok ${OBJECTDIR}/_ext/1270305794/pic24_util.o.err 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_util.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270305794/pic24_util.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1270305794/pic24_util.o.d" -o ${OBJECTDIR}/_ext/1270305794/pic24_util.o ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_util.c    
	
${OBJECTDIR}/_ext/1270305794/pic24_uart.o: ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270305794 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_uart.o.ok ${OBJECTDIR}/_ext/1270305794/pic24_uart.o.err 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270305794/pic24_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1270305794/pic24_uart.o.d" -o ${OBJECTDIR}/_ext/1270305794/pic24_uart.o ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_uart.c    
	
${OBJECTDIR}/_ext/1270305794/pic24_serial.o: ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270305794 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_serial.o.ok ${OBJECTDIR}/_ext/1270305794/pic24_serial.o.err 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270305794/pic24_serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1270305794/pic24_serial.o.d" -o ${OBJECTDIR}/_ext/1270305794/pic24_serial.o ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_serial.c    
	
${OBJECTDIR}/_ext/1472/NeverWanderBand.o: ../NeverWanderBand.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/NeverWanderBand.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/NeverWanderBand.o.ok ${OBJECTDIR}/_ext/1472/NeverWanderBand.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/NeverWanderBand.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/NeverWanderBand.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1472/NeverWanderBand.o.d" -o ${OBJECTDIR}/_ext/1472/NeverWanderBand.o ../NeverWanderBand.c    
	
${OBJECTDIR}/_ext/1472/screen_module.o: ../screen_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/screen_module.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/screen_module.o.ok ${OBJECTDIR}/_ext/1472/screen_module.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/screen_module.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/screen_module.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1472/screen_module.o.d" -o ${OBJECTDIR}/_ext/1472/screen_module.o ../screen_module.c    
	
${OBJECTDIR}/_ext/1472/glcdfont.o: ../glcdfont.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/glcdfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/glcdfont.o.ok ${OBJECTDIR}/_ext/1472/glcdfont.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/glcdfont.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/glcdfont.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1472/glcdfont.o.d" -o ${OBJECTDIR}/_ext/1472/glcdfont.o ../glcdfont.c    
	
${OBJECTDIR}/_ext/1270305794/pic24_spi.o: ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270305794 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_spi.o.ok ${OBJECTDIR}/_ext/1270305794/pic24_spi.o.err 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270305794/pic24_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1270305794/pic24_spi.o.d" -o ${OBJECTDIR}/_ext/1270305794/pic24_spi.o ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_spi.c    
	
else
${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o: ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_clockfreq.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270305794 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o.ok ${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o.err 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o.d" -o ${OBJECTDIR}/_ext/1270305794/pic24_clockfreq.o ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_clockfreq.c    
	
${OBJECTDIR}/_ext/1270305794/pic24_configbits.o: ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_configbits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270305794 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_configbits.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_configbits.o.ok ${OBJECTDIR}/_ext/1270305794/pic24_configbits.o.err 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_configbits.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270305794/pic24_configbits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1270305794/pic24_configbits.o.d" -o ${OBJECTDIR}/_ext/1270305794/pic24_configbits.o ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_configbits.c    
	
${OBJECTDIR}/_ext/1270305794/pic24_util.o: ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270305794 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_util.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_util.o.ok ${OBJECTDIR}/_ext/1270305794/pic24_util.o.err 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_util.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270305794/pic24_util.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1270305794/pic24_util.o.d" -o ${OBJECTDIR}/_ext/1270305794/pic24_util.o ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_util.c    
	
${OBJECTDIR}/_ext/1270305794/pic24_uart.o: ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270305794 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_uart.o.ok ${OBJECTDIR}/_ext/1270305794/pic24_uart.o.err 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270305794/pic24_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1270305794/pic24_uart.o.d" -o ${OBJECTDIR}/_ext/1270305794/pic24_uart.o ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_uart.c    
	
${OBJECTDIR}/_ext/1270305794/pic24_serial.o: ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270305794 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_serial.o.ok ${OBJECTDIR}/_ext/1270305794/pic24_serial.o.err 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270305794/pic24_serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1270305794/pic24_serial.o.d" -o ${OBJECTDIR}/_ext/1270305794/pic24_serial.o ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_serial.c    
	
${OBJECTDIR}/_ext/1472/NeverWanderBand.o: ../NeverWanderBand.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/NeverWanderBand.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/NeverWanderBand.o.ok ${OBJECTDIR}/_ext/1472/NeverWanderBand.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/NeverWanderBand.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/NeverWanderBand.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1472/NeverWanderBand.o.d" -o ${OBJECTDIR}/_ext/1472/NeverWanderBand.o ../NeverWanderBand.c    
	
${OBJECTDIR}/_ext/1472/screen_module.o: ../screen_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/screen_module.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/screen_module.o.ok ${OBJECTDIR}/_ext/1472/screen_module.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/screen_module.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/screen_module.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1472/screen_module.o.d" -o ${OBJECTDIR}/_ext/1472/screen_module.o ../screen_module.c    
	
${OBJECTDIR}/_ext/1472/glcdfont.o: ../glcdfont.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/glcdfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/glcdfont.o.ok ${OBJECTDIR}/_ext/1472/glcdfont.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/glcdfont.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/glcdfont.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1472/glcdfont.o.d" -o ${OBJECTDIR}/_ext/1472/glcdfont.o ../glcdfont.c    
	
${OBJECTDIR}/_ext/1270305794/pic24_spi.o: ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270305794 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_spi.o.ok ${OBJECTDIR}/_ext/1270305794/pic24_spi.o.err 
	@${RM} ${OBJECTDIR}/_ext/1270305794/pic24_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270305794/pic24_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../../../../../ece3724/pic24_code_examples/lib/include" -I"../../lib/include" -I".." -I"." -mlarge-data -msmall-scalar -O1 -MMD -MF "${OBJECTDIR}/_ext/1270305794/pic24_spi.o.d" -o ${OBJECTDIR}/_ext/1270305794/pic24_spi.o ../../../../../../ece3724/pic24_code_examples/lib/common/pic24_spi.c    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBandMain.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../../../../../ece3724/pic24_code_examples/lib/lkr/p24HJ32GP202_bootldr.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG  -o dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBandMain.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,--heap=100,-L"../../../../../../ece3724/pic24_code_examples/lib/lkr",-L".",-Map="${DISTDIR}/NeverWanderBandMain.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBandMain.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../../../../../ece3724/pic24_code_examples/lib/lkr/p24HJ32GP202_bootldr.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBandMain.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,--heap=100,-L"../../../../../../ece3724/pic24_code_examples/lib/lkr",-L".",-Map="${DISTDIR}/NeverWanderBandMain.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBandMain.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
