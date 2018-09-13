/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwGUI.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmutti <cmutti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 19:46:17 by jichen-m          #+#    #+#             */
/*   Updated: 2018/09/13 11:17:21 by cmutti           ###   ########.fr       */
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
	GlfwGUI	*getGUI(void);
	void	deleteGUI(GlfwGUI *test);
}

#endif