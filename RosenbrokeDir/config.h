#pragma once
#include <string>
#include <vector>
using namespace std;

class CConfig
{
public:
    CConfig();
    bool load(string const &name);
    string get(string const &attr) const;
    double getDouble(string const &attr) const;
    int    getInt(string const &attr) const;
	bool   set(string const &str);  
	void set(string const &attr, string const &val);
	~CConfig();
private:
    struct map {
        string attr;
        string val;
    };
    vector<map> _values;
    string      _name;
};

