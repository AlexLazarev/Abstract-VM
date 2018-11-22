NAME = avm

SRC_DIR = ./sources/
OBJ_DIR = ./objects/
INC_DIR = ./includes/

SRC =   main.cpp OperandFactory.cpp Lexer.cpp Parser.cpp Operand.cpp
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++11
HFLAGS = -I $(INC_DIR)
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) -c $< -o $@ $(CFLAGS) $(HFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all
