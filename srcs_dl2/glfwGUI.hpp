/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfwGUI.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 19:46:17 by jichen-m          #+#    #+#             */
/*   Updated: 2018/09/12 20:26:10 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFWGUI_HPP
# define GLFWGUI_HPP

# include <iostream>
# include "IDynamicLibrary.hpp"

class GlfwGUI: public IDynamicLibrary
{
    public:
        GlfwGUI(void);
        ~GlfwGUI(void);

        void    my_func();
};

extern "C"
{
	GlfwGUI	*getTest(void);
	void	deleteTest(GlfwGUI *test);
}

#endif