# Пути
TARGET	= Autorun

INCLUDELIB = C:/Softune/lib/907/include/sample/MB90340
INCLUDELIB += -I C:/Softune/lib/907/include
INCLUDE = INC
SOURCEDIRS = SRC
 
LINCS=IO_DEF/io_def.rel

ifeq ($(MODE),DEBUG)
OUTPUTROOT = DEBUG
else
OUTPUTROOT = RELEASE
endif

OUTPUTDIR = $(OUTPUTROOT)/ABS
OBJDIR = $(OUTPUTROOT)/OBJ
LSTDIR = $(OUTPUTROOT)/LST
#-------------------------------------------------------------------------------

# Инструменты
ifeq ($(OS),WIN32)
AS = C:/Softune/BIN/fasm907s.exe
CC = C:/Softune/BIN/fcc907s.exe
LD = C:/Softune/BIN/flnk907s.exe
CV = C:/Softune/BIN/f2ms.exe
else
AS = wine ~/.wine/drive_C/Softune/BIN/fasm907s.exe
CC = wine ~/.wine/drive_C/Softune/BIN/fcc907s.exe
LD = wine ~/.wine/drive_C/Softune/BIN/flnk907s.exe
CV = wine ~/.wine/drive_C/Softune/BIN/f2ms.exe
endif
RM = rm -rf

.PHONY: directories
all: $(OUTPUTDIR)/$(TARGET).mhx
directories: $(OUTPUTDIR) $(OBJDIR) $(LSTDIR)
$(OUTPUTDIR): $(OUTPUTROOT)
	mkdir $(OUTPUTDIR)
$(OBJDIR): $(OUTPUTROOT)
	mkdir $(OBJDIR)
$(LSTDIR): $(OUTPUTROOT)
	mkdir $(LSTDIR)

$(OUTPUTROOT):
	mkdir $(OUTPUTROOT)

#Список исхоных файлов
SOURCES+= $(wildcard $(SOURCEDIRS)/*.c)
SOURCESASM= $(wildcard $(SOURCEDIRS)/*.asm)
#-------------------------------------------------------------------------------

#Флаги компилятора--------------------------------------------------------------
CFLAGS =-cpu MB90F345C -model SMALL\
-I $(INCLUDELIB) -I $(INCLUDE)\
-B -cwno -cmsg -w 5 -K VOLATILE -Xdof
ifeq ($(MODE),DEBUG)
CFLAGS += -g -O 0
else 
CFLAGS += -O 1
endif
#-------------------------------------------------------------------------------

# Компиляция--------------------------------------------------------------------
ifeq ($(MODE),DEBUG)
$(OBJDIR)/%.obj: $(SOURCEDIRS)/%.c directories
	@echo compilation $<
	@$(CC) $(CFLAGS)  -o "$@" "$<" -INF STACK="$(@:.obj=.stk)"
#-o "$@"	
else
$(OBJDIR)/%.obj: $(SOURCEDIRS)/%.c directories
	@echo compilation $<
	@$(CC) $(CFLAGS) -o "$@" "$<"
endif
#-------------------------------------------------------------------------------

#Флаги ассемблера---------------------------------------------------------------
ifeq ($(MODE),DEBUG)
AFLAGS=-g
endif

AFLAGS+=-w 2\
-linf ON\
-lsrc ON\
-lsec ON\
-lcros OFF\
-linc ON\
-lexp OBJ\
-tab 8\
-cwno\
-cpu MB90F345C\
-cmsg
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
$(OBJDIR)/%.obj: $(SOURCEDIRS)/%.asm directories
	@echo compilation $<
	@$(AS) $(AFLAGS) -Xdof -o "$@"  "$<"
#-------------------------------------------------------------------------------

# Список объектных файлов-------------------------------------------------------
OBJS =  $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.c=.obj)))
OBJS += $(addprefix $(OBJDIR)/,$(notdir $(SOURCESASM:.asm=.obj)))
#-------------------------------------------------------------------------------

#Флаги линковки-----------------------------------------------------------------
LDFLAGS = -cpu MB90F345C\
-ra _INRAM01=0x000100/0x0050FF\
-ro _INROM01=0xF80000/0xFFFFFF\
-check_rora\
-check_locate\
-l C:/Softune/lib/907/lib904s\
-a\
-rg 0\
-mmi\
-alin $(LSTDIR)\
-alout $(LSTDIR)\
-Xals\
-Xalr\
-na\
-nd\
-w 2\
-cwno\
-cmsg\
-AL 2\
-Xdof
ifeq ($(MODE),DEBUG)
LDFLAGS+=-xlf $(LSTDIR)/$(TARGET).mpx\
-slf $(LSTDIR)/$(TARGET).mps\
-mlf $(LSTDIR)/$(TARGET).mpm
LDFLAGS+=-m $(LSTDIR)/$(TARGET).mp1
LDFLAGS+=-g
else
LDFLAGS+=-Xm
endif
#-------------------------------------------------------------------------------

# Линковка----------------------------------------------------------------------
$(OUTPUTDIR)/$(TARGET).abs: $(OBJS)
	@echo Linc
	@$(LD) $(LDFLAGS) -o $(OUTPUTDIR)/$(TARGET).abs $(OBJS) $(LINCS) 
#--------------------------------------------------------------------------------

# Список файлов к удалению командой "make clean"--------------------------------
TOREMOVE = $(OUTPUTDIR)/*.abs
TOREMOVE += $(OUTPUTDIR)/*.mhx
TOREMOVE += $(OBJDIR)/*.obj
TOREMOVE += $(OBJDIR)/*.*
TOREMOVE += $(LSTDIR)/*.*
#-------------------------------------------------------------------------------	

#конвертирование----------------------------------------------------------------
$(OUTPUTDIR)/$(TARGET).mhx: $(OUTPUTDIR)/$(TARGET).abs
	@echo covertion
	@$(CV)	-cwno -cmsg -o $(OUTPUTDIR)/$(TARGET).mhx $(OUTPUTDIR)/$(TARGET).abs
# Очистка-----------------------------------------------------------------------
clean:
	@$(RM)  $(TOREMOVE)  	
