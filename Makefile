###COMPILER###
CC = cc

###FLAGS###
CFLAGS = -Wextra -Wall -Werror
DEBUG_FLAGS = -g

###PROGRAM###
NAME = minishell

###DIRECTORIES###
SRCDIR = src
INCDIR = include
BINDIR = bin
OBJDIR = $(BINDIR)/obj
DEPDIR = $(BINDIR)/dep

#############################################################################################

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

SOURCES = $(shell find $(SRCDIR) -name '*.c') #TODO: change for submission
HEADERS = $(shell find $(INCDIR) -name '*.h')
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)
DEPS = $(SOURCES:%.c=$(DEPDIR)/%.d)

$(NAME): $(OBJECTS)
	@echo "$(YELLOW)Linking objects to create $(NAME)...$(NC)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)
	@echo "$(GREEN)Build successful!$(NC)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEPDIR)/$*)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -MF $(DEPDIR)/$*.d

-include $(DEPS)

#############################################################################################

all: $(NAME)

run: all
	@echo "$(GREEN)Running $(NAME)...$(NC)"
	./$(NAME)

leak: all
	@echo "$(GREEN)Running $(NAME) with valgrind...$(NC)"
	valgrind --leak-check=full --error-exitcode=1 ./$(NAME)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: all
	@echo "$(GREEN)Launching debugger for $(NAME)...$(NC)"
	gdb ./$(NAME)

format:
	@echo "Formatting code with clang-format..."
	clang-format -i $(SOURCES) $(HEADERS)

clean:
	@echo "$(RED)Cleaning up...$(NC)"
	rm -rf $(BINDIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run leak format