#include "ft_ls.h"
#include "libft.h"
#include <stdarg.h>

void func(va_list args) {
    t_ls *st = va_arg(args, t_ls *);

    printf("Function called with args: %s\n", st->test);
}

int main(int ac, char **av) {
	(void)ac;
	(void)av;

	t_ls		ls = { .test = "kjgkj" };

	t_args		mappings[] = {
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

	for (int i = 1; i < ac; i++) {
        char *option = av[i];
        if (ft_parseargs(args, option, &ls)) {
            // Option found and processed
        } else {
            // Option not found
        }
    }
}