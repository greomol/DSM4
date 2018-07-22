#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <assert.h>
#include <time.h>

#include <vector>
using namespace std;

#include "GraphicsClient.h"
#include "Thread.h"
using namespace DS;

#include <iostream>
using namespace std;

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

GraphicsClient::GraphicsClient()
{
	_client = NULL;
}

GraphicsClient::~GraphicsClient()
{
}

DS::uint32 
GraphicsClient::connectToServer(string const &serverName)
{
	_client = new DS::Client();
	_client->connect(serverName, "5556");
	return DS::Error::OK;
}

DS::uint32 
GraphicsClient::disconnectFromServer(string const &serverName)
{
	_client->disconnect(serverName);
	delete _client;
	return DS::Error::OK;
}

DS::uint32 
GraphicsClient::SetViewportArea(double startx, double starty, double endx, double endy)
{
	DS::Serializer ser;
	DS::Deserializer des;
	DS::uint32 res = DS::Error::OK;
	try
	{
		ser.putInt32(doubleToFractionalInt(startx));
		ser.putInt32(doubleToFractionalInt(starty));
		ser.putInt32(doubleToFractionalInt(endx));
		ser.putInt32(doubleToFractionalInt(endy));
		res = _client->call("SetViewportArea", ser, des);
		if (res == DS::Error::OK)
		{
			res = des.getUint32();
		}
	}
	catch (Exception const &ex)
	{
		res = ex.getCode();
	}
	return res;
}

DS::uint32 
GraphicsClient::FillViewportArea(DS::uint32 color)
{
	DS::Serializer ser;
	DS::Deserializer des;
	DS::uint32 res = DS::Error::OK;
	try
	{
		ser.putUint32(color);
		res = _client->call("FillViewportArea", ser, des);
		if (res == DS::Error::OK)
		{
			res = des.getUint32();
		}
//		cout << "Call FillViewportArea = " << res << endl;
	}
	catch (Exception const &ex)
	{
		res = ex.getCode();
	}
	return res;
}


DS::uint32 
GraphicsClient::SetScale(double scalex, double scaley)
{
	DS::Serializer ser;
	DS::Deserializer des;
	DS::uint32 res = DS::Error::OK;
	try
	{
		ser.putUint32(doubleToFractionalInt(scalex));
		ser.putUint32(doubleToFractionalInt(scaley));
		DS::uint32 res = _client->call("SetScale", ser, des);
		if (res == DS::Error::OK)
		{
			res = des.getUint32();
		}
	}
	catch (Exception const &ex)
	{
		res = ex.getCode();
	}
	return res;
}

DS::uint32 
GraphicsClient::Refresh()
{
	DS::Serializer ser;
	DS::Deserializer des;
	DS::uint32 res = DS::Error::OK;
	try
	{
		ser.putUint32(0);
		res = _client->call("Refresh", ser, des);
		if (res == DS::Error::OK)
		{
			res = des.getUint32();
		}
	}
	catch (Exception const &ex)
	{
		res = ex.getCode();
	}
	return res;
}

DS::uint32 
GraphicsClient::Line(DS::uint32 color, double startx, double starty, double endx, double endy)
{
	DS::Serializer ser;
	DS::Deserializer des;
	DS::uint32 res = DS::Error::OK;
	try
	{
		ser.putUint32(doubleToFractionalInt(color));
		ser.putInt32(doubleToFractionalInt(startx));
		ser.putInt32(doubleToFractionalInt(starty));
		ser.putInt32(doubleToFractionalInt(endx));
		ser.putInt32(doubleToFractionalInt(endy));
		DS::uint32 res = _client->call("Line", ser, des);
		if (res == DS::Error::OK)
		{
			res = des.getUint32();
		}
	}
	catch (Exception const &ex)
	{
		res = ex.getCode();
	}
	return res;
}

int GraphicsClient::doubleToFractionalInt(double x)
{
	return (int)(x * 1000. + (x > 0 ? 0.5 : -0.5));
}

DS::uint32 GraphicsClient::Marker(DS::uint32 color, DS::uint32 markerNo, double x, double y)
{
	DS::Serializer ser;
	DS::Deserializer des;
	DS::uint32 res = DS::Error::OK;
	try
	{
		ser.putUint32(color);
		ser.putUint32(markerNo);
		ser.putInt32(doubleToFractionalInt(x));
		ser.putInt32(doubleToFractionalInt(y));
		DS::uint32 res = _client->call("Marker", ser, des);
		if (res == DS::Error::OK)
		{
			res = des.getUint32();
		}
	}
	catch (Exception const &ex)
	{
		res = ex.getCode();
	}
	return res;
}

DS::uint32 GraphicsClient::Markers(DS::uint32 color, DS::uint32 markerNo, vector<double> x, vector<double> y)
{
	DS::Serializer ser;
	DS::Deserializer des;
	DS::uint32 res = DS::Error::OK;
	try
	{
		ser.putUint32(color);
		ser.putUint32(markerNo);
		DS::uint32 n = x.size() < y.size() ? x.size() : y.size();
		ser.putUint32(n);
		for (DS::uint32 i = 0; i < n; i++)
		{
			ser.putInt32(doubleToFractionalInt(x[i]));
			ser.putInt32(doubleToFractionalInt(y[i]));
		}
		DS::uint32 res = _client->call("Markers", ser, des);
		if (res == DS::Error::OK)
		{
			res = des.getUint32();
		}
	}
	catch (Exception const &ex)
	{
		res = ex.getCode();
	}
	return res;
}

DS::uint32 GraphicsClient::makeColor(int r, int g, int b)
{
	DS::uint32 ret = ((unsigned)b << 16) | ((unsigned)g << 8) | r;
	return ret;
}
