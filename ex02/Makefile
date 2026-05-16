# ---------------------------------------------------------------------------- #
# Makefile template v 2.2 (C++, one-file)							2026-04-26
# ---------------------------------------------------------------------------- #
# Features:
# - Multiple mode support (reg, asan, val)
# - Only one mode per invocation allowed						 __(°)<
# - Separate mandatory vs bonus part builds						 \_)_)
# - Easy to use: make run/runb/asan/asanb/val/valb				~~~~~~
# - Supports nested source subdirectories
# ---------------------------------------------------------------------------- #

# ============================================================================ #
# PART 0 -- project control
# ============================================================================ #
PROG_NAME		?= PmergeMe
# ----------------------------------------------------------------------------
# arguments for executing the program in the various modes
RUN_ARGS_reg	?= 982 845 9 352 1597 11 42
RUN_ARGS_asan	?= 982 845 9 352 1597 11 42
RUN_ARGS_val	?= 982 845 9 352 1597 11 42
# ----------------------------------------------------------------------------
VALGRIND_FLAGS	?=	--leak-check=full \
					--show-leak-kinds=all --errors-for-leak-kinds=all\
					--show-error-list=yes\
					--track-origins=yes

#	--errors-for-leak-kinds=all		
#	--show-error-list=yes			
#	--leak-check=full				
#	--show-leak-kinds=all			catch still reachable
#	--track-fds=yes					
#	--track-origins=yes				uninitialized reads, slow
#	--trace-children=yes			
#	--trace-children-skip=""		
#	--suppressions=					
#	--num-callers=20				longer stack traces
#	--quiet
#	--log-file=valgrind.log
#	--read-var-info=yes				slow
#	--tool=helgrind					threads data race 

# ----------------------------------------------------------------------------
# set to 0 if there is no libft in this project
USE_LIBFT	?= 0
# ----------------------------------------------------------------------------
# control commands
# Ensure PROG_NAME is filled
ifeq ($(words $(PROG_NAME)),0)
$(error You must fill the PROG_NAME variable.)
endif

# Enforce one goal per invocation (recommended); prevents `make clean asan`.
ifneq ($(words $(MAKECMDGOALS)),0)
ifneq ($(words $(MAKECMDGOALS)),1)
$(error Run with none or one goal per invocation. Got: $(MAKECMDGOALS))
endif
endif

# ============================================================================ #
# PART 1 -- sources
# ============================================================================ #
# Root directory that contains the source files. NO DIR SLASH
SRC_ROOT	?= src/

# This block takes files relative to the source root directory. eg:
SRC_MAN		?= main.cpp PmergeMe.cpp
SRC_BON		?= 

# Pattern for source files in subdirectories. WITH DIR SLASH
#   DIR_PARSER = parser/
#   SRC_PARSER = tokenize.c parse.c
#   SRC_MAN   += $(addprefix $(DIR_PARSER),$(SRC_PARSER))

# ============================================================================ #
# PART 2 -- headers
# ============================================================================ #
# List project headers with relative path to trigger rebuilds on header change.
# libft header is added automatically
HEADER		?= inc/PmergeMe.hpp
# Include directories (space-separated). Used to build CINCL flags.
INC_PATHS	?= inc/

# ============================================================================ #
# PART 3 -- build selection
# ============================================================================ #
# MODE affects flags + output directories; regular, sanitizer, valgrind
MODE	?= reg
# PART affects which sources are compiled; mandatory or bonus
PART	?= man

# Output layout to isolate objects and binaries per mode & part.
# NOTE: must be recursive (=), because MODE/PART are target-specific and change.
OBJ_DIR	= build/$(MODE)/$(PART)/
BIN_DIR	= bin/$(MODE)/$(PART)/
BIN		= $(BIN_DIR)$(PROG_NAME)

# Choose sources based on PART.
# NOTE: cannot use make directives (ifeq)
#		because they are set while reading not when builing
#		=> PART is target specific and can change
SRC	= $(if $(filter bon,$(PART)),$(SRC_BON),$(SRC_MAN))

OBJ	= $(addprefix $(OBJ_DIR),$(SRC:.cpp=.o))

# ============================================================================ #
# PART 4 -- libraries (libft and others)
# ============================================================================ #
# libft
LFT_ROOT	:= lib/libft/
LFT_DIR		= $(LFT_ROOT)lib/$(MODE)/
LFT_NAME	:= libft.a
# Other libraries go here: -lname -lname
LIBS		?=

# Construct or remove libft dependency references.
ifeq ($(USE_LIBFT),1)
	LFT_DEP		= $(LFT_DIR)$(LFT_NAME)
	CLIBS		= $(LFT_DEP) $(LIBS)
	INC_PATHS	+= $(LFT_ROOT)include/
	HEADER		+= $(LFT_ROOT)include/libft.h
	LFT_CLEAN	= @$(MAKE) -C $(LFT_ROOT) clean --no-print-directory
	LFT_FCLEAN	= @$(MAKE) -C $(LFT_ROOT) fclean --no-print-directory
	LFT_PRINT	= @$(MAKE) -C $(LFT_ROOT) print --no-print-directory
	LFT_NORM	= @$(MAKE) -C $(LFT_ROOT) norm --no-print-directory
