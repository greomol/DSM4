all: metaserv meta rosenbroke

clear:
	-rm -f metaserv meta rosenbroke
	-rm $(SERVEROBJS)
	-rm $(CLIENTOBJS)
	-rm -f metaserv meta
	-cd RosenbrokeDir; make clear

SERVEROBJS = ProblemMain.o \
       MetaControlServer/MetaControlServer.o \
       MetaControlServer/MetaServer.o \
       MetaControlServer/MetaScheduler.o \
       MetaControlServer/MetaServerContext.o \
       MetaControlServer/MetaQueueItem.o \
       MetaControlServer/MetaRPC.o \
       DSLib/ServerContext.o \
       DSLib/ExecutorHashTable.o \
       DSLib/CRC32.o \
       DSLib/TransportConnectionTCPServer.o \
       DSLib/TransportConnection.o \
       DSLib/TransportConnectionTCP.o \
       DSLib/NetworkAddress.o \
       DSLib/ServerClientContext.o \
       DSLib/PacketHeader.o \
       DSLib/Server.o 

CLIENTOBJS = AdsorbClient/MetaClient.o \
       AdsorbClient/main.o \
       DSLib/Client.o \
       DSLib/TransportConnection.o \
       DSLib/NetworkAddress.o \
       DSLib/TransportConnectionTCP.o \
       DSLib/PacketHeader.o \
       DSLib/TransportConnectionTCPClient.o

#i#MetaControlServer.o: MetaControlServer.cpp
#	c++ -I ../DSLib MetaCon

clean:
	rm $(SERVEROBJS) $(CLIENTOBJS) rosenbroke metaserv meta

CPPFLAGS = -I DSLib -I MetaControlServer -I MetaClient -O

rosenbroke:
	cd RosenbrokeDir; make && cp rosenbroke ..

metaserv: $(SERVEROBJS)
	c++ -o metaserv $(SERVEROBJS) -lpthread

meta: $(CLIENTOBJS)
	c++ -o meta $(CLIENTOBJS) -lpthread



