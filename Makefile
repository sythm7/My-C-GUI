EXEC_NAME = MyApp
OBJDIR = obj
SRCDIRS = src src/windows
EXEC = bin/$(EXEC_NAME)
CFLAGS = -Wall -pedantic
INCLUDE_PATH = include
LIB_PATH = lib
LINKS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
EXTRAS = -mwindows
SRCS = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))
INCS = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.h))
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS = $(OBJS:.o=.d)

ifeq ($(OS),Windows_NT)
	SEPARATOR := \$(strip)
	CLEAN_COMMAND = del /S /q $(OBJDIR)\$(strip) bin\$(EXEC_NAME).exe
	STD_REDIRECTION = 2> NUL
else
	SEPARATOR := /
	CLEAN_COMMAND = rm -rf $(OBJDIR)/* $(EXEC)
	STD_REDIRECTION = 2>/dev/null
endif

$(EXEC_NAME) : $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o $(EXEC) -I $(INCLUDE_PATH) -L $(LIB_PATH) $(LINKS) $(EXTRAS)

$(OBJDIR)/%.o : %.c
	$(eval TEMP = $(subst /,$(SEPARATOR),$(dir $@)))
	@mkdir $(TEMP) $(STD_REDIRECTION) || echo Repertory $(TEMP) already exists. Skipping.
	gcc -MD -c $< -o $@ -I $(INCLUDE_PATH) -L $(LIB_PATH) $(LINKS)

debug : $(OBJS)
	$(eval CFLAGS += -g)
	gcc $(CFLAGS) $(OBJS) -o $(EXEC) -I $(INCLUDE_PATH) -L $(LIB_PATH) $(LINKS)

clean :
	$(CLEAN_COMMAND)

-include $(DEPS)