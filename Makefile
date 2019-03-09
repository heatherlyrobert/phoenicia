#*============================----beg-of-source---============================*#


#===[[ VARABLES ]]======================================================================================================================================================#

#===(current variables)=================================================================================================================================================#
BASE    = txt2bdf
OTHER   = bdf2txt
PSFT    = txt2psft
CHARM   = charmap
SHORT   = txt2vim
SHARE   = font_share
YSTR    = txt2ystr

DEBUG   = ${BASE}_debug
HDIR    = /home/system/watcher.robotic_feedback
IDIR    = /usr/local/bin

#===(compilier variables)===============================================================================================================================================#
# must have "-x c" on gcc line so stripped files work with alternate extensions
COMP    = gcc -c -std=gnu89 -x c -g -pg -Wall -Wextra
INCS    = -I/usr/local/include 

#===(linker options)========================================================================================================================================================================#
#------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)--------------
LINK    = gcc
LIBDIR  = -L/usr/local/lib
LIBS    = ${LIBDIR}         -lm -lySTR
LIBD    = ${LIBDIR}         -lm -lySTR -lyLOG

#===(file lists)============================================================================================================================================================================#
#------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)--------------
HEADS   = font.h
OBJS    = ${BASE}.os        font_share.os
OBJD    = ${BASE}.o         font_share.o

#===(make variables)====================================================================================================================================================#
COPY    = cp -f
CLEAN   = rm -f
PRINT   = @printf
STRIP   = @grep -v -e " DEBUG_" -e " yLOG_" 



#===[[ EXECUTABLES ]]===================================================================================================================================================#

all                : ${BASE} ${OTHER} ${CHARM} ${PSFT} ${SHORT} ${YSTR}

${BASE}            : ${OBJD}
	${LINK}  -o ${BASE}        ${OBJS}   ${LIBS}

${OTHER}           : ${OTHER}.o font_share.os
	${LINK}  -o ${OTHER}       ${OTHER}.os  font_share.os ${LIBS}

${PSFT}            : ${PSFT}.o font_share.os
	${LINK}  -o ${PSFT}        ${PSFT}.os   font_share.os   ${LIBS}

${CHARM}           : ${CHARM}.o
	${LINK}  -o ${CHARM}       ${CHARM}.os   ${LIBS}

${SHORT}           : ${SHORT}.o font_share.os
	${LINK}  -o ${SHORT}       ${SHORT}.os   font_share.os ${LIBS}

${YSTR}            : ${YSTR}.o font_share.os
	${LINK}  -o ${YSTR}        ${YSTR}.os    font_share.os ${LIBS}



#===[[ OBJECT FILES ]]==================================================================================================================================================#

${SHARE}.o         : ${HEADS}       ${SHARE}.c
	${COMP}    ${SHARE}.c                               ${INC}
	${STRIP}   ${SHARE}.c          > ${SHARE}.cs
	${COMP}    ${SHARE}.cs        -o ${SHARE}.os        ${INC}

${BASE}.o          : ${HEADS}       ${BASE}.c
	${COMP}    ${BASE}.c                                ${INC}
	${STRIP}   ${BASE}.c           > ${BASE}.cs
	${COMP}    ${BASE}.cs         -o ${BASE}.os         ${INC}

${OTHER}.o         : ${HEADS}       ${OTHER}.c
	${COMP}    ${OTHER}.c                               ${INC}
	${STRIP}   ${OTHER}.c          > ${OTHER}.cs
	${COMP}    ${OTHER}.cs        -o ${OTHER}.os        ${INC}

${PSFT}.o          : ${HEADS}       ${PSFT}.c
	${COMP}    ${PSFT}.c                                ${INC}
	${STRIP}   ${PSFT}.c           > ${PSFT}.cs
	${COMP}    ${PSFT}.cs         -o ${PSFT}.os         ${INC}

${CHARM}.o         : ${HEADS}       ${CHARM}.c
	${COMP}    ${CHARM}.c                               ${INC}
	${STRIP}   ${CHARM}.c          > ${CHARM}.cs
	${COMP}    ${CHARM}.cs        -o ${CHARM}.os        ${INC}

${SHORT}.o         : ${HEADS}       ${SHORT}.c
	${COMP}    ${SHORT}.c                               ${INC}
	${STRIP}   ${SHORT}.c          > ${SHORT}.cs
	${COMP}    ${SHORT}.cs        -o ${SHORT}.os        ${INC}

${YSTR}.o          : ${HEADS}       ${YSTR}.c
	${COMP}    ${YSTR}.c                               ${INC}
	${STRIP}   ${YSTR}.c           > ${YSTR}.cs
	${COMP}    ${YSTR}.cs         -o ${YSTR}.os        ${INC}




#===[[ SCRIPTS ]]=======================================================================================================================================================#

clean              :
	#---(all versions)--------------------#
	${CLEAN} ${BASE}
	${CLEAN} ${DEBUG}
	${CLEAN} ${CHARM}
	${CLEAN} ${PSFT}
	#---(object and stripped files)-------#
	${CLEAN} ${BASE}*.o
	${CLEAN} ${BASE}*.cs
	${CLEAN} ${BASE}*.os
	${CLEAN} ${BASE}*.Sc
	${CLEAN} ${BASE}*.So
	${CLEAN} ${OTHER}*.o
	${CLEAN} ${OTHER}*.os
	${CLEAN} ${SHARE}*.o
	${CLEAN} ${SHARE}*.os
	${CLEAN} ${CHARM}*.o
	${CLEAN} ${CHARM}*.os
	${CLEAN} ${PSFT}*.o
	${CLEAN} ${PSFT}*.os
	#---(junk files)----------------------#
	${CLEAN} *~
	${CLEAN} temp*

bigclean           :
	${CLEAN} .*.swp

install            : ${BASE}
	#---(production version)--------------#
	${COPY}   ${BASE}    ${IDIR}/
	chown     root:root  ${IDIR}/${BASE}
	chmod     0700       ${IDIR}/${BASE}
	@sha1sum  ${BASE}
	#---(conversion version)--------------#
	${COPY}   ${OTHER}   ${IDIR}/
	chown     root:root  ${IDIR}/${OTHER}
	chmod     0700       ${IDIR}/${OTHER}
	@sha1sum  ${OTHER}
	#---(conversion version)--------------#
	${COPY}   ${PSFT}    ${IDIR}/
	chown     root:root  ${IDIR}/${PSFT}
	chmod     0700       ${IDIR}/${PSFT}
	@sha1sum  ${PSFT}
	#---(conversion version)--------------#
	${COPY}   myfont.sh  ${IDIR}/myfont
	chown     root:root  ${IDIR}/myfont
	chmod     0700       ${IDIR}/myfont
	@sha1sum  myfont.sh
	#---(conversion version)--------------#
	${COPY}   ${CHARM}   ${IDIR}/
	chown     root:root  ${IDIR}/${CHARM}
	chmod     0700       ${IDIR}/${CHARM}
	@sha1sum  ${CHARM}
	#---(conversion version)--------------#
	${COPY}   ${SHORT}   ${IDIR}/
	chown     root:root  ${IDIR}/${SHORT}
	chmod     0700       ${IDIR}/${SHORT}
	@sha1sum  ${SHORT}
	#---(conversion version)--------------#
	${COPY}   ${YSTR}    ${IDIR}/
	chown     root:root  ${IDIR}/${YSTR}
	chmod     0700       ${IDIR}/${YSTR}
	@sha1sum  ${YSTR}


remove             :
	#---(all versions)--------------------#
	${CLEAN}  ${IDIR}/${BASE}



#*============================----end-of-source---============================*#
