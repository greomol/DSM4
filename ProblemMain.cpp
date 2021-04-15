#define _USE_MATH_DEFINES 1
#include <math.h>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <assert.h>

#ifdef GRAPHICS_CLIENT
#include "../GraphicsClient/GraphicsClient.h"
static GraphicsClient gc;
#endif

using namespace std;

#include "MetaControlServer.h"

static const double GOOGOL = 1.0e100;

static int do_print = 0;
const int PRINT_POINTS = 1;
const int PRINT_VALUES = 2;
const int PRINT_DEBUG_ZONES = 4;
const int PRINT_ZONES = 8;
const int PRINT_SCHEDULE = 16;


#include <stdio.h>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

class Param
{
public:
	Param()
	{
		initialized = false;
	}

	void init (double left, double right, double val) 
	{ 
		initialized = true;
		discrete = false; 
		this->left = left;
		this->right = right;
		this->val = val;
	}

	Param(double left, double right, double val) 
	{ 
		init (left, right, val);
	}

	void init (vector<int> const &iarg, size_t ival) 
	{ 
		initialized = true;
		discrete = true;
		imap = iarg;
		this->ival = ival;
	}

	Param(vector<int> const &iarg, size_t ival)
	{
		init(iarg, ival);
	}

	bool isDouble() const 
	{
		if (!initialized) 
		{
			throw "Not initialized";
		}
		return !discrete;
	}

	double getDouble() const 
	{
		if (!initialized) 
		{
			throw "Not initialized";
		}
		if (discrete)
		{
			throw "Not double";
		}
		return val;
	}

	double getLeft() const 
	{
		if (!initialized) 
		{
			throw "Not initialized";
		}
		if (discrete)
		{
			throw "Not double";
		}
		return left;
	}

	double getRight() const 
	{
		if (!initialized) 
		{
			throw "Not initialized";
		}
		if (discrete)
		{
			throw "Not double";
		}
		return right;
	}

	size_t getSize() const
	{
		if (!initialized) 
		{
			throw "Not initialized";
		}
		if (!discrete)
		{
			throw "Not discrete";
		}
		return imap.size();
	}

	size_t getIndex() const
	{
		if (!initialized) 
		{
			throw "Not initialized";
		}
		if (!discrete)
		{
			throw "Not discrete";
		}
		return ival;
	}

	void setIndex(size_t ival) 
	{
		if (!initialized) 
		{
			throw "Not initialized";
		}
		if (!discrete)
		{
			throw "Not discrete";
		}
		this->ival = ival;
	}

	void setDouble(double val)
	{
		if (!initialized) 
		{
			throw "Not initialized";
		}
		if (discrete)
		{
			throw "Not double";
		}
		this->val = val;
	}

	int getVal(size_t index) const
	{
		if (!initialized) 
		{
			throw "Not initialized";
		}
		if (!discrete)
		{
			throw "Not discrete";
		}
		return imap[index];
	}

	string str() const
	{
		stringstream t;
		t << "{";
		if (!initialized)
		{
			t << "UNINITIALIZED";
		}
		else
		{
			if (discrete)
			{
				t << "I(" << imap.size() << ": ";
				for (size_t i = 0; i < imap.size(); i++)
				{
					t << imap[i];
					if (i != imap.size() - 1)
					{
						t << ","; 
					}
				}
				t << ") V=" << ival;
			}
			else
			{
				t << "D(" << left << "," << right << ") V=" << val;
			}
		}
		t << "}";
		return t.str();
	}
private:
	bool initialized;
	bool    discrete;
	double  left, right, val;

	vector<int>   imap;
	size_t        ival;
};



class NVector {
public:
	NVector()
	{
	}

	void init(int size)
	{
		v.resize(size);
		for (int i = 0; i < size; i++)
		{
			v[i] = 0;
		}
	}

	NVector(int size)
	{
		v.resize(size);
		for (int i = 0; i < size; i++)
		{
			v[i] = 0;
		}
	}

