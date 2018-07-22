#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

#include "DSMTester.h"
#include "Types.h"
#include "Error.h"
#include "Client.h"
#include "Serializer.h"
#include "Exception.h"

DSMTester::DSMTester()
{
    _server = NULL;
    _client = NULL;
}

DSMTester::~DSMTester()
{
}

static vector<string> 
splitString(string const &s, string const &delim)
{
    vector<string> ret;
    string word;
    for (size_t i = 0; i < s.size(); i++)
    {
        if (delim.find(s[i]) == string::npos)
        {
            word.push_back(s[i]);
        }
        else
        {
            if (!word.empty())
            {
                ret.push_back(word);
                word.clear();
            }
        }
    }
    if (!word.empty())
    {
        ret.push_back(word);
        word.clear();
    }
    return ret;     
}

void unknownCommand( string const & cmd ) 
{
    cout << "command " << "`" << cmd << "' is not recognized\n"; 
}

bool
DSMTester::executeCommand(string const &cmd)
{
    vector<string> args = splitString(cmd, " \t");
    if (args.size() == 0)
    {
        return true;
    }
    if (args[0] == "server" && args.size() > 1)
    {
        if (args[1] == "start")
        {
			commandStartServer();
            return true;
        }
        else if (args[1] == "stop")
        {
            commandStopServer();
            return true;
        }
        else if (args[1] == "status")
        {
            cout << (_server == NULL ? "Server is not running" : "Server is running") << endl;
            return true;
        }
    }
    else if (args[0] == "client" && args.size() >= 3)
    {
        if (args[1] == "open")
        {
			commandClientOpen(args[2]);
        }
    }
    else if (args[0] == "help")
    {
        comandHelp();
        return true;
    }
    else if (args[0] == "quit")
    {
        return false;
    }
    else if (args[0] == "run" && args.size() > 1)
    {
        commandRun(args[1]);
        return true;
    }
    else 
    {
        if (!(args[0].size() == 0 || (args[0].size() > 1 && args[0][0] == '#')))
        {
            unknownCommand(cmd);
            return true;
        }
    }
    return true;
}

void 
DSMTester::commandStartServer()
{
    if (_server == NULL)
    {
		_server = new TesterServer();
    }
    DS::uint32 code = _server->start();
    cout << "return code is " << DS::Error::explain(code) << endl;
}

void 
DSMTester::commandStopServer()
{
    DS::uint32 code = DS::Error::ObjectIsNULL;
    if (_server != NULL)
    {
        code = _server->stop();
        delete _server;
    }
    _server = NULL;
    cout << "return code is " << DS::Error::explain(code) << endl;
}

void 
DSMTester::comandHelp()
{
    cout << "Valid commands are:\n";
    cout << "server start\n";
    cout << "server stop\n";
    cout << "server status\n";
    cout << "run file.inp\n";
	cout << "client open <addr>\n";
    cout << "help\n";
    cout << "quit\n";
}

void
DSMTester::commandRun(string const &arg)
{
    ifstream ifs;
    ifs.open(arg.c_str());
    if (ifs.fail())
    {
        cout << "Run: cannot open input file `" << arg << "'\n";
        return;
    }
    const int bufSize = 512;
    char buf[bufSize];
    while (!ifs.eof())
    {
         ifs.getline(buf, bufSize);
         executeCommand(buf);
    }
}


void test_mutex_simple(DS::Client &c, DS::Serializer &ser, DS::Deserializer &des)
{
	ser.clear();
	cout << "test create mutex" << endl;
	ser.putString("mutex1");
	c.call("CreateMutex", ser, des);
	DS::int32 ans = des.getInt32();
	cout << "answer: " << ans << endl;

	ser.clear();
	cout << "test create already existing mutex" << endl;
	ser.putString("mutex1");
	c.call("CreateMutex", ser, des);
	ans = des.getInt32();
	cout << "answer: " << ans << endl;

	ser.clear();
	cout << "test destroy non-existing mutex" << endl;
	ser.putString("mutex2");
	c.call("DestroyMutex", ser, des);
	ans = des.getInt32();
	cout << "answer: " << ans << endl;

	ser.clear();
	cout << "test acquire non-existing mutex" << endl;
	ser.putString("mutex2");
	c.call("AcquireMutex", ser, des);
	ans = des.getInt32();
	cout << "answer: " << ans << endl;

	ser.clear();
	cout << "test release non-existing mutex" << endl;
	ser.putString("mutex2");
	c.call("ReleaseMutex", ser, des);
	ans = des.getInt32();
	cout << "answer: " << ans << endl;

	ser.clear();
	cout << "test acquire existing mutex" << endl;
	ser.putString("mutex1");
	c.call("AcquireMutex", ser, des);
	ans = des.getInt32();
	cout << "answer: " << ans << endl;

	ser.clear();
	cout << "test release existing mutex" << endl;
	ser.putString("mutex1");
	c.call("ReleaseMutex", ser, des);
	ans = des.getInt32();
	cout << "answer: " << ans << endl;

	ser.clear();
	cout << "test destroy existing mutex" << endl;
	ser.putString("mutex1");
	c.call("DestroyMutex", ser, des);
	ans = des.getInt32();
	cout << "answer: " << ans << endl;
}


void test_mutex_conc(DS::Client &c, DS::Serializer &ser, DS::Deserializer &des)
{
	cout << "test mutex concurrent" << endl;
	ser.clear();
	ser.putString("mutex");
	c.call("CreateMutex", ser, des);
	for (int i = 0; i < 10; i++)
	{
		ser.clear();
		ser.putString("mutex");
		c.call("AcquireMutex", ser, des);
		Sleep(500);
		cout << "inside cs "<< i << endl;
		Sleep(500);
		ser.clear();
		ser.putString("mutex");
		c.call("ReleaseMutex", ser, des);
	}
	ser.clear();
	ser.putString("mutex");
	c.call("DestroyMutex", ser, des);
}


void
DSMTester::commandClientOpen(string const &name)
{
    try
    {
        DS::Client c;
        c.connect(name, "5555");

        DS::Serializer ser;
        DS::Deserializer des;
        cout << "test mul32" << endl;
        ser.putUint32(12345);
        ser.putUint32(54321);
        c.call("mul32", ser, des);
	    DS::uint32 res = des.getUint32();
	    cout << "Call mul32(12345,54321) = " << res << endl;

        ser.clear();
        cout << "test enum RPC names" << endl;
        c.call("enumRPCNames", ser, des);
        string en = des.getString();
        while (en.size() != 0)
        {
            cout << "found name: '" << en << "'" << endl;
            en = des.getString();
        }

		ser.clear();
        cout << "test extension" << endl;
        ser.putString("extension.dll");
        c.call("loadExtension", ser, des);
        DS::int32 code = des.getInt32();
        DS::int32 syscode = des.getInt32();
        cout << "code = " << code << " syscode = " << syscode << endl;

		test_mutex_simple(c, ser, des);
		test_mutex_conc(c, ser, des);

        c.disconnect(name);
    } catch (DS::Exception const &ex)
    {
        cout << "Exception:" << ex.getInfo() << "code =" <<  ex.getCode() << "(" << DS::Error::explain(ex.getCode()) << ")\n";
    }
}
