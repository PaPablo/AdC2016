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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=source/config.c source/delay.c source/lcd.c source/main.c source/isr_ADC.c source/isr_DMA.c source/isr_timer346.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/source/config.o ${OBJECTDIR}/source/delay.o ${OBJECTDIR}/source/lcd.o ${OBJECTDIR}/source/main.o ${OBJECTDIR}/source/isr_ADC.o ${OBJECTDIR}/source/isr_DMA.o ${OBJECTDIR}/source/isr_timer346.o
POSSIBLE_DEPFILES=${OBJECTDIR}/source/config.o.d ${OBJECTDIR}/source/delay.o.d ${OBJECTDIR}/source/lcd.o.d ${OBJECTDIR}/source/main.o.d ${OBJECTDIR}/source/isr_ADC.o.d ${OBJECTDIR}/source/isr_DMA.o.d ${OBJECTDIR}/source/isr_timer346.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/source/config.o ${OBJECTDIR}/source/delay.o ${OBJECTDIR}/source/lcd.o ${OBJECTDIR}/source/main.o ${OBJECTDIR}/source/isr_ADC.o ${OBJECTDIR}/source/isr_DMA.o ${OBJECTDIR}/source/isr_timer346.o

# Source Files
SOURCEFILES=source/config.c source/delay.c source/lcd.c source/main.c source/isr_ADC.c source/isr_DMA.c source/isr_timer346.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ256GP710
MP_LINKER_FILE_OPTION=,--script=p33FJ256GP710.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/source/config.o: source/config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/source 
	@${RM} ${OBJECTDIR}/source/config.o.d 
	@${RM} ${OBJECTDIR}/source/config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/config.c  -o ${OBJECTDIR}/source/config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/config.o.d"      -g -D__DEBUG     -omf=coff -O0 -I"../../../../../../microchip_solutions_v2013-06-15/Microchip/Include" -I"../../../../../../../../opt/microchip/xc16/v1.20/include" -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/delay.o: source/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/source 
	@${RM} ${OBJECTDIR}/source/delay.o.d 
	@${RM} ${OBJECTDIR}/source/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/delay.c  -o ${OBJECTDIR}/source/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/delay.o.d"      -g -D__DEBUG     -omf=coff -O0 -I"../../../../../../microchip_solutions_v2013-06-15/Microchip/Include" -I"../../../../../../../../opt/microchip/xc16/v1.20/include" -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/lcd.o: source/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/source 
	@${RM} ${OBJECTDIR}/source/lcd.o.d 
	@${RM} ${OBJECTDIR}/source/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/lcd.c  -o ${OBJECTDIR}/source/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/lcd.o.d"      -g -D__DEBUG     -omf=coff -O0 -I"../../../../../../microchip_solutions_v2013-06-15/Microchip/Include" -I"../../../../../../../../opt/microchip/xc16/v1.20/include" -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/main.o: source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/source 
	@${RM} ${OBJECTDIR}/source/main.o.d 
	@${RM} ${OBJECTDIR}/source/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/main.c  -o ${OBJECTDIR}/source/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/main.o.d"      -g -D__DEBUG     -omf=coff -O0 -I"../../../../../../microchip_solutions_v2013-06-15/Microchip/Include" -I"../../../../../../../../opt/microchip/xc16/v1.20/include" -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/isr_ADC.o: source/isr_ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/source 
	@${RM} ${OBJECTDIR}/source/isr_ADC.o.d 
	@${RM} ${OBJECTDIR}/source/isr_ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/isr_ADC.c  -o ${OBJECTDIR}/source/isr_ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/isr_ADC.o.d"      -g -D__DEBUG     -omf=coff -O0 -I"../../../../../../microchip_solutions_v2013-06-15/Microchip/Include" -I"../../../../../../../../opt/microchip/xc16/v1.20/include" -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/isr_ADC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/isr_DMA.o: source/isr_DMA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/source 
	@${RM} ${OBJECTDIR}/source/isr_DMA.o.d 
	@${RM} ${OBJECTDIR}/source/isr_DMA.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/isr_DMA.c  -o ${OBJECTDIR}/source/isr_DMA.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/isr_DMA.o.d"      -g -D__DEBUG     -omf=coff -O0 -I"../../../../../../microchip_solutions_v2013-06-15/Microchip/Include" -I"../../../../../../../../opt/microchip/xc16/v1.20/include" -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/isr_DMA.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/isr_timer346.o: source/isr_timer346.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/source 
	@${RM} ${OBJECTDIR}/source/isr_timer346.o.d 
	@${RM} ${OBJECTDIR}/source/isr_timer346.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/isr_timer346.c  -o ${OBJECTDIR}/source/isr_timer346.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/isr_timer346.o.d"      -g -D__DEBUG     -omf=coff -O0 -I"../../../../../../microchip_solutions_v2013-06-15/Microchip/Include" -I"../../../../../../../../opt/microchip/xc16/v1.20/include" -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/isr_timer346.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/source/config.o: source/config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/source 
	@${RM} ${OBJECTDIR}/source/config.o.d 
	@${RM} ${OBJECTDIR}/source/config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/config.c  -o ${OBJECTDIR}/source/config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/config.o.d"        -g -omf=coff -O0 -I"../../../../../../microchip_solutions_v2013-06-15/Microchip/Include" -I"../../../../../../../../opt/microchip/xc16/v1.20/include" -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/delay.o: source/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/source 
	@${RM} ${OBJECTDIR}/source/delay.o.d 
	@${RM} ${OBJECTDIR}/source/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/delay.c  -o ${OBJECTDIR}/source/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/delay.o.d"        -g -omf=coff -O0 -I"../../../../../../microchip_solutions_v2013-06-15/Microchip/Include" -I"../../../../../../../../opt/microchip/xc16/v1.20/include" -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/lcd.o: source/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/source 
	@${RM} ${OBJECTDIR}/source/lcd.o.d 
	@${RM} ${OBJECTDIR}/source/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/lcd.c  -o ${OBJECTDIR}/source/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/lcd.o.d"        -g -omf=coff -O0 -I"../../../../../../microchip_solutions_v2013-06-15/Microchip/Include" -I"../../../../../../../../opt/microchip/xc16/v1.20/include" -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/main.o: source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/source 
	@${RM} ${OBJECTDIR}/source/main.o.d 
	@${RM} ${OBJECTDIR}/source/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/main.c  -o ${OBJECTDIR}/source/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/main.o.d"        -g -omf=coff -O0 -I"../../../../../../microchip_solutions_v2013-06-15/Microchip/Include" -I"../../../../../../../../opt/microchip/xc16/v1.20/include" -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/isr_ADC.o: source/isr_ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/source 
	@${RM} ${OBJECTDIR}/source/isr_ADC.o.d 
	@${RM} ${OBJECTDIR}/source/isr_ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/isr_ADC.c  -o ${OBJECTDIR}/source/isr_ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/isr_ADC.o.d"        -g -omf=coff -O0 -I"../../../../../../microchip_solutions_v2013-06-15/Microchip/Include" -I"../../../../../../../../opt/microchip/xc16/v1.20/include" -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/isr_ADC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/isr_DMA.o: source/isr_DMA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/source 
	@${RM} ${OBJECTDIR}/source/isr_DMA.o.d 
	@${RM} ${OBJECTDIR}/source/isr_DMA.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/isr_DMA.c  -o ${OBJECTDIR}/source/isr_DMA.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/isr_DMA.o.d"        -g -omf=coff -O0 -I"../../../../../../microchip_solutions_v2013-06-15/Microchip/Include" -I"../../../../../../../../opt/microchip/xc16/v1.20/include" -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/isr_DMA.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/isr_timer346.o: source/isr_timer346.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/source 
	@${RM} ${OBJECTDIR}/source/isr_timer346.o.d 
	@${RM} ${OBJECTDIR}/source/isr_timer346.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/isr_timer346.c  -o ${OBJECTDIR}/source/isr_timer346.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/isr_timer346.o.d"        -g -omf=coff -O0 -I"../../../../../../microchip_solutions_v2013-06-15/Microchip/Include" -I"../../../../../../../../opt/microchip/xc16/v1.20/include" -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/isr_timer346.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG   -omf=coff -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,$(MP_LINKER_FILE_OPTION),--stack=16,--no-check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/proyectobase3.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase3.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=coff -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--no-check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/proyectobase3.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase3.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=coff 
	
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
