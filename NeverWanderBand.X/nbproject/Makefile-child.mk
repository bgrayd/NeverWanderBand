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
ifeq "$(wildcard nbproject/Makefile-local-child.mk)" "nbproject/Makefile-local-child.mk"
include nbproject/Makefile-local-child.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=child
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBand.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBand.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=C:/ece3724/pic24lib_all/lib/src/pic24_clockfreq.c C:/ece3724/pic24lib_all/lib/src/pic24_configbits.c C:/ece3724/pic24lib_all/lib/src/pic24_serial.c C:/ece3724/pic24lib_all/lib/src/pic24_uart.c C:/ece3724/pic24lib_all/lib/src/pic24_util.c C:/ece3724/pic24lib_all/lib/src/pic24_spi.c C:/ece3724/pic24lib_all/lib/src/pic24_i2c.c ../NeverWanderBand.c ../GPS_module.c ../screen_module.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1719179988/pic24_clockfreq.o ${OBJECTDIR}/_ext/1719179988/pic24_configbits.o ${OBJECTDIR}/_ext/1719179988/pic24_serial.o ${OBJECTDIR}/_ext/1719179988/pic24_uart.o ${OBJECTDIR}/_ext/1719179988/pic24_util.o ${OBJECTDIR}/_ext/1719179988/pic24_spi.o ${OBJECTDIR}/_ext/1719179988/pic24_i2c.o ${OBJECTDIR}/_ext/1472/NeverWanderBand.o ${OBJECTDIR}/_ext/1472/GPS_module.o ${OBJECTDIR}/_ext/1472/screen_module.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1719179988/pic24_clockfreq.o.d ${OBJECTDIR}/_ext/1719179988/pic24_configbits.o.d ${OBJECTDIR}/_ext/1719179988/pic24_serial.o.d ${OBJECTDIR}/_ext/1719179988/pic24_uart.o.d ${OBJECTDIR}/_ext/1719179988/pic24_util.o.d ${OBJECTDIR}/_ext/1719179988/pic24_spi.o.d ${OBJECTDIR}/_ext/1719179988/pic24_i2c.o.d ${OBJECTDIR}/_ext/1472/NeverWanderBand.o.d ${OBJECTDIR}/_ext/1472/GPS_module.o.d ${OBJECTDIR}/_ext/1472/screen_module.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1719179988/pic24_clockfreq.o ${OBJECTDIR}/_ext/1719179988/pic24_configbits.o ${OBJECTDIR}/_ext/1719179988/pic24_serial.o ${OBJECTDIR}/_ext/1719179988/pic24_uart.o ${OBJECTDIR}/_ext/1719179988/pic24_util.o ${OBJECTDIR}/_ext/1719179988/pic24_spi.o ${OBJECTDIR}/_ext/1719179988/pic24_i2c.o ${OBJECTDIR}/_ext/1472/NeverWanderBand.o ${OBJECTDIR}/_ext/1472/GPS_module.o ${OBJECTDIR}/_ext/1472/screen_module.o

# Source Files
SOURCEFILES=C:/ece3724/pic24lib_all/lib/src/pic24_clockfreq.c C:/ece3724/pic24lib_all/lib/src/pic24_configbits.c C:/ece3724/pic24lib_all/lib/src/pic24_serial.c C:/ece3724/pic24lib_all/lib/src/pic24_uart.c C:/ece3724/pic24lib_all/lib/src/pic24_util.c C:/ece3724/pic24lib_all/lib/src/pic24_spi.c C:/ece3724/pic24lib_all/lib/src/pic24_i2c.c ../NeverWanderBand.c ../GPS_module.c ../screen_module.c


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
	${MAKE}  -f nbproject/Makefile-child.mk dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBand.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP128GP502
