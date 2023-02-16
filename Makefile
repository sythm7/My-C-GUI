EXEC_NAME = MyApp
OBJDIR = obj
SRCDIRS = $(sort $(dir $(wildcard src/*/))) 
EXEC = bin/$(EXEC_NAME)
CFLAGS = -Wall -pedantic
SRCS = src/main.c $(foreach dir,$(SRCDIRS),$(wildcard $(dir)*.c))
INCS = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)*.h))
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS = $(OBJS:.o=.d)

ifeq ($(OS),Windows_NT)
	SEPARATOR = \$(strip)
	CLEAN_COMMAND = del /S /q $(OBJDIR)\$(strip) bin\$(EXEC_NAME).exe
	INCLUDE_PATH = -I include
	LIB_PATH = -L lib
	LINKS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lcomdlg32
	MKDIR = mkdir
	STD_REDIRECTION = 2> NUL
	EXTRAS = -mwindows
	END =
else
	SEPARATOR = /
	CLEAN_COMMAND = rm -rf $(OBJDIR)/* $(EXEC)
	INCLUDE_PATH =
	LIB_PATH =
	LINKS = $(shell sdl2-config --cflags --libs) $(shell pkg-config --cflags gtk+-3.0) $(shell pkg-config --libs gtk+-3.0) -lSDL2_image -lSDL2_ttf
	MKDIR = mkdir -p
	STD_REDIRECTION = 2>/dev/null
	EXTRAS = 
	END = -lm
endif

$(EXEC_NAME) : $(OBJS)
	gcc $(CFLAGS) $^ -o $(EXEC) $(INCLUDE_PATH) $(LIB_PATH) $(LINKS) $(EXTRAS) $(END)

$(OBJDIR)/%.o : %.c
	$(eval TEMP = $(subst /,$(SEPARATOR),$(dir $@)))
	@$(MKDIR) $(TEMP) $(STD_REDIRECTION) || echo Repertory $(TEMP) already exists. Skipping.
	gcc -MD -c $(CFLAGS) $< -o $@ $(INCLUDE_PATH) $(LIB_PATH) $(LINKS)

debug : CFLAGS += -g
debug : EXTRAS =
debug : $(EXEC_NAME)

clean :
	$(CLEAN_COMMAND)

-include $(DEPS)