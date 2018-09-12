NAME = nibbler

DL1_NAME = dl1.so

DL2_NAME = dl2.so

DL3_NAME = dl3.so


SDIR_MAIN = ./srcs_main/

SDIR_DL1 = ./srcs_dl1/

SDIR_DL2 = ./srcs_dl2/

SDIR_DL3 = ./srcs_dl3/


INCLUDES_DIR = includes


SRC_MAIN = 	$(SDIR_MAIN)main.cpp

SRC_DL1 = 	$(SDIR_DL1)test1.cpp

SRC_DL2 = 	$(SDIR_DL2)glfwGUI.cpp

SRC_DL3 = 	$(SDIR_DL3)test3.cpp


OBJ_MAIN = $(SRC_MAIN:.cpp=.o)

OBJ_DL1 = $(SRC_DL1:.cpp=.o)

OBJ_DL2 = $(SRC_DL2:.cpp=.o)

OBJ_DL3 = $(SRC_DL3:.cpp=.o)


ALL = $(DL1_NAME) $(DL2_NAME) $(DL3_NAME) $(NAME)


CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES_DIR)

DLFLAGS = $(CFLAGS) -shared -fPIC

DL1_FLAGS = $(DLFLAGS) `pkg-config --libs sdl2`

DL2_FLAGS = $(DLFLAGS) `pkg-config --libs glfw3` -framework OpenGL

DL3_FLAGS = $(DLFLAGS) `pkg-config --libs sfml-all`

CC = clang++

all: $(ALL)

$(DL1_NAME): $(OBJ_DL1)
	$(CC) $(DL1_FLAGS) -o $(DL1_NAME) $(OBJ_DL1)
	@echo "				$(DL1_NAME) created"

$(DL2_NAME): $(OBJ_DL2)
	$(CC) $(DL2_FLAGS) -o $(DL2_NAME) $(OBJ_DL2)
	@echo "				$(DL2_NAME) created"

$(DL3_NAME): $(OBJ_DL3)
	$(CC) $(DL3_FLAGS) -o $(DL3_NAME) $(OBJ_DL3)
	@echo "				$(DL3_NAME) created"

$(NAME): $(OBJ_MAIN)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_MAIN)
	@echo "				$(NAME) created"

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)

clean:
	@/bin/rm -f $(OBJ_MAIN) $(OBJ_DL1) $(OBJ_DL2) $(OBJ_DL3)
	@echo "				All project's .o deleted"

fclean: clean
	@/bin/rm -f $(ALL)
	@echo "				Exec and libraries deleted"

re: fclean all

.PHONY: all lib clean fclean re