	NVector(NVector const &oth) 
	{
		v.resize(oth.v.size());
		for (int i = 0; i < (int)v.size(); i++)
		{
			v[i] = oth.v[i];
		}
	}
	vector<double> v;
	NVector(int size, double x) 
	{
		init(size);
		v[0] = x;
		for (int i = 1; i < size; i++)
		{
			v[i] = 0;
		}
	}
	NVector(int size, double x, double y)
	{
		init(size);
		if (size > 0)
		{
			v[0] = x;
		}
		if (size > 1)
		{
			v[1] = y;
		}
		for (int i = 2; i < size; i++)
		{
			v[i] = 0;
		}
	}

	NVector(int size, double x, double y, double z) 
	{
		init(size);
		if (size > 0)
		{
			v[0] = x;
		}
		if (size > 1)
		{
			v[1] = y;
		}
		if (size > 2)
		{
			v[2] = z;
		}
		for (int i = 3; i < size; i++)
		{
			v[i] = 0;
		}
	}

	NVector(int size, double x, double y, double z, double t) 
	{
		init(size);
		if (size > 0)
		{
			v[0] = x;
		}
		if (size > 1)
		{
			v[1] = y;
		}
		if (size > 2)
		{
			v[2] = z;
		}
		if (size > 3)
		{
			v[3] = t;
		}
		for (int i = 4; i < size; i++)
		{
			v[i] = 0;
		}
	}

	string str() const 
	{
		stringstream ret;
		ret << "(";
		for (int i = 0; i < (int)v.size()-1; i++)
		{
			ret << v[i] << ",";
		}
		ret << v[v.size()-1] << ")";
		return ret.str();
	}

	NVector &operator +=(NVector const &oth)
	{
		for (int i = 0; i < (int)v.size(); i++)
		{
			this->v[i] += oth.v[i];
		}
		return *this;
	}

	NVector &operator -=(NVector const &oth)
	{
		for (int i = 0; i < (int)v.size(); i++)
		{
			this->v[i] -= oth.v[i];
		}
		return *this;
	}

	static NVector zero(int size)
	{
		NVector ret(size);
		for (int i = 0; i < size; i++)
		{
			ret.v[i] = 0.;
		}
		return ret;
	}

	NVector &operator *=(double val)
	{
		for (int i = 0; i < (int)v.size(); i++)
		{
			v[i] *= val;
		}
		return *this;
	}

	bool operator<(NVector const &second) const
	{
		int i;
		for (i = 0; i < (int)v.size(); i++)
		{
			if (this->v[i] > second.v[i])
			{
				//				printf("false\n");
				return false;
			}
			if (this->v[i] < second.v[i])
			{
				return true;
			}
		}
		return false;
	}

	bool inArea(NVector const &first, NVector const &second) const
	{
		for (int i = 0; i < (int)v.size(); i++)
		{
			if (this->v[i] < first.v[i] || this->v[i] > second.v[i]) return false;
		}
		return true;
	}

	double length() const 
	{
		double s = 0;
		for (int i = 0; i < (int)v.size(); i++)
		{
			s += v[i] * v[i];
		}
		return ::sqrt(s);
	}

	double distance(NVector const &oth) const
	{
		double ret = 0;
		for (int i = 0; i < (int)v.size(); i++)
		{
			ret += (v[i] - oth.v[i]) * (v[i] - oth.v[i]);
		}
		return ::sqrt(ret);
	}

	static double scale(double l, double r, double val)
	{
		double s = r - l;
		return (l + s * val);
	}

	static double reverseScale(double l, double r, double val)
	{
		double s  = val - l;
		return s / (r - l);
	}

	void scale(NVector const &orig, NVector const &l, NVector const &r)
	{
		for (int i = 0; i < (int)v.size(); i++)
		{
			v[i] = scale(l.v[i], r.v[i], orig.v[i]);
		}
	}

	void reverseScale(NVector const &orig, NVector const &l, NVector const &r)
	{
		for (int i = 0; i < (int)v.size(); i++)
		{
			v[i] = reverseScale(l.v[i], r.v[i], orig.v[i]);
		}
	}

