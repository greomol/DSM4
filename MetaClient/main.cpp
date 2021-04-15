#define _USE_MATH_DEFINES 1
#include <math.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include "MetaClient.h"
#include "TransportConnectionTCP.h"
#include "Serializer.h"
#include "Thread.h"
#include <signal.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

template <typename T>
class NVector {
public:
	NVector(int size) : SIZE(size)
	{
		v = new T[SIZE];
		for (size_t i = 0; i < SIZE; i++)
		{
			v[i] = 0;
		}
	}
	NVector(NVector const &oth) : v(oth.s)
	{
		v = new T[SIZE];
		for (size_t i = 0; i < SIZE; i++)
		{
			v[i] = oth.v[i];
		}
	}
    ~NVector()
    {
        delete v;
    }

	T *v;
	int SIZE;
	string str() const 
	{
		stringstream ret;
		ret << "(";
		for (size_t i = 0; i < SIZE-1; i++)
		{
			ret << v[i] << ",";
		}
		ret << v[SIZE-1] << ")";
		return ret.str();
	}

	NVector &operator +=(NVector<T> const &oth)
	{
		for (size_t i = 0; i < SIZE; i++)
		{
			this->v[i] += oth.v[i];
		}
		return *this;
	}

	NVector &operator -=(NVector<T> const &oth)
	{
		for (size_t i = 0; i < SIZE; i++)
		{
			this->v[i] -= oth.v[i];
		}
		return *this;
	}

	static NVector zero(int SIZE)
	{
		NVector<T> ret(SIZE);
		for (size_t i = 0; i < SIZE; i++)
		{
			ret.v[i] = 0.;
		}
		return ret;
	}

	NVector &operator *=(T val)
	{
		for (size_t i = 0; i < SIZE; i++)
		{
			v[i] *= val;
		}
		return *this;
	}

	bool operator<(NVector<T> const &second) const
	{
		//		printf("%s < %s = ", str().c_str(), second.str().c_str());
		int i;
		for (i = 0; i < SIZE; i++)
		{
			if (this->v[i] > second.v[i])
			{
				//				printf("false\n");
				return false;
			}
			if (this->v[i] < second.v[i])
			{
				//				printf("true\n");
				return true;
			}
		}
		//		printf("false\n");
		return false;
	}

	bool inArea(NVector<T> const &first, NVector<T> const &second)
	{
		for (size_t i = 0; i < SIZE; i++)
		{
			if (this->v[i] < first.v[i] || this->v[i] > second.v[i]) return false;
		}
		return true;
	}

	double length() const 
	{
		double s = 0;
		for (int i = 0; i < SIZE; i++)
		{
			s += v[i] * v[i];
		}
		return ::sqrt(s);
	}


};

string 
adsorb_ini_generate(DS::uint64 serial, double *v, string &log_file, string &dat_file)
{
	char bbb[128];
	sprintf(bbb,"INI_%lld.DAT", serial);
        dat_file = bbb;
	FILE *fp = fopen(bbb, "w");
	if (fp == NULL) 
	{
		throw "adsorb_ini_generate: can't create output file";
	}
	fprintf(fp,
		"N=4\n"
		"M=4\n"
		"Tolerance=1e-10\n"
		"y0=0.17123\n"
		"y1=0\n"
		"y2=0\n"
		"y3=0.3076\n"
		"initial_t=0\n"
		"final_t=240\n"
		"save_time=10\n"
		"tau=0.0001\n"
		"tau_min=1e-8\n"
		"tau_max=0.001\n"
		"output=solution_%lld.dat\n"
		"P9=2.7\n"
		"P10=0.4615\n"
		"P11=0.5136\n"
		"errorlog=error_%lld.log\n", serial, serial);

	char ccc[128];
	sprintf(ccc, "error_%lld.log", serial);
 	log_file = ccc;
	for (int i = 0; i < 8; i++) {
		fprintf(fp, "P%d=%.6g\n", i+1, v[i]);
	}
	fclose(fp);
	return bbb;
}

static void skip(FILE *fpin)
{
	int c;
	while (!feof(fpin)) 
	{
		if ( (c = fgetc(fpin)) == '\n')
		{
			break;
		}
		if (c == EOF)
		{
			break;
		}
	}
}

static string get(FILE *fpin)
{
	int c;
	string ret;
	while (!feof(fpin)) 
	{
		c = fgetc(fpin);
		if ( c == '\n' || c == EOF) 
		{
			break;
		}
		ret.push_back((char)c);
	}
	return ret;
}

static double getnumber(string const &src, int &start)
{
	string ret;
	while (start < (int)src.size()) 
	{
		int c = src[start++];
		if (c == ';') 
		{
			break;
		}
		ret.push_back((char)c);
	}
	return atof(ret.c_str());
}

struct adsorb_result
{
	double Time,AlB,BC,AlC,AlB2,err;
	double sum;
};

struct exp_data {
	double initbc, initac;
	double time;
	double sorb_b, sorb_a;
};

double sqr(double x) { return x * x; }

