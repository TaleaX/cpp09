CC=c++
CPPFLAGS=-Werror -Wextra -Wall -std=c++98
NAME=PMergeMe
SRC=main.cpp PMergeMe.cpp
INC=PMergeMe.hpp
header=.header

all : $(NAME)

$(NAME) : $(header) $(SRC) $(INC)
	@$(CC) $(SRC) $(INC) -o $(NAME)
	@echo "$(GREEN)Done$(RESET)"

$(header) :
	@touch .header
	@echo	"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"
	@echo	"░████████╗██████╗░███████╗██╗░░██╗███╗░░██╗███████╗░"
	@echo	"░╚══██╔══╝██╔══██╗██╔════╝██║░░██║████╗░██║██╔════╝░"
	@echo	"░░░░██║░░░██║░░██║█████╗░░███████║██╔██╗██║█████╗░░░"
	@echo	"░░░░██║░░░██║░░██║██╔══╝░░██╔══██║██║╚████║██╔══╝░░░"
	@echo	"░░░░██║░░░██████╔╝███████╗██║░░██║██║░╚███║███████╗░"
	@echo	"░░░░╚═╝░░░╚═════╝░╚══════╝╚═╝░░╚═╝╚═╝░░╚══╝╚══════╝░"
	@echo	"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"
clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) .header

re: fclean all