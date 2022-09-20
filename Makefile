# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 15:25:19 by pbremond          #+#    #+#              #
#    Updated: 2022/09/20 21:31:20 by pbremond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
_BLACK			= \033[0;30m
_RED 			= \033[0;31m
_GREEN			= \033[0;32m
_BROWN			= \033[0;33m
_BLUE			= \033[0;34m
_PURPLE			= \033[0;35m
_CYAN			= \033[0;36m
_LIGHT_GRAY		= \033[0;37m
_DARK_GRAY		= \033[1;30m
_LIGHT_RED		= \033[1;31m
_LIGHT_GREEN	= \033[1;32m
_YELLOW			= \033[1;33m
_LIGHT_BLUE		= \033[1;34m
_LIGHT_PURPLE	= \033[1;35m
_LIGHT_CYAN		= \033[1;36m
_WHITE			= \033[1;37m
_NC 			= \033[0m

# Inverted, i.e. colored backgrounds
_IGREY			= \x1b[40m
_IRED			= \x1b[41m
_IGREEN			= \x1b[42m
_IYELLOW		= \x1b[43m
_IBLUE			= \x1b[44m
_IPURPLE		= \x1b[45
_ICYAN			= \x1b[46m
_IWHITE			= \x1b[47m

# Color reset
_COLOR_RESET	= \033[0m

# Folders
INCLUDES = include
SRC_DIR = src
OBJ_DIR = objs

# ============================================================================ #
# ============================================================================ #

# Source files common to mandatory and bonus parts
SRC_COMMON =	main.cpp	test.cpp

# ============================================================================ #
# ============================================================================ #

# Source files exclusive to mandatory part
SRC_MANDATORY =	$(SRC_COMMON)

# Makefile variables for mandatory
SRC_MANDATORY_PLUS_PATH = $(addprefix $(SRC_DIR)/, $(SRC_MANDATORY))
# OBJ = $(subst $(SRC_DIR)/, $(OBJ_DIR)/, $(patsubst %.cpp, %.o, $(SRC_MANDATORY_PLUS_PATH)))
FT_OBJ  = $(subst $(SRC_DIR)/, $(OBJ_DIR)/ft/,  $(patsubst %.cpp, %.o, $(SRC_MANDATORY_PLUS_PATH)))
STD_OBJ = $(subst $(SRC_DIR)/, $(OBJ_DIR)/std/, $(patsubst %.cpp, %.o, $(SRC_MANDATORY_PLUS_PATH)))

# ============================================================================ #
# ============================================================================ #

# Source files exclusive to bonuses
# SRC_BONUS =	$(SRC_COMMON) $(SOMETHING_SRC_BONUS)\
# 			bonus.cpp

# SOMETHING_SRC_FILES_BONUS =	bonus.cpp

# SOMETHING_SRC_BONUS =	$(addprefix something/,	$(RENDER_SRC_FILES_BONUS))

# # Makefile variables for bonuses
# SRC_BONUS_PLUS_PATH = $(addprefix $(SRC_DIR)/, $(SRC_BONUS))
# BONUS_OBJ = $(subst $(SRC_DIR)/, $(OBJ_DIR)/, $(patsubst %.cpp, %.o, $(SRC_BONUS_PLUS_PATH)))

# ============================================================================ #
# ============================================================================ #

LIBS = 

# NAME = ft_containers_test
FT_NAME  = ft_containers_test
STD_NAME = std_containers_test

# NAME_BONUS = ft_containers_test_bonus

CXX = clang++
ifdef BONUS
	CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98 -D BONUS
else
	CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98
endif

all : $(FT_NAME) $(STD_NAME)

$(FT_NAME): $(FT_OBJ)
	@echo "$(_PURPLE)Linking $(FT_NAME)$(_COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) $(FT_OBJ) -o $(FT_NAME) $(LIBS)
	@echo "$(_GREEN)DONE$(_COLOR_RESET)"

$(STD_NAME): $(STD_OBJ)
	@echo "$(_PURPLE)Linking $(STD_NAME)$(_COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) $(STD_OBJ) -o $(STD_NAME) $(LIBS)
	@echo "$(_GREEN)DONE$(_COLOR_RESET)"

bonus: fclean
	@make BONUS=1 all

$(NAME_BONUS): $(BONUS_OBJ)
	@echo "$(_PURPLE)Linking $(NAME_BONUS)$(_COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) $(BONUS_OBJ) -o $(NAME_BONUS) $(LIBS)
	@echo "$(_GREEN)DONE$(_COLOR_RESET)"

$(OBJ_DIR)/ft/%.o : $(SRC_DIR)/%.cpp
	@echo "$(_BLUE)Compiling $(basename $(notdir $*.o)) $(_COLOR_RESET)"
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -I./$(INCLUDES)

$(OBJ_DIR)/std/%.o : $(SRC_DIR)/%.cpp
	@echo "$(_BLUE)Compiling $(basename $(notdir $*.o)) $(_COLOR_RESET)"
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -D NAMESP=std -c $< -o $@ -I./$(INCLUDES)


re: fclean all

rebonus: fclean bonus

b: bonus

fclean: clean
	@echo "$(_RED)Deleting $(FT_NAME) $(STD_NAME) $(_COLOR_RESET)"
	@rm -rf $(FT_NAME) $(STD_NAME)

clean:
	@echo "$(_RED)Cleaning object files$(_COLOR_RESET)"
	@rm -rf $(OBJ_DIR)
	
.PHONY: clean fclean re all bonus
