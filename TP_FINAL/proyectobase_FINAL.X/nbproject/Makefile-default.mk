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
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase_FINAL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase_FINAL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=source/config.c source/delay.c source/isr_UART2.c source/lcd.c source/main.c source/isr_timer46.c source/funciones.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/source/config.o ${OBJECTDIR}/source/delay.o ${OBJECTDIR}/source/isr_UART2.o ${OBJECTDIR}/source/lcd.o ${OBJECTDIR}/source/main.o ${OBJECTDIR}/source/isr_timer46.o ${OBJECTDIR}/source/funciones.o
POSSIBLE_DEPFILES=${OBJECTDIR}/source/config.o.d ${OBJECTDIR}/source/delay.o.d ${OBJECTDIR}/source/isr_UART2.o.d ${OBJECTDIR}/source/lcd.o.d ${OBJECTDIR}/source/main.o.d ${OBJECTDIR}/source/isr_timer46.o.d ${OBJECTDIR}/source/funciones.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/source/config.o ${OBJECTDIR}/source/delay.o ${OBJECTDIR}/source/isr_UART2.o ${OBJECTDIR}/source/lcd.o ${OBJECTDIR}/source/main.o ${OBJECTDIR}/source/isr_timer46.o ${OBJECTDIR}/source/funciones.o

# Source Files
SOURCEFILES=source/config.c source/delay.c source/isr_UART2.c source/lcd.c source/main.c source/isr_timer46.c source/funciones.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase_FINAL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ256GP710
MP_LINKER_FILE_OPTION=,--script=p33FJ256GP710.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/source/config.o: source/config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/config.o.d 
	@${RM} ${OBJECTDIR}/source/config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/config.c  -o ${OBJECTDIR}/source/config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/config.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=coff -no-legacy-libc  -O0 -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/delay.o: source/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/delay.o.d 
	@${RM} ${OBJECTDIR}/source/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/delay.c  -o ${OBJECTDIR}/source/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=coff -no-legacy-libc  -O0 -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/isr_UART2.o: source/isr_UART2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/isr_UART2.o.d 
	@${RM} ${OBJECTDIR}/source/isr_UART2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/isr_UART2.c  -o ${OBJECTDIR}/source/isr_UART2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/isr_UART2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=coff -no-legacy-libc  -O0 -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/isr_UART2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/lcd.o: source/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/lcd.o.d 
	@${RM} ${OBJECTDIR}/source/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/lcd.c  -o ${OBJECTDIR}/source/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/lcd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=coff -no-legacy-libc  -O0 -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/main.o: source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/main.o.d 
	@${RM} ${OBJECTDIR}/source/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/main.c  -o ${OBJECTDIR}/source/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=coff -no-legacy-libc  -O0 -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/isr_timer46.o: source/isr_timer46.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/isr_timer46.o.d 
	@${RM} ${OBJECTDIR}/source/isr_timer46.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/isr_timer46.c  -o ${OBJECTDIR}/source/isr_timer46.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/isr_timer46.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=coff -no-legacy-libc  -O0 -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/isr_timer46.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/funciones.o: source/funciones.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/funciones.o.d 
	@${RM} ${OBJECTDIR}/source/funciones.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/funciones.c  -o ${OBJECTDIR}/source/funciones.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/funciones.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=coff -no-legacy-libc  -O0 -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/funciones.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/source/config.o: source/config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/config.o.d 
	@${RM} ${OBJECTDIR}/source/config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/config.c  -o ${OBJECTDIR}/source/config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/config.o.d"        -g -omf=coff -no-legacy-libc  -O0 -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/delay.o: source/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/delay.o.d 
	@${RM} ${OBJECTDIR}/source/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/delay.c  -o ${OBJECTDIR}/source/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/delay.o.d"        -g -omf=coff -no-legacy-libc  -O0 -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/isr_UART2.o: source/isr_UART2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/isr_UART2.o.d 
	@${RM} ${OBJECTDIR}/source/isr_UART2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/isr_UART2.c  -o ${OBJECTDIR}/source/isr_UART2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/isr_UART2.o.d"        -g -omf=coff -no-legacy-libc  -O0 -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/isr_UART2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/lcd.o: source/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/lcd.o.d 
	@${RM} ${OBJECTDIR}/source/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/lcd.c  -o ${OBJECTDIR}/source/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/lcd.o.d"        -g -omf=coff -no-legacy-libc  -O0 -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/main.o: source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/main.o.d 
	@${RM} ${OBJECTDIR}/source/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/main.c  -o ${OBJECTDIR}/source/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/main.o.d"        -g -omf=coff -no-legacy-libc  -O0 -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/isr_timer46.o: source/isr_timer46.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/isr_timer46.o.d 
	@${RM} ${OBJECTDIR}/source/isr_timer46.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/isr_timer46.c  -o ${OBJECTDIR}/source/isr_timer46.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/isr_timer46.o.d"        -g -omf=coff -no-legacy-libc  -O0 -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/isr_timer46.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/funciones.o: source/funciones.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/funciones.o.d 
	@${RM} ${OBJECTDIR}/source/funciones.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/funciones.c  -o ${OBJECTDIR}/source/funciones.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/funciones.o.d"        -g -omf=coff -no-legacy-libc  -O0 -I"../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/funciones.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase_FINAL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase_FINAL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=coff -no-legacy-libc   -mreserve=data@0x800:0x822   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PICKIT2=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F",--no-force-link,--smart-io,-Map="${DISTDIR}/proyectobase4.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase_FINAL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase_FINAL.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=coff -no-legacy-libc  -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="../../../../../../../../opt/microchip/xc16/v1.20/support/dsPIC33F",--no-force-link,--smart-io,-Map="${DISTDIR}/proyectobase4.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/proyectobase_FINAL.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=coff  
	
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
