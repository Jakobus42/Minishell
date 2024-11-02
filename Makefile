###COMPILER###
CC = cc

###FLAGS###
CFLAGS = -Wextra -Wall -Werror -g -I$(INCDIR) -I$(LIBS)

###PROGRAM###
NAME = minishell

###DIRECTORIES###
SRCDIR = src
INCDIR = include
LIBS = libraries
BINDIR = bin
OBJDIR = $(BINDIR)/obj
DEPDIR = $(BINDIR)/dep

#############################################################################################

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

SOURCES := \
    $(SRCDIR)/core/main.c \
    $(SRCDIR)/core/builtins/builtins.c \
    $(SRCDIR)/core/builtins/cd.c \
    $(SRCDIR)/core/builtins/echo.c \
    $(SRCDIR)/core/builtins/exit.c \
    $(SRCDIR)/core/builtins/export.c \
    $(SRCDIR)/core/builtins/export_utils.c \
	$(SRCDIR)/core/builtins/exit_utils.c \
	$(SRCDIR)/core/builtins/redirect_builtins.c \
    $(SRCDIR)/core/env/env.c \
	$(SRCDIR)/core/env/env_utils_too.c \
    $(SRCDIR)/core/env/env_utils.c \
    $(SRCDIR)/core/executor/check_executable.c \
    $(SRCDIR)/core/executor/executor.c \
    $(SRCDIR)/core/executor/executor_utils.c \
    $(SRCDIR)/core/executor/redirections.c \
    $(SRCDIR)/core/expander/expand_token.c \
    $(SRCDIR)/core/expander/expander.c \
    $(SRCDIR)/core/parser/heredoc.c \
    $(SRCDIR)/core/parser/parser.c \
    $(SRCDIR)/core/parser/process_token.c \
    $(SRCDIR)/core/parser/syntax.c \
    $(SRCDIR)/core/shell/error.c \
    $(SRCDIR)/core/shell/free.c \
    $(SRCDIR)/core/shell/shell.c \
    $(SRCDIR)/core/shell/signal.c \
    $(SRCDIR)/core/tokenizer/token_types.c \
    $(SRCDIR)/core/tokenizer/tokenizer.c \
    $(SRCDIR)/utils/debug.c \
    $(SRCDIR)/utils/logger.c \
    $(SRCDIR)/utils/memory.c \
    $(SRCDIR)/utils/quote.c \
    $(SRCDIR)/utils/string.c

OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)
DEPS = $(SOURCES:%.c=$(DEPDIR)/%.d)

$(NAME): $(OBJECTS)
	make -C ./$(LIBS)/libft all
	@echo "$(YELLOW)Linking objects to create $(NAME)...$(NC)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) -lreadline ./$(LIBS)/libft/libft.a
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
	valgrind --errors-for-leak-kinds=all --leak-check=full --read-var-info=yes --show-error-list=yes \
	--show-leak-kinds=all --suppressions=./minishell.supp --trace-children=yes --track-origins=yes \
	--track-fds=all --trace-children-skip="/bin/*,/usr/bin/*,/usr/sbin/*,$(which -a norminette)" ./$(NAME)

debug: all
	@echo "$(GREEN)Launching debugger for $(NAME)...$(NC)"
	gdb ./$(NAME)

clean:
	make -C ./$(LIBS)/libft clean
	@echo "$(RED)Cleaning up...$(NC)"
	rm -rf $(BINDIR)

fclean: clean
	make -C ./$(LIBS)/libft fclean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run leak format