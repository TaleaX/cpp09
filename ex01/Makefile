CC=c++
CPPFLAGS=-Werror -Wextra -Wall -std=c++98
NAME=RPN
SRC=main.cpp RPN.cpp
OBJ=main.p RPN.o
INC=RPN.hpp
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