else
	CLIBS	= $(LIBS)
endif

# ============================================================================ #
# PART 5 -- compiler + flags
# ============================================================================ #
CC		:= c++
C_FLAGS	?= -Wall -Wextra -Werror -Wpedantic -Wshadow -std=c++98
CINCL	= $(addprefix -I,$(INC_PATHS))

# Mode-specific flags (extend as you like)
C_FLAGS_reg		:=
C_FLAGS_asan	:= -g -fsanitize=address -fno-omit-frame-pointer -O0
C_FLAGS_val		:= -g -O0

# Final flags used for compilation/linking (recursive; MODE is target-specific)
CFLAGS	= $(C_FLAGS) $(C_FLAGS_$(MODE))

# ============================================================================ #
# PART 6 -- command targets
# ============================================================================ #

EXEC_STR	= ./$(BIN) $(RUN_ARGS_$(MODE))
EXEC_V_STR	= valgrind $(VALGRIND_FLAGS) ./$(BIN) $(RUN_ARGS_$(MODE))
END_STR		= printf '$(C_FUJI_GRAY3)::::::::::::\n$(C_RESET)'

define EXEC
	$(PRT_EXEC)
	@$(EXEC_STR)
	@$(END_STR)
endef
define EXEC_VALG
	$(PRT_VALG)
	@$(EXEC_V_STR)
	@$(END_STR)
endef

all:		MODE := reg
all:		PART := man
all:		build

bonus:		MODE := reg
bonus:		PART := bon
bonus:		build

run:		MODE := reg
run:		PART := man
run:		build
	$(EXEC)

runb:		MODE := reg
runb:		PART := bon
runb:		build
	$(EXEC)

asan:		MODE := asan
asan:		PART := man
asan:		build
	$(EXEC)

asanb:		MODE := asan
asanb:		PART := bon
asanb:		build
	$(EXEC)

val:		MODE := val
val:		PART := man
val:		build
	$(EXEC_VALG)

valb:		MODE := val
valb:		PART := bon
valb:		build
	$(EXEC_VALG)

print:
	@printf "$(C_SAKURA_BLOSSOM)"
	@printf '%s\n' '---BUILDING---'
	@printf '%s\n' "$(PROG_NAME)"
	@printf '%s\n' '---SRC ROOT---'
	@printf '%s\n' "$(SRC_ROOT)"
	@printf '%s\n' '---SRC_MAN---'
	@printf '%s\n' "$(SRC_MAN)"
	@printf '%s\n' '---SRC_BON---'
	@printf '%s\n' "$(SRC_BON)"
	@printf '%s\n' '---OBJ_DIR---'
	@printf '%s\n' "$(OBJ_DIR)"
	@printf '%s\n' '---CFLAGS---'
	@printf '%s\n' "$(CFLAGS)"
	@printf '%s\n' '---CLIBS---'
	@printf '%s\n' "$(CLIBS)"
	@printf '$(C_RESET)'
	$(LFT_PRINT)

clean:
	@rm -rf build
	@printf "$(C_BAMBOO_GREEN)$(PROG_NAME) clean complete$(C_RESET)\n"
	$(LFT_CLEAN)

fclean:		clean
	@rm -rf bin $(PROG_NAME)
	@printf "$(C_BAMBOO_GREEN)$(PROG_NAME) fclean complete$(C_RESET)\n"
	$(LFT_FCLEAN)

re:		fclean all

# the second make call assures that MODE and PART change affect SRC and OBJ
# (make expands dependencies right away and does not adapt them on later change)
build: prt $(LFT_DEP)
	@printf "$(C_BAMBOO_GREEN)"
	@$(MAKE) $(BIN) MODE=$(MODE) PART=$(PART) --no-print-directory
	@printf "$(C_RESET)"
	@printf '\n'

prt: 
	$(PRT_BUILD)

# this target ensures that change in libft is detected
ifeq ($(USE_LIBFT),1)
libft:
	@$(MAKE) -C $(LFT_ROOT) MODE=$(MODE) --no-print-directory
else
libft:
	@printf "$(C_FUJI_WHITE) There is $(C_AUTUMN_RED)$(C_BOLD)no libft "
	@printf "$(C_RESET_BOLD)$(C_FUJI_WHITE)support enabled.$(C_RESET)\n"
endif

norm:
#	$(LFT_NORM)
	@norminette -R CheckForForbiddenHeader \
	$(addprefix $(SRC_ROOT), $(SRC_MAN) $(SRC_BON)) $(HEADER)

.PHONY:	all bonus clean fclean re \
		run runb asan asanb val valb \
		print build libft norm

# ============================================================================ #
# PART 7 -- build rules
# ============================================================================ #

# Linking
$(BIN): $(OBJ)
	@mkdir -p $(@D)
	@printf "$(C_WINTER_BLUE)"
	$(CC) $(CFLAGS) $(OBJ) $(CLIBS) -o $@
	@printf "$(C_RESET)"
	@if [ "$(MODE)" = "reg" ]; then cp $(BIN) .; fi