adsorb_result adsorb_sum(string const &mainFile, string const &ifn)
{
	FILE *fpin = fopen(ifn.c_str(), "r");
	if (fpin == NULL) 
	{
		fprintf(stderr,"File '%s' error", ifn.c_str());
		throw "adsorb_sum: Can't open input file";
	}
	exp_data e[5];
	for (int i = 0; i < 5; i++) {
		if (fscanf(fpin, "%lg %lg %lf %lg %lg\n", &e[i].initbc, &e[i].initac, &e[i].time, &e[i].sorb_b, &e[i].sorb_a) != 5) {
			throw "adsorb_sum: invalid file format";
		}
	}
	fclose(fpin);

	FILE *fpmain = fopen(mainFile.c_str(), "r");
	if (fpmain == NULL)	{
		throw "adsorb_sum: Can't open main input file";
	}

	double sum = 0;
	string skip = get(fpmain);
	for (;;)
	{
		double Time,AlB,BC,AlC,AlB2,err;
		if (fscanf(fpmain, "%lf %lf %lf %lf %lf %lf\n", &Time, &AlB, &BC, &AlC, &AlB2, &err) != 6) {
			if (Time < 240) {
				sum = 1E99;
			}
			break;
		}
		if (fabs(err) > 1E-3) {
			sum = 1E100;
			break;
		}
		for (int i = 0; i < 5; i++) {
			if (fabs(e[i].time - Time) < 1) {
				sum += sqr(e[i].sorb_a - AlC);
				sum += sqr(e[i].sorb_b - BC);
			}
		}
	}
	fclose(fpmain);
	adsorb_result tr;
	tr.sum = sum;
	return tr;
}

void run_adsorb(string const &ini_name)
{
#ifdef _MSC_VER
    string exe = "rosenbroke ";
#else
	string exe = "./rosenbroke ";
#endif
	exe += ini_name;
	system(exe.c_str());
}

double adsorb_calculate(DS::uint64 serial, NVector<double> const &p)
{
	// There come 11 parameters in p.v[0..10]
	
	printf("adsorb_calculate(");
	for (int i = 0; i < 7; i++) {
		printf("%.2g, ", p.v[i]);
	}
	printf("%.2g)\n",p.v[7]);
	string log_file, dat_file;
	string res_file = adsorb_ini_generate(serial, p.v, log_file, dat_file);
	run_adsorb(res_file);
	char sf[128];
	sprintf(sf, "solution_%lld.dat", serial);
	adsorb_result tr = adsorb_sum(sf, "exper.dat");
	fprintf(stderr, "adsorb_calculate(");
	for (int i = 0; i < 7; i++) {
		fprintf(stderr, "%.2g, ", p.v[i]);
	}
	fprintf(stderr,"%.2g) = %.2g\n",p.v[7], tr.sum);
	unlink(res_file.c_str());
 	unlink(log_file.c_str());
	unlink(sf);
	return tr.sum;
}


static int interrupted = 0;
void sigfunc(int signo)
{
	interrupted = 1;
}

int
main(int argc, char **argv)
{
	MetaClient   grid;
	::signal(SIGINT, sigfunc);
    srand(time(NULL));
	string ip = "188.165.223.171";
	if (argc > 1)
	{
		ip = argv[1];
	}

	string myname = DS::TransportConnectionTCP::getLocalName();
	try {
		for (;;)
		{
			try
			{
				try 
				{
					grid.connectToServer(ip);
				} 
				catch (DS::Exception const &ex)
				{
					DS::Thread::sleep(1000);
					continue;
				}
				int code = grid.announceReady(myname, "Windows", 32, 8192, 4);

				std::cout << code << endl;
				DS::Deserializer des;
				grid.prepareTask(myname, des);
				for (;;)
				{
					if (interrupted) break;
					grid.launchTask(myname, des);
					DS::Deserializer d2;
					DS::uint32 ret = des.getUint32();
					if (ret == DS::Error::QueueIsEmpty)
					{
						DS::Thread::sleep(1);
						continue;
					}
					if (ret != DS::Error::OK)
					{
						break;
					}
					DS::uint64 serial = des.getUint64();
					des.getDeserializer(d2);
					int size = d2.getUint32();
					NVector<double> tf_arg(size);
					for (int i = 0; i < size; i++)
					{
						tf_arg.v[i] = d2.getDouble();
					}
					string tf_name = d2.getString();
					// cout << "serial=" << serial << "; ready to start task " << tf_name << "(" << ax << "," << ay << ")\n";
					//double res = tritask_calculate(tf_arg); // testf(tf_arg);
					double res;
					// Not very good code....
					if (tf_name == "adsorb_calculate") 
					{
						res = adsorb_calculate(serial, tf_arg);
					} 
					DS::Serializer ser;
					ser.putUint32(interrupted == 0 ? DS::Error::OK : DS::Error::YetNotImplemented);
					ser.putUint64(serial);
					ser.putUint32(size);
					for (int i = 0; i < size; i++)
					{
						ser.putDouble(tf_arg.v[i]);
					}
					ser.putDouble(res);
					grid.taskCompleted(myname, ser);
				}
				code = grid.announceLeave(myname, 0);
				grid.disconnectFromServer(ip);
			}
			catch (DS::Exception const &ex)
			{
				cout << "Caught exception " << DS::Error::explain(ex.getCode()) << " in " << ex.getInfo() << "\n";
			}
			catch (const char* str)
			{
				cout << "Caught unknown exception " << str << "\n";
			}
		}
	}
	catch (int code)
	{
		cout << "Program ended with code " << code << endl;
	}
	cout << "Program ended";
	return 0;
}
