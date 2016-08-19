#################################################################
#                    tdrdbo Ins 模块make文件
#文 件 名：
#        Makefile
#编译方法：
#     A、release版本：make
#        或           make clean;make
#        或           make clean;make -f Makefile
#     B、debug版本：  make mode=debug
#        或           make clean;make mode=debug
#        或           make clean;make mode=debug -f Makefile
#注意事项：
#        行首使用TAB键,避免使用空格
#################################################################

#基本路径【以下部分请勿修改】
BASE=$(PWD)
BASE_SOURCE=$(BASE)

#obj文件生成路径【以下部分固化后请勿修改】
HEADFILE=$(BASE)

OBJPATH=$(BASE)/obj

BASE_PATH=$(BASE)/..

#程序或lib路径【以下部分固化后请勿修改】
BINPATH=$(BASE_PATH)/../binall/lib

#=====================Begin:需要修改的部分==================
#源文件路径
SRC_MODULE=$(BASE)/src

#头文件路径
BASE_INCLUDE=$(BASE_PATH)/../include
INC_MODULE=$(BASE)/inc

#需要引入的所有源文件路径
VPATH=$(SRC_MODULE):$(SRC_TRACE):$(OBJPATH):$(BINPATH)

#需要引入的所有头文件路径
INCLUDES=-I$(BASE_INCLUDE) \
	-I$(INC_MODULE) \
	-I$(HEADFILE) \

#需要生成的obj文件
OBJ=brd_nsq_consumer.o \

#需要引入的库文件及路径
LIBALL= -L$(BINPATH) \
	-lnsq

#需要生成的程序名
LIBFILE=libbrd_nsq_consumer.so

#编译选项
OPTIONS=-Wno-deprecated
#=====================End:需要修改的部分====================

#【以下部分请勿修改】
ifeq ($(mode),debug)
	CC=gcc -DDEBUG -shared -fPIC -ggdb3 $(OPTIONS)
else
	CC=gcc -DNDEBUG -shared -fPIC -O2 $(OPTIONS)
endif

#【以下部分请勿修改】
FLAG=-fexceptions 

#【以下部分请勿修改】
build:$(LIBFILE)

#【以下部分请勿修改】
$(LIBFILE):$(OBJ)
	@echo 'link all file '
	@cd $(OBJPATH); $(CC) $(LIBALL) $(OBJ) -o $(BINPATH)/$(LIBFILE)
	@ldd $(BINPATH)/$(LIBFILE)
	@echo 'mv' $(LIBFILE) $(BINPATH)

#【以下部分请勿修改】
.SUFFIX:.cpp.o
.cpp.o:
	@if [ ! -d $(OBJPATH) ]; then mkdir $(OBJPATH); fi;
	@echo Compile file $<,`more $<|wc -l` lines ...
	@$(CC) -c $(INCLUDES) $(FLAG) $< -o $(OBJPATH)/$*.o

.SUFFIX:.c.o
.c.o:
	@if [ ! -d $(OBJPATH) ]; then mkdir $(OBJPATH); fi;
	@echo Compile file $<,`more $<|wc -l` lines ...
	@$(CC) -c $(INCLUDES) $(FLAG) $< -o $(OBJPATH)/$*.o

#【以下部分请勿修改】
.PHONY:clean

clean:
	@if [ ! -d $(OBJPATH) ]; then mkdir $(OBJPATH); fi;
	@echo Delete $(OBJ) $(LIBFILE)
	@rm -f $(BINPATH)/$(LIBFILE); cd $(OBJPATH); rm -f $(OBJ)
	@rm -f *.o
	@rm -f $(SRC_MODULE)/*.o