MP_LINKER_FILE_OPTION=,--script="C:\ece3724\pic24lib_all\lib\lkr\p33EP128MC502_bootldr.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1719179988/pic24_clockfreq.o: C:/ece3724/pic24lib_all/lib/src/pic24_clockfreq.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1719179988 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_clockfreq.o.d 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_clockfreq.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/ece3724/pic24lib_all/lib/src/pic24_clockfreq.c  -o ${OBJECTDIR}/_ext/1719179988/pic24_clockfreq.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1719179988/pic24_clockfreq.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1719179988/pic24_clockfreq.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1719179988/pic24_configbits.o: C:/ece3724/pic24lib_all/lib/src/pic24_configbits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1719179988 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_configbits.o.d 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_configbits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/ece3724/pic24lib_all/lib/src/pic24_configbits.c  -o ${OBJECTDIR}/_ext/1719179988/pic24_configbits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1719179988/pic24_configbits.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1719179988/pic24_configbits.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1719179988/pic24_serial.o: C:/ece3724/pic24lib_all/lib/src/pic24_serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1719179988 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/ece3724/pic24lib_all/lib/src/pic24_serial.c  -o ${OBJECTDIR}/_ext/1719179988/pic24_serial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1719179988/pic24_serial.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1719179988/pic24_serial.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1719179988/pic24_uart.o: C:/ece3724/pic24lib_all/lib/src/pic24_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1719179988 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/ece3724/pic24lib_all/lib/src/pic24_uart.c  -o ${OBJECTDIR}/_ext/1719179988/pic24_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1719179988/pic24_uart.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1719179988/pic24_uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1719179988/pic24_util.o: C:/ece3724/pic24lib_all/lib/src/pic24_util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1719179988 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_util.o.d 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_util.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/ece3724/pic24lib_all/lib/src/pic24_util.c  -o ${OBJECTDIR}/_ext/1719179988/pic24_util.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1719179988/pic24_util.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1719179988/pic24_util.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1719179988/pic24_spi.o: C:/ece3724/pic24lib_all/lib/src/pic24_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1719179988 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/ece3724/pic24lib_all/lib/src/pic24_spi.c  -o ${OBJECTDIR}/_ext/1719179988/pic24_spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1719179988/pic24_spi.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1719179988/pic24_spi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1719179988/pic24_i2c.o: C:/ece3724/pic24lib_all/lib/src/pic24_i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1719179988 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/ece3724/pic24lib_all/lib/src/pic24_i2c.c  -o ${OBJECTDIR}/_ext/1719179988/pic24_i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1719179988/pic24_i2c.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1719179988/pic24_i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/NeverWanderBand.o: ../NeverWanderBand.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/NeverWanderBand.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/NeverWanderBand.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../NeverWanderBand.c  -o ${OBJECTDIR}/_ext/1472/NeverWanderBand.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/NeverWanderBand.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/NeverWanderBand.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/GPS_module.o: ../GPS_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/GPS_module.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/GPS_module.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../GPS_module.c  -o ${OBJECTDIR}/_ext/1472/GPS_module.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/GPS_module.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/GPS_module.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/screen_module.o: ../screen_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/screen_module.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/screen_module.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../screen_module.c  -o ${OBJECTDIR}/_ext/1472/screen_module.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/screen_module.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/screen_module.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1719179988/pic24_clockfreq.o: C:/ece3724/pic24lib_all/lib/src/pic24_clockfreq.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1719179988 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_clockfreq.o.d 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_clockfreq.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/ece3724/pic24lib_all/lib/src/pic24_clockfreq.c  -o ${OBJECTDIR}/_ext/1719179988/pic24_clockfreq.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1719179988/pic24_clockfreq.o.d"      -mno-eds-warn  -g -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1719179988/pic24_clockfreq.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1719179988/pic24_configbits.o: C:/ece3724/pic24lib_all/lib/src/pic24_configbits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1719179988 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_configbits.o.d 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_configbits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/ece3724/pic24lib_all/lib/src/pic24_configbits.c  -o ${OBJECTDIR}/_ext/1719179988/pic24_configbits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1719179988/pic24_configbits.o.d"      -mno-eds-warn  -g -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1719179988/pic24_configbits.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1719179988/pic24_serial.o: C:/ece3724/pic24lib_all/lib/src/pic24_serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1719179988 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/ece3724/pic24lib_all/lib/src/pic24_serial.c  -o ${OBJECTDIR}/_ext/1719179988/pic24_serial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1719179988/pic24_serial.o.d"      -mno-eds-warn  -g -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1719179988/pic24_serial.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1719179988/pic24_uart.o: C:/ece3724/pic24lib_all/lib/src/pic24_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1719179988 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/ece3724/pic24lib_all/lib/src/pic24_uart.c  -o ${OBJECTDIR}/_ext/1719179988/pic24_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1719179988/pic24_uart.o.d"      -mno-eds-warn  -g -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1719179988/pic24_uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1719179988/pic24_util.o: C:/ece3724/pic24lib_all/lib/src/pic24_util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1719179988 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_util.o.d 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_util.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/ece3724/pic24lib_all/lib/src/pic24_util.c  -o ${OBJECTDIR}/_ext/1719179988/pic24_util.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1719179988/pic24_util.o.d"      -mno-eds-warn  -g -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1719179988/pic24_util.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1719179988/pic24_spi.o: C:/ece3724/pic24lib_all/lib/src/pic24_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1719179988 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/ece3724/pic24lib_all/lib/src/pic24_spi.c  -o ${OBJECTDIR}/_ext/1719179988/pic24_spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1719179988/pic24_spi.o.d"      -mno-eds-warn  -g -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1719179988/pic24_spi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1719179988/pic24_i2c.o: C:/ece3724/pic24lib_all/lib/src/pic24_i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1719179988 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1719179988/pic24_i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/ece3724/pic24lib_all/lib/src/pic24_i2c.c  -o ${OBJECTDIR}/_ext/1719179988/pic24_i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1719179988/pic24_i2c.o.d"      -mno-eds-warn  -g -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1719179988/pic24_i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/NeverWanderBand.o: ../NeverWanderBand.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/NeverWanderBand.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/NeverWanderBand.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../NeverWanderBand.c  -o ${OBJECTDIR}/_ext/1472/NeverWanderBand.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/NeverWanderBand.o.d"      -mno-eds-warn  -g -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/NeverWanderBand.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/GPS_module.o: ../GPS_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/GPS_module.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/GPS_module.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../GPS_module.c  -o ${OBJECTDIR}/_ext/1472/GPS_module.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/GPS_module.o.d"      -mno-eds-warn  -g -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/GPS_module.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/screen_module.o: ../screen_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/screen_module.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/screen_module.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../screen_module.c  -o ${OBJECTDIR}/_ext/1472/screen_module.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/screen_module.o.d"      -mno-eds-warn  -g -omf=elf -I"C:/ece3724/pic24lib_all/lib/include" -I"C:/ece3724/pic24lib_all/lib/lkr" -I"C:/ece3724/pic24lib_all/lib/src" -O0 -I"../../lib/include" -DCHILDBAND -DDEFAULT_UART=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/screen_module.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBand.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    C:/ece3724/pic24lib_all/lib/lkr/p33EP128MC502_bootldr.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBand.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG   -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBand.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   C:/ece3724/pic24lib_all/lib/lkr/p33EP128MC502_bootldr.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBand.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/NeverWanderBand.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/child
	${RM} -r dist/child

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