	void scale(NVector const &orig, vector<Param> const &p)
	{
		for (int i = 0; i < (int)v.size(); i++)
		{
			if (p[i].isDouble())
			{
				v[i] = scale(p[i].getLeft(), p[i].getRight(), orig.v[i]);
			}
			else
			{
				size_t size = p[i].getSize();
				double st = p[i].getVal(0);
				double en = p[i].getVal(size-1);
				double cur = st + (en - st) * orig.v[i];
				size_t j;
				for (j = 0; j < size-1; j++)
				{
					double dlen = p[i].getVal(j+1) - p[i].getVal(j);
					if (cur >= p[i].getVal(j) - dlen/2. && cur <= p[i].getVal(j) + dlen/2.)
					{
						v[i] = (double)(int)(p[i].getVal(j) + 0.5);
						break;
					}
				}
				if (j == size-1)
				{
					v[i] = (double)(int)(p[i].getVal(j) + 0.5);
				}
			}
		}
	}

	void reverseScale(NVector const &orig, vector<Param> const &p)
	{
		for (int i = 0; i < (int)v.size(); i++)
		{
			if (p[i].isDouble())
			{
				v[i] = reverseScale(p[i].getLeft(), p[i].getRight(), orig.v[i]);
			}
			else
			{
				throw "Not implemented yet";
			}
		}
	}


	static double diameter(vector <NVector> const &a)
	{
		size_t size = a.size();
		double dmax = -GOOGOL;
		for (size_t i = 0; i < size-1; i++)
		{
			for (size_t j = i+1; j < size; j++)
			{
				double d = a[i].distance(a[j]);
				if (d > dmax)
				{
					dmax = d;
				}
			}
		}
		return dmax;
	}

	static vector< set<int> > findConsensusZones(vector <NVector> const &a, double diam)
	{
		vector <set<int> > ret;
		set<int> used;
		stack<int> toProbe;
		for (int i = 0; i < (int)a.size(); i++)
		{
			if (used.find(i) != used.end()) continue;
			toProbe.push(i);
			used.insert(i);
			set<int> s;
			s.insert(i);
			while (!toProbe.empty()) 
			{
				int k = toProbe.top(); toProbe.pop();
				for (size_t j = 0; j < a.size(); j++)
				{
					if (used.find(j) != used.end()) continue;
					double d = a[k].distance(a[j]);
					if (d < diam)
					{
						s.insert(j);
						used.insert(j);
						toProbe.push(j);
					}
				}
			}
			ret.push_back(s);
		}
		return ret;
	}
};

typedef double (*targetFunction)(NVector const &p);

class ProblemServer
{
private:
	int SIZE;
	map<NVector, double> _solved;
	unsigned long long _iterationsCount;
	unsigned long long _hashHits;
	string _logFileName;
	MetaScheduler *_metaScheduler;
public:
	ProblemServer(int size, MetaScheduler *scheduler) : SIZE(size)
	{
		_metaScheduler = scheduler;
		_iterationsCount = 0;
		_hashHits = 0;
	}

	size_t getSolvedSize() const { return _solved.size(); }

	void clearSolved() {
		_solved.clear();
	}

	unsigned long long getIterationsCount() const {
		return _iterationsCount;
	}

	unsigned long long getCacheHits() const {
		return _hashHits;
	}

	~ProblemServer()	{ }


	map<string, targetFunction> localMap;

	DS::uint64 schedule( NVector p, string const & tf, FILE * log ) 
	{
		// Schedule only not cached!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if (getCachedValue(p) < GOOGOL) return 0;
		MetaQueueItem g;
		g.ser.putUint32(SIZE);
		for (int i = 0; i < SIZE; i++) {
			g.ser.putDouble(p.v[i]);
		}
		g.ser.putString(tf);
		DS::uint64 serial;
		_metaScheduler->enqueueToInputQueue(g, serial);
		return serial;
	}

