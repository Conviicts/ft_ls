#include "libft.h"

void func() {
    printf("Function for option1\n");
}

int main(int ac, char **av) {
	(void)ac;
	(void)av;
	t_args mappings[] = {
        { "-l", func },
        { "-R", func },
        { "-a", func },
        { "-r", func },
        { "-t", func }
    };

    t_argsArray args = {
        .mappings = mappings,
        .len = sizeof(mappings) / sizeof(mappings[0])
    };

	ft_parseargs(args, av[1]);
}