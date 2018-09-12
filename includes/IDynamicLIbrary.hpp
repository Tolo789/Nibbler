#ifndef I_DYNAMIC_LIBRARY_HPP
# define I_DYNAMIC_LIBRARY_HPP

class IDynamicLibrary {
	public:
		IDynamicLibrary() {};
		virtual ~IDynamicLibrary() {};
		virtual void	my_func () = 0;
};

#endif // !I_DYNAMIC_LIBRARY_HPP