# Compiling (plus subdir creation)
$(OBJ_DIR)%.o: $(SRC_ROOT)%.cpp $(HEADER)
	@mkdir -p $(@D)
	@printf "$(C_SUMI_5)"
	$(CC) $(CFLAGS) $(CINCL) -c $< -o $@
	@printf "$(C_RESET)"

# Ensure libft exists (if enabled)
$(LFT_DIR)$(LFT_NAME): libft

# ============================================================================ #
# PART 9 -- visuals
# ============================================================================ #

# MODE_TXT ?= $(if $(filter reg, $(MODE)),regular,$(if $(filter asan,$(MODE)),sanitizer,valgrind))
MODE_TXT = $(strip \
  $(if $(filter reg,$(MODE)),regular, \
  $(if $(filter asan,$(MODE)),sanitizer,valgrind)) \
)

PART_TXT = $(if $(filter man, $(PART)),mandatory,bonus)

define PRT_BUILD
	@printf '\n'
 	@printf '$(C_AUTUMN_ORANGE)   building: '
	@printf '$(C_FUJI_WHITE)binary $(C_BOLD)$(PROG_NAME)$(C_RESET_BOLD) '
	@printf 'for $(C_ITALIC)$(MODE_TXT)$(C_RESET_ITALIC) use '
	@printf 'with $(C_ITALIC)$(PART_TXT)$(C_RESET_ITALIC) files.$(C_RESET)\n'
	@printf '$(C_FUJI_GRAY3)°°°°°°°°°°°°\n$(C_RESET)'
endef

define PRT_EXEC
	@printf '$(C_AUTUMN_ORANGE)  executing: '
	@printf '$(C_FUJI_WHITE)$(EXEC_STR)$(C_RESET)\n'
	@printf '$(C_FUJI_GRAY3)°°°°°°°°°°°°\n$(C_RESET)'
endef

# 	@printf '\n'
define PRT_VALG
	@printf '$(C_AUTUMN_ORANGE)  executing: '
	@printf '$(C_FUJI_WHITE)$(EXEC_V_STR)$(C_RESET)\n'
	@printf '$(C_FUJI_GRAY3)°°°°°°°°°°°°\n$(C_RESET)'
endef

# ============================
#  RESET / BASE
# ============================
C_RESET       := \033[0m
C_BOLD         := \033[1m
C_DIM          := \033[2m
C_ITALIC       := \033[3m
C_UNDERLINE    := \033[4m
C_BLINK        := \033[5m
C_REVERSE      := \033[7m
C_HIDDEN       := \033[8m
C_STRIKE       := \033[9m
C_DUNDERLINE   := \033[21m
C_RESET_BOLD       := \033[22m
C_RESET_DIM        := \033[22m
C_RESET_ITALIC     := \033[23m
C_RESET_UNDERLINE  := \033[24m
C_RESET_BLINK      := \033[25m
C_RESET_REVERSE    := \033[27m
C_RESET_HIDDEN     := \033[28m
C_RESET_STRIKE     := \033[29m


# ============================
#  SUMI INK (background tones from darkest to lightest)
# ============================
C_SUMI_0      := \033[38;2;17;17;27m
C_SUMI_1      := \033[38;2;22;22;29m
C_SUMI_2      := \033[38;2;36;40;59m
C_SUMI_3      := \033[38;2;54;58;79m
C_SUMI_4      := \033[38;2;65;69;89m
C_SUMI_5      := \033[38;2;74;78;100m

# ============================
#  FUJI (foreground text from brightest to darkest)
# ============================
C_FUJI_WHITE  := \033[38;2;235;219;178m
C_FUJI_GRAY   := \033[38;2;198;188;167m
C_FUJI_GRAY2  := \033[38;2;169;159;139m
C_FUJI_GRAY3  := \033[38;2;147;137;117m

# ============================
#  WAVE BLUES (signature from darker to brighter)
# ============================
C_WAVE_BLUE1  := \033[38;2;38;66;86m
C_WAVE_BLUE2  := \033[38;2;65;90;119m
C_DRAGON_BLUE  := \033[38;2;72;103;131m
C_WINTER_BLUE  := \033[38;2;110;134;161m

# ============================
#  WARM ACCENTS
# ============================
C_AUTUMN_RED    := \033[38;2;223;113;113m
C_AUTUMN_YELLOW := \033[38;2;224;175;104m
C_AUTUMN_GREEN  := \033[38;2;152;195;121m
C_AUTUMN_ORANGE := \033[38;2;255;158;100m
C_AUTUMN_PURPLE := \033[38;2;198;160;246m

# ============================
#  SAKURA / LOTUS ACCENTS
# ============================
C_SAKURA_PINK     := \033[38;2;223;142;155m
C_SAKURA_BLOSSOM  := \033[38;2;255;204;212m

# ============================
#  NATURAL GREENS
# ============================
C_BAMBOO_GREEN  := \033[38;2;133;153;0m
C_SPRING_GREEN  := \033[38;2;152;195;121m
C_MOSS_GREEN    := \033[38;2;106;153;85m
