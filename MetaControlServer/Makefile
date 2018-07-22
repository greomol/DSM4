all: metaserver

OBJS = MetaControlServer.o MetaServer.o MetaScheduler.o MetaServerContext.o MetaQueueItem.o \
       MetaRPC.o ../DSLib/ServerContext.o ../DSLib/ExecutorHashTable.o ../DSLib/CRC32.o \
       ../DSLib/TransportConnectionTCPServer.o ../DSLib/TransportConnection.o \
       ../DSLib/TransportConnectionTCP.o ../DSLib/NetworkAddress.o \
       ../DSLib/ServerClientContext.o ../DSLib/PacketHeader.o \
       ../DSLib/Server.o 


#i#MetaControlServer.o: MetaControlServer.cpp
#	c++ -I ../DSLib MetaCon

CPPFLAGS = -I ../DSLib

metaserver: $(OBJS)
	c++ -o metaserver $(OBJS) -lpthread