	void waitForPendingItems(set<DS::uint64> &pending, FILE *log) {
		log = log;
		MetaQueueItem it;
		DS::uint64 serial;
		int msec = 0;
		while (pending.size() > 0) {
                        fprintf(stderr,"%lu to go          \r", pending.size());
			int wcode = _metaScheduler->dequeueFromCompletedQueue(it, serial);
			if (wcode == DS::Error::OK)	{
				//
				msec = 0;
				pending.erase(serial);
				DS::Deserializer d2;
				it.des.getDeserializer(d2);
				DS::uint32 err    = d2.getUint32();
				DS::uint64 qserial = d2.getUint64();
				if (err == DS::Error::OK) {
					int size = d2.getUint32();
					NVector cv(size);
					for (int q = 0; q < size; q++) {
						cv.v[q] = d2.getDouble();						
					}
					double dres = d2.getDouble();
					// Поместить данные в кэш
					cacheValue(cv, dres);
				}
			} else {
				_metaScheduler->waitForCompleteQueueIsNotEmpty();
			}
		}
	}

	void cacheValue(NVector const &val, double r) {
		map<NVector, double>::iterator f = _solved.find(val);
		_iterationsCount++;
		if (f == _solved.end())	{
			_solved.insert(LatticePair(val, r));
		}	else {
			_hashHits++;
		}
	}

	double getCachedValue(NVector const &val) {
		map<NVector, double>::iterator f = _solved.find(val);
		if (f == _solved.end()) {
			return GOOGOL;
		} else {
			return f->second;
		}
	}

	void clearCache() {
		_solved.clear();
	}

	static double random(double l, double r) {
		double x = (double)rand() / (double)RAND_MAX;
		return l + x * (r-l);
	}

	NVector calcParametric(NVector const &startPoint, NVector const &direction, double t) {
		NVector delta = direction;
		delta *= t;
		NVector x1 = startPoint;
		x1 += delta;
		return x1;
	}

	void getRandomScaledPoint(vector<Param> const &params, NVector &normalizedPoint, NVector &scaledPoint) {
		NVector p(SIZE);
		for (int k = 0; k < SIZE; k++) {
			p.v[k] = random(0., 1.);
			double d = random(-0.05, 0.05);
			p.v[k] += d;
			if (p.v[k] < 0.0) {
				p.v[k] = 0.0;
			}
			if (p.v[k] > 1.0) {
				p.v[k] = 1.0;
			}
		}
		NVector sp(SIZE); 
		sp.scale(p, params);
		scaledPoint = sp;
		normalizedPoint = p;
	}

