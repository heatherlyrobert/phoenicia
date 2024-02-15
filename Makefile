#================================[[ beg-code ]]================================#



#===(manditory)============================================#
# basename of executable, header, and all code files
NAME_BASE  = phoenicia
# additional standard and outside libraries
LIB_STD    = -lm
# all heatherly libraries used, debug versions whenever available
LIB_MINE   = -lySTR_debug
# directory for production code, no trailing slash
INST_DIR   = /usr/local/bin



#===(optional)=============================================#
# extra include directories required
INC_MINE   = 
# utilities generated, separate from main program
NAME_UTIL  = 
# libraries only for the utilities
LIB_UTIL   = 



#===(post-processing)======================================#
# create a rule for...
#install_prep       :
#remove_prep        :



#===(master template)======================================#
include /usr/local/sbin/make_program



#===(post-processing)======================================#
# create a rule for...
install_post       :

#remove_post        :



#================================[[ end-code ]]================================#

## #*============================----beg-of-source---============================*#
## 
## 
## #===[[ VARABLES ]]======================================================================================================================================================#
## 
## #===(current variables)=================================================================================================================================================#
## BASE    = txt2bdf
## OTHER   = bdf2txt
## PSFT    = txt2psft
## CHARM   = charmap
## CHAR2   = charmap2
## SHORT   = txt2vim
## SHARE   = font_share
## YSTR    = txt2ystr
## TXF     = txt2txf
## 
## DEBUG   = ${BASE}_debug
## HDIR    = /home/system/watcher.robotic_feedback
## IDIR    = /usr/local/bin
## 
## #===(compilier variables)===============================================================================================================================================#
## # must have "-x c" on gcc line so stripped files work with alternate extensions
## COMP    = gcc -c -std=gnu89 -x c -g -pg -Wall -Wextra
## INCS    = -I/usr/local/include 
## 
## #===(linker options)========================================================================================================================================================================#
## #------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)--------------
## LINK    = gcc
## LIBDIR  = -L/usr/local/lib
## LIBS    = ${LIBDIR}         -lm -lySTR
## LIBD    = ${LIBDIR}         -lm -lySTR -lyLOG
## 
## #===(file lists)============================================================================================================================================================================#
## #------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)--------------
## HEADS   = font.h
## OBJS    = ${BASE}.os        font_share.os
## OBJD    = ${BASE}.o         font_share.o
## 
## #===(make variables)====================================================================================================================================================#
## COPY    = cp -f
## CLEAN   = rm -f
## PRINT   = @printf
## STRIP   = @grep -v -e " DEBUG_" -e " yLOG_" 
## 
## 
## 
## #===[[ EXECUTABLES ]]===================================================================================================================================================#
## 
## all                : ${BASE} ${TXF} ${OTHER} ${CHARM} ${CHAR2} ${PSFT} ${SHORT} ${YSTR} phoenicia
## 
## ${BASE}            : ${OBJD}
## 	${LINK}  -o ${BASE}        ${OBJS}   ${LIBS}
## 
## ${TXF}             : ${TXF}.o font_share.o
## 	${LINK}  -o ${TXF}       ${TXF}.os  font_share.os  ${LIBS} -lyFONT -lyGLTEX -lGL -lGLU
## 
## ${OTHER}           : ${OTHER}.o font_share.os
## 	${LINK}  -o ${OTHER}       ${OTHER}.os  font_share.os ${LIBS}
## 
## ${PSFT}            : ${PSFT}.o font_share.os
## 	${LINK}  -o ${PSFT}        ${PSFT}.os   font_share.os   ${LIBS}
## 
## ${CHARM}           : ${CHARM}.o
## 	${LINK}  -o ${CHARM}       ${CHARM}.os   ${LIBS}
## 
## ${CHAR2}           : ${CHAR2}.o
## 	${LINK}  -o ${CHAR2}       ${CHAR2}.os   ${LIBS} -lncurses -ltinfo
## 
## ${SHORT}           : ${SHORT}.o font_share.os
## 	${LINK}  -o ${SHORT}       ${SHORT}.os   font_share.os ${LIBS}
## 
## ${YSTR}            : ${YSTR}.o font_share.os
## 	${LINK}  -o ${YSTR}        ${YSTR}.os    font_share.os ${LIBS}
## 
## phoenicia          : phoenicia.o font_share.os
## 	${LINK}  -o phoenicia      phoenicia.os    font_share.os ${LIBS}
## 
## 
## 
## #===[[ OBJECT FILES ]]==================================================================================================================================================#
## 
## ${SHARE}.o         : ${HEADS}       ${SHARE}.c
## 	${COMP}    ${SHARE}.c                               ${INC}
## 	${STRIP}   ${SHARE}.c          > ${SHARE}.cs
## 	${COMP}    ${SHARE}.cs        -o ${SHARE}.os        ${INC}
## 
## ${BASE}.o          : ${HEADS}       ${BASE}.c
## 	${COMP}    ${BASE}.c                                ${INC}
## 	${STRIP}   ${BASE}.c           > ${BASE}.cs
## 	${COMP}    ${BASE}.cs         -o ${BASE}.os         ${INC}
## 
## ${TXF}.o           : ${HEADS}       ${TXF}.c
## 	${COMP}    ${TXF}.c                                 ${INC}
## 	${STRIP}   ${TXF}.c            > ${TXF}.cs
## 	${COMP}    ${TXF}.cs          -o ${TXF}.os          ${INC}
## 
## ${OTHER}.o         : ${HEADS}       ${OTHER}.c
## 	${COMP}    ${OTHER}.c                               ${INC}
## 	${STRIP}   ${OTHER}.c          > ${OTHER}.cs
## 	${COMP}    ${OTHER}.cs        -o ${OTHER}.os        ${INC}
## 
## ${PSFT}.o          : ${HEADS}       ${PSFT}.c
## 	${COMP}    ${PSFT}.c                                ${INC}
## 	${STRIP}   ${PSFT}.c           > ${PSFT}.cs
## 	${COMP}    ${PSFT}.cs         -o ${PSFT}.os         ${INC}
## 
## ${CHARM}.o         : ${HEADS}       ${CHARM}.c
## 	${COMP}    ${CHARM}.c                               ${INC}
## 	${STRIP}   ${CHARM}.c          > ${CHARM}.cs
## 	${COMP}    ${CHARM}.cs        -o ${CHARM}.os        ${INC}
## 
## ${CHAR2}.o         : ${HEADS}       ${CHAR2}.c
## 	${COMP}    ${CHAR2}.c                               ${INC}
## 	${STRIP}   ${CHAR2}.c          > ${CHAR2}.cs
## 	${COMP}    ${CHAR2}.cs        -o ${CHAR2}.os        ${INC}
## 
## ${SHORT}.o         : ${HEADS}       ${SHORT}.c
## 	${COMP}    ${SHORT}.c                               ${INC}
## 	${STRIP}   ${SHORT}.c          > ${SHORT}.cs
## 	${COMP}    ${SHORT}.cs        -o ${SHORT}.os        ${INC}
## 
## ${YSTR}.o          : ${HEADS}       ${YSTR}.c
## 	${COMP}    ${YSTR}.c                               ${INC}
## 	${STRIP}   ${YSTR}.c           > ${YSTR}.cs
## 	${COMP}    ${YSTR}.cs         -o ${YSTR}.os        ${INC}
## 
## phoenicia.o        : ${HEADS}       phoenicia.c
## 	${COMP}    phoenicia.c                               ${INC}
## 	${STRIP}   phoenicia.c           > phoenicia.cs
## 	${COMP}    phoenicia.cs         -o phoenicia.os        ${INC}
## 
## 
## 
## 
## #===[[ SCRIPTS ]]=======================================================================================================================================================#
## 
## vi_edit            :
## 	vi -c "call HBUF_on()" -c "call HTAG_on()" font.h ${BASE}.c ${OTHER}.c ${PSFT}.c ${CHARM}.c ${SHORT}.c ${SHARE}.c ${YSTR}.c ${TXF}.c phoenicia.c
## 
## allclean           :
## 	#---(all versions)--------------------#
## 	${CLEAN} ${BASE}
## 	${CLEAN} ${TXF}
## 	${CLEAN} ${DEBUG}
## 	${CLEAN} ${CHARM}
## 	${CLEAN} ${CHAR2}
## 	${CLEAN} ${PSFT}
## 	#---(object and stripped files)-------#
## 	${CLEAN} ${BASE}*.o
## 	${CLEAN} ${BASE}*.cs
## 	${CLEAN} ${BASE}*.os
## 	${CLEAN} ${BASE}*.Sc
## 	${CLEAN} ${BASE}*.So
## 	${CLEAN} ${OTHER}*.o
## 	${CLEAN} ${OTHER}*.os
## 	${CLEAN} ${SHARE}*.o
## 	${CLEAN} ${SHARE}*.os
## 	${CLEAN} ${CHARM}*.o
## 	${CLEAN} ${CHARM}*.os
## 	${CLEAN} ${CHAR2}*.o
## 	${CLEAN} ${CHAR2}*.os
## 	${CLEAN} ${PSFT}*.o
## 	${CLEAN} ${PSFT}*.os
## 	#---(junk files)----------------------#
## 	${CLEAN} *~
## 	${CLEAN} temp*
## 
## bigclean           :
## 	${CLEAN} .*.swp
## 
## install            : ${BASE}
## 	#---(production version)--------------#
## 	${COPY}   ${BASE}    ${IDIR}/
## 	chown     root:root  ${IDIR}/${BASE}
## 	chmod     0700       ${IDIR}/${BASE}
## 	@sha1sum  ${BASE}
## 	#---(production version)--------------#
## 	${COPY}   ${TXF}     ${IDIR}/
## 	chown     root:root  ${IDIR}/${TXF} 
## 	chmod     0700       ${IDIR}/${TXF} 
## 	@sha1sum  ${TXF} 
## 	#---(conversion version)--------------#
## 	${COPY}   ${OTHER}   ${IDIR}/
## 	chown     root:root  ${IDIR}/${OTHER}
## 	chmod     0700       ${IDIR}/${OTHER}
## 	@sha1sum  ${OTHER}
## 	#---(conversion version)--------------#
## 	${COPY}   ${PSFT}    ${IDIR}/
## 	chown     root:root  ${IDIR}/${PSFT}
## 	chmod     0700       ${IDIR}/${PSFT}
## 	@sha1sum  ${PSFT}
## 	#---(conversion version)--------------#
## 	${COPY}   myfont.sh  ${IDIR}/myfont
## 	chown     root:root  ${IDIR}/myfont
## 	chmod     0700       ${IDIR}/myfont
## 	@sha1sum  myfont.sh
## 	#---(conversion version)--------------#
## 	${COPY}   ${CHARM}   ${IDIR}/
## 	chown     root:root  ${IDIR}/${CHARM}
## 	chmod     0700       ${IDIR}/${CHARM}
## 	@sha1sum  ${CHARM}
## 	${COPY}   ${CHAR2}   ${IDIR}/
## 	chown     root:root  ${IDIR}/${CHAR2}
## 	chmod     0700       ${IDIR}/${CHAR2}
## 	@sha1sum  ${CHAR2}
## 	#---(conversion version)--------------#
## 	${COPY}   ${SHORT}   ${IDIR}/
## 	chown     root:root  ${IDIR}/${SHORT}
## 	chmod     0700       ${IDIR}/${SHORT}
## 	@sha1sum  ${SHORT}
## 	#---(conversion version)--------------#
## 	${COPY}   ${YSTR}    ${IDIR}/
## 	chown     root:root  ${IDIR}/${YSTR}
## 	chmod     0700       ${IDIR}/${YSTR}
## 	@sha1sum  ${YSTR}
## 
## 
## remove             :
## 	#---(all versions)--------------------#
## 	${CLEAN}  ${IDIR}/${BASE}
## 
## 
## 
## #*============================----end-of-source---============================*#
