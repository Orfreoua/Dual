NAME = dual

CXX = g++

CXXFLAGS = -Wall -Wextra -Werror -std=c++17

SDL_LIBS = -lSDL2 -lSDL2_image

SRC =	srcs/main.cpp\
		srcs/Game.cpp\
		srcs/Character.cpp\
		srcs/Samurai.cpp\
		srcs/Animation.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling the executable..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SDL_LIBS)
	@echo "$(NAME) successfully built."

clean:
	@echo "Cleaning up files..."
	rm -f $(OBJ) $(NAME)
	@echo "Clean complete."

re: clean all

%.o: %.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@
