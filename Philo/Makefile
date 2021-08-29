NAME			= philo

CC				:= gcc
RM				:= rm -rf
LEAKS			= -g #-fsanitize=address
CFLAGS			= $(LEAKS) -pthread -Wall -Wextra -Werror -O2 

# LIBFT_GIT		:= https://github.com/axma331/libft.git
# LIBFT_DIR		:= libft
# LIBFT			:= $(LIBFT_DIR)/libft.a

HEADER			:= $(NAME).h

SRCS			:=	philo.c\
					philo_input_data.c\
					philo_threads.c\
					philo_utils_1.c\
					philo_utils_2.c

OBJ_DIR			:= .obj
OBJC			:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all:  			$(NAME) #libft_make

$(NAME): 		$(OBJC) Makefile
				@$(CC) $(OBJC) -o $@
				@echo "$(CLRCY)Создан$(CLRPR)$@$(CLRRS)"

$(OBJ_DIR)/%.o:	%.c $(LIBFT) $(HEADER) | $(OBJ_DIR)
				@$(CC) $(CFLAGS) -c $< -o $@
				@echo "$(CLRCY)Создан$(CLRGR)$@$(CLRRS)"

$(OBJ_DIR):
				@mkdir -p $@

bonus:			all

re:
				@make fclean
				@make all

clean:
# @-make clean -C $(LIBFT_DIR)
				@{ $(RM) $(OBJ_DIR);\
				echo "$(CLRCY)Очистка$(CLRRE)$(OBJ_DIR)$(CLRRS)"; }

fclean: clean
# @-make fclean -C $(LIBFT_DIR)
				@$(RM) $(NAME)
				@echo "$(CLRCY)Удаление$(CLRRE)$(NAME) $(CLRRS)"
libft_rm:
				@{ $(RM) $(LIBFT_DIR); \
				echo "$(CLRCY)Удаление$(CLRRE)$(NAME) $(CLRRS)"; }


libft_make:
				@make -C $(LIBFT_DIR) || { git clone $(LIBFT_GIT); make -C $(LIBFT_DIR); }

gitpush: fclean
				git status
				git add .
				git commit -m "New edition"
				git push

.PHONY: 		all re clean fclean libft_rm libft_make 




#-c говорит не запускать линкер, потому что нет main
#-g порождает отладочную информацию в родном формате операционной системы
#включает использование дополнительной отладочной информации, 
#которую может использовать только GDB; 
#эта дополнительная отладочная информация делает работу отладки в GDB лучше, но может, 
#вероятно испортить работу других отладчиков, или помешать им прочитать программу.

CLRRS = \033[0m #сброс цвета
BOLDf = \033[1m #жирный шрифт
UNDRL = \033[4m #подчеркивание
FONGR = \033[47m #серый цвет фона
CLRGR = \033[37m #серый цвет шрифта
FONCY = \033[46m #цвет морской волны фона		
CLRCY = \033[36m #цвет морской волны шрифта
FONPR = \033[45m #фиолетовый цвет фона
CLRPR = \033[35m #фиолетовый цвет шрифта
FONBL = \033[44m #синий цвет фона
CLRBL = \033[34m #синий цвет шрифта
FONEL = \033[43m #желтый цвет фона
CLREL = \033[33m #желтый цвет шрифта
FONGR = \033[42m #зелёный цвет фона
CLRGR = \033[32m #зелёный цвет шрифта
FONRE = \033[41m #красный цвет фона
CLRRE = \033[31m #красный цвет шрифта
FONBC = \033[40m #чёрный цвет фона
CLRBC = \033[30m #чёрный цвет шрифта
#COLOR+FON = \033[6;35m - можно совмещать \033[6 - цвет шрифта ;35m - цвет фона