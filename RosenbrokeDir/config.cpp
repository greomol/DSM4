#define _CRT_SECURE_NO_WARNINGS 1

#include "config.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

CConfig::CConfig()
{
}

CConfig::~CConfig()
{
}

bool
CConfig::load(const std::string &name)
{
    _name = name;
    ifstream f;
    f.open(name.c_str());
    if (!f) return false;
    char    s[512];
    while (!f.eof())
    {
        f.getline(s, sizeof s);
		if (s[0] == ';') continue;
        if (s[0] == 0) break;
        set(s);
    }
    return true;
}

void   
CConfig::set(string const &attr, string const &val)
{
	for (size_t i = 0; i < _values.size(); i++)
	{
		if (_values[i].attr == attr)
		{
			_values[i].val = val;
		}
	}
	// Not found
	map o;
	o.attr = attr;
	o.val = val;
	_values.push_back(o);
}


bool
CConfig::set(string const &str)
{
	string attr;
	string val;
	bool isAttr = true;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == ';')
			break;
		if (str[i] == '=')
		{
			isAttr = false;

		}
		else
		{
			if (isAttr)
			{
				attr.push_back(str[i]);
			}
			else
			{
				val.push_back(str[i]);
			}
		}
	}
	if (!attr.empty() && !val.empty())
	{
		set(attr, val);
		return true;
	}
	return false;
}


string 
CConfig::get(string const &attr) const
{
    for (size_t i = 0; i < _values.size(); i++)
    {
        if (_values[i].attr == attr)
        {
            return _values[i].val;
        }
    }
    string o = "String '";
    o += attr;
    o += "' not found";
    throw o; //CError(o);
}

double CConfig::getDouble(string const &attr) const
{
    string v = get(attr);
    return atof(v.c_str());
}

int    CConfig::getInt(string const &attr) const
{
    string v = get(attr);
    return atoi(v.c_str());
}