	NVector differentialEvolutionNew(vector<Param> params, int pointsCount, 
		string const &tf, double delta, double eps, double &result)
	{
		FILE *log = NULL;
		if (_logFileName.size() > 0) {
			log = fopen(_logFileName.c_str(), "a");
		}
		if (log != NULL) {
			fprintf(log, "differentialEvolution par=");
			printf("differentialEvolution par=");
			for (size_t p = 0; p < params.size(); p++) {
				fprintf(log,"%s ", params[p].str().c_str());
				printf("%s ", params[p].str().c_str());
			}
			fprintf(log, "\n");
			printf("\n");
			fflush(log);
		}
		NVector newCoords(SIZE);
		vector<bool> used;
		vector< NVector> scaledPoints;
		vector< NVector> normalizedPoints;
		for (int i = 0; i < pointsCount; i++) {
			NVector np(SIZE);
			NVector sp(SIZE);
			getRandomScaledPoint(params,np, sp);
			scaledPoints.push_back(sp);
			normalizedPoints.push_back(np);
			used.push_back(false);
		}
		NVector optVal = scaledPoints[0];

		double crossoverProbability = 0.7;
		double differentialWeight = 0.5;

		clearCache();
		set<DS::uint64> pending;
		for (int i = 0; i < pointsCount; i++) {
			DS::uint64 sc = schedule(scaledPoints[i], tf, log);
			if (sc > 0)	{
				pending.insert(sc);
			}
		}

		waitForPendingItems(pending, log);

		double globalBest = GOOGOL;
		int bestIndex = -1;
		for (int i = 0; i < pointsCount; i++) {
			double red = getCachedValue(scaledPoints[i]);
			if (red < globalBest) {
				globalBest = red;
				bestIndex = (int)i;
			}
		}

		int iterationsCount = 300;
		int evaluationsCount = 0;
		double lastGlobalBest = globalBest;
		NVector lastBestScaledPoint = scaledPoints[bestIndex];
		double bestDeltas = 0;
		bool done = false;
		for(int iteration = 0; iteration < iterationsCount && !done; iteration++) {
			if ((iterationsCount + 1) % 100 == 0) {
				printf("Iter=%d\r", iteration); fflush(stdout);
			}

#ifdef GRAPHICS_CLIENT
			gc.FillViewportArea(GraphicsClient::makeColor(255,255,255));
			{
				vector<double> x;
				vector<double> y;
				for (int i = 0; i < pointsCount; i++)
				{
					x.push_back(scaledPoints[i].v[0]);
					y.push_back(scaledPoints[i].v[1]);
				}
				gc.Markers(GraphicsClient::makeColor(0,0,0), 1, x, y);
			}
			gc.Refresh();
#endif
			double dist = NVector::diameter(scaledPoints);

			if (do_print & PRINT_POINTS) {
				if (log != NULL) {
					fprintf(log,"Current estimation: diameter=%g\n", dist);
				}
//				if (do_print & PRINT_VALUES) {
//					for (int i = 0; i < pointsCount; i++) {
//						fprintf(log, "p[%d]=%s val=%g\n", i, scaledPoints[i].str().c_str(), getCachedValue(scaledPoints[i]));
//						printf("p[%d]=%s val=%g\n", i, scaledPoints[i].str().c_str(), getCachedValue(scaledPoints[i]));
//						fflush(log);
//					}
//				}
				printf("Current estimation: diameter=%g\n", dist);
			}
			vector <set<int> > zones = NVector::findConsensusZones(scaledPoints, delta);
			vector<double> zonesMinimum(zones.size());

			int zoneContainedMin = -1;
			double reachedMin = GOOGOL;
			for (int i = 0; i < (int)zones.size(); i++) {
				double zoneMinValue = GOOGOL;
				set<int> s = zones[i];
				for (set<int>::const_iterator si = s.begin(); si != s.end(); si++) {
					int pointNo = *si;
					double pointVal = getCachedValue(scaledPoints[pointNo]);
					if (pointVal < zoneMinValue) {
						zoneMinValue = pointVal;
					}
				}
//				if (s.size() > 0) {
//					if (do_print & PRINT_DEBUG_ZONES) {
//						printf("minimum of zone %d(%lu points) = %g\n", i, s.size(), zoneMinValue); 
//						fprintf(log, "minimum of zone %d(%lu points) = %g\n", i, s.size(), zoneMinValue); 
//					}
//				}
				zonesMinimum[i] = zoneMinValue;
				if (zoneMinValue < reachedMin) {
					zoneContainedMin = i;
					reachedMin = zoneMinValue;
				}
			}
            printf("iter=%d of %d reached min now=%g\n", iteration, iterationsCount, reachedMin);
			if (do_print & PRINT_DEBUG_ZONES) {
				if (zones[zoneContainedMin].size() > 1) {
					printf("Zone %d contains %lu points and global minimum %g\n", zoneContainedMin, zones[zoneContainedMin].size(), reachedMin);
					fprintf(log, "Zone %d contains %lu points and global minimum %g\n", zoneContainedMin, zones[zoneContainedMin].size(), reachedMin);
				}
			}
			if (reachedMin < eps) { 
				done = true;
				break;
			}
			vector<bool> probesMinExists(zones.size());
			vector<NVector> probesMinPoints(zones.size());
			pending.clear();

			for (int i = 0; i < (int)zones.size(); i++)	{
				if (probesMinExists[i])	{
					DS::uint64 sc = schedule(probesMinPoints[i], tf,log);
					if (sc > 0)	{
						pending.insert(sc);
					}
				}
			}
			vector<NVector> normalizedProbePoints;
			int indices[4];

			for(int pointIndex = 0; pointIndex < pointsCount && !done; pointIndex++) {
				int bestIndex = 0;
				for(int i = 0; i < pointsCount; i++) {
					if(getCachedValue(scaledPoints[i])  < getCachedValue(scaledPoints[bestIndex])) {
						bestIndex = i;
					}
				}

				used[pointIndex] = true;
				for(int currIndex = 0; currIndex < 4; currIndex++) {
					indices[currIndex] = rand() % pointsCount;
					while(used[indices[currIndex]]) {
						indices[currIndex] = (indices[currIndex] + 1) % pointsCount;
					}
					used[indices[currIndex]] = true;
				}

				NVector newNormalizedCoords(SIZE);
				int crossoverCoord = rand() % SIZE;
				for(int coordIndex = 0; coordIndex < SIZE; coordIndex++) {
					if((crossoverCoord == coordIndex) || (random(0.0, 1.0) < crossoverProbability)) {
						newNormalizedCoords.v[coordIndex] = normalizedPoints[pointIndex].v[coordIndex];
						newNormalizedCoords.v[coordIndex] += differentialWeight * (normalizedPoints[indices[0]].v[coordIndex] - normalizedPoints[indices[1]].v[coordIndex]);
						newNormalizedCoords.v[coordIndex] += differentialWeight * (normalizedPoints[bestIndex ].v[coordIndex] - normalizedPoints[pointIndex].v[coordIndex]);
					} else {
						newNormalizedCoords.v[coordIndex] = normalizedPoints[pointIndex].v[coordIndex];
					}
					if(newNormalizedCoords.v[coordIndex] < 0.0) newNormalizedCoords.v[coordIndex] = 0.0;
					if(newNormalizedCoords.v[coordIndex] > 1.0) newNormalizedCoords.v[coordIndex] = 1.0;
				}
				NVector newCoords(SIZE); newCoords.scale(newNormalizedCoords, params);
				normalizedProbePoints.push_back(newNormalizedCoords);
				DS::uint64 sc = schedule(newCoords, tf,log);
				if (sc > 0) {
					pending.insert(sc);
				}
				for(int currIndex = 0; currIndex < 4; currIndex++) {
					used[indices[currIndex]] = false;
				}
				used[pointIndex] = false;
			}
			waitForPendingItems(pending, log);
			for (int i = 0; i < (int)zones.size(); i++) {
				if (probesMinExists[i]) {
					double cv = getCachedValue(probesMinPoints[i]);
					double worstValue = -GOOGOL;
					double bestValue = GOOGOL;
					int bestPoint = -1;
					int    worstPoint = -1;
					for (set<int>::iterator it = zones[i].begin(); it != zones[i].end(); it++) {
						int k = *it;
						NVector saved = scaledPoints[k];
						double v = getCachedValue(saved);
						if (v > worstValue) {
							worstValue = v;
							worstPoint = k;
						}
						if (v < bestValue) {
							bestValue = v;
							bestPoint = k;
						}
					}
					if (cv < bestValue) {
						scaledPoints[worstPoint] = probesMinPoints[i];
						normalizedPoints[worstPoint].reverseScale(scaledPoints[worstPoint], params);
					}
				}
			}

			for(int pointIndex = 0; pointIndex < pointsCount && !done; pointIndex++) {
				NVector newNormalizedCoords = normalizedProbePoints[pointIndex];
				NVector newCoords(SIZE); newCoords.scale(newNormalizedCoords, params);
				double value = getCachedValue(newCoords);
				double valueOfScalePointsOfPointIndex = getCachedValue(scaledPoints[pointIndex]);
				if(value < valueOfScalePointsOfPointIndex) {
					if (log != NULL) {
						if (do_print & PRINT_POINTS) {
							fprintf(log, "New best value on point %d %s: %g (old was %g)\n", pointIndex, newCoords.str().c_str(), value, valueOfScalePointsOfPointIndex);
							printf("New best value on point %d %s: %g (old was %g)\n", pointIndex, newCoords.str().c_str(), value, valueOfScalePointsOfPointIndex);
							fflush(log);
						}
					}
					normalizedPoints[pointIndex] = newNormalizedCoords;
					scaledPoints[pointIndex].scale(normalizedPoints[pointIndex], params);
				}

				if(value < globalBest) {
					if (log != NULL) {
						if (do_print & PRINT_VALUES) {
							fprintf(log, "++ New globalbest reached: %g (was %g)\n", value, globalBest);
							printf("++ New globalbest reached: %g (was %g)\n", value, globalBest);
						}
						fflush(log);
					}
					globalBest = value;
					lastBestScaledPoint = newNormalizedCoords;
				}

			}
			if (dist < delta) {
				if (log != NULL) {
					fprintf(log, "++ Diameter %g reached\n", dist);
					fflush(log);
					printf("++ Diameter %g reached\n", dist);
				}
				done = true;
				break;
			}
			lastGlobalBest = globalBest;
		}

		bestIndex = 0;
		globalBest = getCachedValue(scaledPoints[bestIndex]);;
		for(int pointIndex = 0; pointIndex < pointsCount; pointIndex++) {
			if(getCachedValue(scaledPoints[pointIndex]) < globalBest) {
				globalBest = getCachedValue(scaledPoints[pointIndex]);
				bestIndex = pointIndex;
			}		
		}
		optVal = scaledPoints[bestIndex];
		result = globalBest;
		if (log != NULL) {
			fclose(log);
		}
        printf("Best value at %s is %g\n", optVal.str().c_str(), result);
		return optVal;
	}

