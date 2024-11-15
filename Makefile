# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 16:36:18 by ltreser           #+#    #+#              #
#    Updated: 2024/11/15 20:59:57 by ltreser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#### MAIN SETTINGS ####

# Compiler to be used
CC				:= cc

# Compiler flags
CFLAGS			:= -Wall -Werror -Wextra #-fsanitize=thread

# Include directories
INCLUDES		:= -Iinclude/

# Target executable
TARGET			:= philo

# Source files directory
SRC_DIR			:= src/

# Source files
SRC_FILES		+= main.c 
SRC_FILES		+= parse.c
SRC_FILES		+= utils.c
SRC_FILES		+= init.c
SRC_FILES		+= run.c
SRC_FILES		+= mutex.c
SRC_FILES		+= free.c

# Object files directory
OBJ_DIR			:= obj/

# Dependency files directory
DEP_DIR			:= dep/

# Object files
OBJ_FILES		:= $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC_FILES))

# Dependency files
DEPENDS			:= $(patsubst %.o, $(DEP_DIR)%.d, $(OBJ_FILES))
-include $(DEPENDS)

#### SHELL COMMANDS ####

RM				:= /bin/rm -f
MKDIR			:= /bin/mkdir -p
TOUCH			:= /bin/touch

#### DEBUG SETTINGS ####

ifeq ($(DEBUG), 1)
	CFLAGS		+= -g3
endif

#### TARGET COMPILATION ####

.DEFAULT_GOAL := all

quick: ## Run recipes simultaneously
	@$(MAKE) -j all

all: $(TARGET) ## Build this project

# Compilation rule for object files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(MKDIR) $(@D) 
	$(CC) $(CFLAGS) -MMD -MF $(patsubst %.o, %.d, $@) $(INCLUDES) -c $< -o $@

# Rule for linking the target executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES) $(INCLUDES)
	-@echo -n "$(MAGENTA)" && ls -lah $(TARGET) && echo -n "$(RESET)"

#### ADDITIONAL RULES ####

clean: ## Clean objects and dependencies
	$(RM) $(OBJ_FILES)
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(DEP_DIR)

fclean: clean ## Restore project to initial state
	$(RM) $(TARGET)

re: fclean quick ## Rebuild project

help: ## Show help info
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | \
		awk 'BEGIN {FS = ":.*?## "}; {printf "$(CYAN)%-30s$(RESET) %s\n", $$1, $$2}'

.PHONY: all re clean fclean help

#### UTILITIES ####

# Utility commands
RM			:= /bin/rm -f
MKDIR		:= /bin/mkdir -p

#### COLORS ####
# Color codes
RESET		:= \033[0m
BOLD		:= \033[1m
UNDERLINE	:= \033[4m

# Regular colors
BLACK		:= \033[30m
RED			:= \033[31m
GREEN		:= \033[32m
YELLOW		:= \033[33m
BLUE		:= \033[34m
MAGENTA		:= \033[35m
CYAN		:= \033[36m
WHITE		:= \033[37m
