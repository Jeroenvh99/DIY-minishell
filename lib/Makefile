LIB	:= libft.a

.PHONY: all clean fclean re

all: $(LIB)

libft.a:
	@$(MAKE) --directory=./libft/
	@ln -fs ./libft/$@ ./$@

clean:
	@-$(MAKE) --directory=./libft/ clean

fclean: clean
	@-$(MAKE) --directory=./libft/ fclean
	@rm -f ./libft.a

re: fclean all