	void setLog( const char *param1 )  {
		_logFileName = param1;
	}

	typedef pair<NVector, double> LatticePair;
};

int meta_main(int size, MetaControlServer &dsm, 
			  string const &tf, NVector const &start, NVector const &end, int points, double diam)
{
	ProblemServer l(size, dsm.getMetaScheduler());
#ifdef GRAPHICS_CLIENT
	gc.SetViewportArea(start.v[0], start.v[1], end.v[0], end.v[1]); // 2D only 
#endif

	l.setLog("log.log");
	vector<Param> params;
	for (int i = 0; i < size; i++) {
		Param p;
		p.init(start.v[i], end.v[i], (start.v[i]+end.v[i])/2.0);
		params.push_back(p);
	}
	double result;
	NVector p;
	p = l.differentialEvolutionNew(params, points, tf, diam, 1e-5, result);
	return 0;	
}

int
main(int argc, char **argv)
{
	try
	{
		typedef int (*executor)(void *);
		MetaControlServer   dsm;
		unsigned s0 = (unsigned)::time(NULL);
		double diam = 0.00001;
		string tf = "adsorb_calculate";
		if (argc > 1) {
			diam = atof(argv[1]);
		}
		if (argc > 2) {
			tf = argv[2];
		}

		srand(s0);
		dsm.commandStartServer();
		dsm.metaStart();
#ifdef GRAPHICS_CLIENT
		string gserverIP = "127.0.0.1";
		if (argc > 3) {
			gserverIP = argv[3];
		}
		try
		{
			gc.connectToServer("127.0.0.1");
		} catch (DS::Exception const &e)
		{
			printf("Graphics is not available\n");
		}
		NVector start(2);
		NVector end(2);
		start.v[0] = -10; end.v[0] = 10;
		start.v[1] = -10; end.v[1] = 10;
		//		start.v[8] = 0; end.v[8] = 3;
		//		start.v[9] = 0; end.v[9] = 1;
		//		start.v[10] = 0; end.v[10] = 2;
		meta_main(2, dsm, tf, start, end, 64, 0.001);
#else
		//do_print = 0; // PRINT_ZONES;
		do_print =  0xFF; // PRINT_POINTS | PRINT_ZONES | PRINT_VALUES | PRINT_SCHEDULE | PRINT_DEBUG_ZONES | PRINT_DEBUG;
		NVector start(8 );
		NVector end(8 );
		start.v[0] = 0; end.v[0] = 1E-6;
		start.v[1] = 0; end.v[1] = 1E-4;
		start.v[2] = 0; end.v[2] = 4E-4;
		start.v[3] = 0; end.v[3] = 1E-2;
		start.v[4] = 0; end.v[4] = 2E-3;
		start.v[5] = 0; end.v[5] = 1E-4;
		start.v[6] = 0; end.v[6] = 2E-2;
		start.v[7] = 0; end.v[7] = 2E-2;
//		start.v[8] = 0; end.v[8] = 3;
//		start.v[9] = 0; end.v[9] = 1;
//		start.v[10] = 0; end.v[10] = 2;
		meta_main(8, dsm, tf, start, end, 32, diam);
#endif
		cout << "Program ended" << endl;
		return 0;
	}
	catch (const char *s) {
		printf("Caught %s\n", s);
	}
}
