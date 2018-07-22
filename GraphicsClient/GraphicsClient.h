#pragma once

#include "Client.h"
#include <string>
using namespace std;

class GraphicsClient
{
public:
    GraphicsClient();
    ~GraphicsClient();
	DS::uint32 connectToServer(string const &serverName);
	DS::uint32 disconnectFromServer(string const &serverName);

	DS::uint32 SetViewportArea(double startx, double starty, double endx, double endy);
	DS::uint32 FillViewportArea(DS::uint32 color);
	DS::uint32 SetScale(double scalex, double scaley);  
	DS::uint32 Refresh();
	DS::uint32 Line(DS::uint32 color, double startx, double starty, double endx, double endy);
	DS::uint32 Marker(DS::uint32 color, DS::uint32 markerNo, double x, double y);
	DS::uint32 Markers(DS::uint32 color, DS::uint32 markerNo, vector<double> x, vector<double> y);
	static DS::uint32 makeColor(int r, int g, int b);
private:
	DS::Client *_client;
	int  doubleToFractionalInt(double x); // in 1000-th : 1000 = 1, 1500 = 1.5 e.t.c
};
