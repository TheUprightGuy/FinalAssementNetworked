#pragma once
#ifndef __MENU_H__

#include "utils.h"
#include "button.h"
#include <string.h>
#include <map>
class CMenu
{
public:
	CMenu(){}
	~CMenu()
	{
	}

	void AddButton(CButton* m_pButton, std::string _key) { m_pMenu[_key] = m_pButton; }

	std::string GetSelection()
	{
		std::string selected;
		std::map<std::string, CButton*>::const_iterator it; // declare an iterator
		it = m_pMenu.begin(); // assign it to the start of the vector
		while (it != m_pMenu.end()) // while it hasn't reached the end
		{
			if (it->second->CheckCollision())
			{
				selected = it->first;
			}
			it++; // and iterate to the next element
		}

		return(selected);
	}

	void Render()
	{
		std::map<std::string, CButton*>::const_iterator it; // declare an iterator
		it = m_pMenu.begin(); // assign it to the start of the vector
		while (it != m_pMenu.end()) // while it hasn't reach the end
		{
			it->second->Render();
			it++; // and iterate to the next element
		}
	}

	CButton* GetButton(std::string _button) { return(m_pMenu[_button]); }
private:
	std::map<std::string, CButton*> m_pMenu;
};
#endif