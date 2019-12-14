ifeq ($(OS),WIN32)
SHELL := cmd.exe
endif

# Пути
#-------------------------------------------------------------------------------
TARGET	= Autorun
SOURCEDIRS	= ./SRC
INCLUDELIB += C:/Softune/lib/907/include/sample/MB90340
INCLUDE += ./INC 
SOURCES+= $(wildcard $(SOURCEDIRS)/*.c)
SOURCESASM= $(wildcard $(SOURCEDIRS)/*.asm)
LINCS=IO_DEF/io_def.rel

ifeq ($(MODE),DEBUG)
OUTPUTDIR	= Debug/ABS
OBJDIR = Debug/OBJ
LSTDIR = Debug/LST
else
OUTPUTDIR	= Release/ABS
OBJDIR = Release/OBJ
LSTDIR = Release/LST
endif

# Инструменты
#-------------------------------------------------------------------------------
ifeq ($(OS),WIN32)
AS = C:\Softune\BIN\fasm907s.exe
CC = C:\Softune\BIN\fcc907s.exe
LD = C:\Softune\BIN\flnk907s.exe
CV = C:\Softune\BIN\f2ms.exe
else
AS = wine ~/.wine/drive_C/Softune/BIN/fasm907s.exe
CC = wine ~/.wine/drive_C/Softune/BIN/fcc907s.exe
LD = wine ~/.wine/drive_C/Softune/BIN/flnk907s.exe
CV = wine ~/.wine/drive_C/Softune/BIN/f2ms.exe
endif
RM = -rm

# Флаги
#--------------------------------------------------------------------------------
ifeq ($(MODE),DEBUG)
CFLAGS=-g\
-O 0
else 
CFLAGS+=-O 1
endif

CFLAGS+=-w 5\
-I $(INCLUDELIB)\
-I $(INCLUDE)\
-model SMALL\
-B\
-c\
-cwno\
-cpu MB90F345C\
-cmsg

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
#-pl 60\
#-pw 100\

ifeq ($(MODE),DEBUG)
LDFLAGS=-xlf $(LSTDIR)/$(TARGET).mpx\
-slf $(LSTDIR)/$(TARGET).mps\
-mlf $(LSTDIR)/$(TARGET).mpm
LDFLAGS+=-m $(LSTDIR)/$(TARGET).mp1
else
LDFLAGS+=-m $(LSTDIR)/$(TARGET).mp1
endif

LDFLAGS+=-g
LDFLAGS+=-AL 2\
-ra _INRAM01=0x000100/0x0050FF\
-ro _INROM01=0xF80000/0xFFFFFF\
-check_rora\
-check_locate\
-rg 0\
-mmi\
-alin $(LSTDIR)\
-alout $(LSTDIR)\
-pl 60\
-pw 132\
-Xals\
-Xalr\
-na\
-nd\
-L C:/Softune/lib/907\
-w 2\
-cwno\
-a\
-cpu MB90F345C\
-cmsg

# Список файлов к удалению командой "make clean"
#-------------------------------------------------------------------------------
TOREMOVE += $(OUTPUTDIR)/*.abs
TOREMOVE += $(OUTPUTDIR)/*.mhx
TOREMOVE += $(OBJDIR)/*.obj
TOREMOVE += $(OBJDIR)/*.stk
TOREMOVE += $(LSTDIR)/*.*

# Список объектных файлов
#-------------------------------------------------------------------------------
OBJS =  $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.c=.obj)))
OBJS += $(addprefix $(OBJDIR)/,$(notdir $(SOURCESASM:.asm=.obj)))

all: $(OUTPUTDIR)/$(TARGET).abs

# Компиляция
#------------------------------------------------------------------------------- 
ifeq ($(MODE),DEBUG)
$(OBJDIR)/%.obj: $(SOURCEDIRS)/%.c 
	@echo compilation $<
	@$(CC) $(CFLAGS) -Xdof -o "$@" "$<" -INF STACK="$(@:.obj=.stk)"
else
$(OBJDIR)/%.obj: $(SOURCEDIRS)/%.c 
	@echo compilation $<
	@$(CC) $(CFLAGS) -Xdof -o "$@" "$<"
endif

$(OBJDIR)/%.obj: $(SOURCEDIRS)/%.asm
	@echo compilation $<
	@$(AS) $(AFLAGS) -Xdof -o "$@"  "$<"

# Линковка
#------------------------------------------------------------------------------- 
$(OUTPUTDIR)/$(TARGET).abs: $(OBJS)
	@echo Linc
	@$(LD) $(LDFLAGS) -o $(OUTPUTDIR)/$(TARGET).abs $(OBJS) $(LINCS) -Xdof
	@$(CV)	-cwno -o $(OUTPUTDIR)/$(TARGET).mhx $(OUTPUTDIR)/$(TARGET).abs
	
# Очистка
#-------------------------------------------------------------------------------
clean:
	@$(RM) -f $(TOREMOVE)  	
