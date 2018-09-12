#include <dlfcn.h>
#include <iostream>

void	dlerror_wrapper() {
	std::cerr << "Error: " << dlerror() << std::endl;
	exit(EXIT_FAILURE);
}

int		main(int ac, char **av) {
	int		dl_index;
	void	*dl_handle;
	void	(*my_func_ptr)(void);

	if (ac != 4) {
		std::cout << "Need 3 din_lib path..!" << std::endl;
		exit(EXIT_FAILURE);
	}
	while (1) {
		std::cout << "Enter library choice (1 / 2 / 3): ";
		std::cin >> dl_index;
		if (dl_index <= 0 || dl_index > 3)
			std::cout << "Wrong number given..!" << std::endl;
		else {
			dl_handle = dlopen(av[dl_index], RTLD_LAZY | RTLD_LOCAL);
			my_func_ptr = (void (*)(void)) dlsym(dl_handle, "my_func");
			if (!my_func_ptr)
				dlerror_wrapper();

			my_func_ptr();

			dlclose(dl_handle);
		}

	}
	return 0;
}