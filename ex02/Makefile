CC=g++
CPPFLAGS=-Werror -Wextra -Wall -std=c++98
NAME=PmergeMe
SRC=main.cpp PmergeMe.cpp
INC=PmergeMe.hpp
OBJ=main.p PmergeMe.o
header=.header

all : $(NAME)

$(NAME) : $(header) $(SRC)
	@$(CC) $(CPPFLAGS) $(SRC) -o $(NAME)
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
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME) .header

re: fclean all