3DODEV	= C:/3DODev/
ARMDEV	= C:/ARM250/
DEBUG	= 0

NAME	= LaunchMe
STACKSIZE = 10000
BANNER	= BannerDoom.bmp
FILESYSTEM	= takeme

CC		= $(ARMDEV)bin/armcc
AS 		= $(ARMDEV)bin/armasm
LD		= $(ARMDEV)bin/armlink
RM		= $(3DODEV)bin/rm
MODBIN	= $(3DODEV)bin/modbin
MAKEBANNER	= $(3DODEV)bin/MakeBanner


CCFLAGS = -bi -zps1 -za1 -wn -ff -fa -i /swst/fp -d DEBUG=$(DEBUG) -cpu ARM6 
ASFLAGS = -BI -i $(3DODEV)includes/
INCPATH	= -I $(3DODEV)includes/
LDFLAGS = -aif -r -b 0x00 -sym $(NAME).sym 
LIBPATH	= $(3DODEV)libs/
STARTUP = $(LIBPATH)cstartup.o

LIBS 	= $(LIBPATH)burger.lib \
	$(LIBPATH)lib3do.lib \
	$(LIBPATH)filesystem.lib \
	$(LIBPATH)graphics.lib \
	$(LIBPATH)audio.lib \
	$(LIBPATH)music.lib \
	$(LIBPATH)operamath.lib \
	$(LIBPATH)input.lib \
	$(LIBPATH)string.lib \
	$(LIBPATH)clib.lib \
	$(LIBPATH)swi.lib \
	$(LIBPATH)IntMath.lib \

#	$(LIBPATH)3dlib.lib $(LIBPATH)armlib.32b \
#	$(LIBPATH)compression.lib $(LIBPATH)codec.lib \
#	$(LIBPATH)cpluslib.lib $(LIBPATH)DataAcq.lib \
#	$(LIBPATH)DS.lib $(LIBPATH)exampleslib.lib \
#	$(LIBPATH)international.lib $(LIBPATH)jstring.lib \
#	$(LIBPATH)memdebug.lib $(LIBPATH)mvelib.lib \
#	$(LIBPATH)obsoletelib3do.lib $(LIBPATH)pgl.lib \
#	$(LIBPATH)Subscriber.lib \

SRC_S		= $(wildcard src/*.s)
SRC_C		= $(wildcard src/*.c)

OBJ	+= $(SRC_S:.s=.o)
OBJ	+= $(SRC_C:.c=.o)

all: $(NAME)


$(NAME): $(OBJ) 
	$(3DODEV)bin/MakeBanner.exe $(3DODEV)bin/BannerDoom.bmp  $(FILESYSTEM)/BannerScreen 
	$(LD) -dupok -o $(FILESYSTEM)/$(NAME). $(LDFLAGS) $(STARTUP) $(LIBS) $(OBJ)
	$(MODBIN) $(STACKSIZE) $(FILESYSTEM)/$(NAME)
	$(3DODEV)bin/3doiso.exe -in $(FILESYSTEM) -out C:\Doom\3DOWin.iso
	$(3DODEV)bin/3doencrypt.exe genromtags C:\Doom\3DOWin.iso

%.o: %.c 
	$(CC) $(INCPATH) $(CCFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(INCPATH) $(ASFLAGS) $< -o $@
	

clean:
	$(RM) -f $(OBJ)
	$(RM) -f $(FILESYSTEM)/$(NAME)
