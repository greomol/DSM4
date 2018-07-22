#include "ServerClientContext.h"
#include "Error.h"
#include "PacketHeader.h"
#include "ServerContext.h"
#include "TransportConnection.h"
#include "ExecutorHashTable.h"

namespace DS {

ServerClientContext::ServerClientContext()
{
    inputBuffer = NULL;
    inputBufferUsed = 0;
    inputBufferAllocated = 0;
}

ServerClientContext::~ServerClientContext()
{
    if (inputBuffer != NULL)
    {
        delete inputBuffer;
        inputBuffer = NULL;
    }
}

uint32 ServerClientContext::serveRequest()
{
    outputResults.clear();
    Deserializer d(inputBuffer, inputBufferUsed);
    string name = d.getString();             // ��� ���� ��� ����������� ���������
    d.getDeserializer(inputArguments);       // ��� ���� ��������� ����������� ���������

	void *context;
    executorPtr f = serv->find(name, &context);
    if (f != NULL)
    {
//        fprintf(stderr, "Procedure '%s' is to be called\n", name.c_str());
        f(context, inputArguments, outputResults);
    }
    else
    {
        fprintf(stderr, "Procedure '%s' is not found\n", name.c_str());
    }
    return Error::OK;
}


uint32 ServerClientContext::readInput()
{
    int rd;
    if ((rd = conn->read(header, PacketHeader::size)) != (int)PacketHeader::size)
    {
        // ������ ������, ��������� ������ � ��������?
        fprintf(stderr, "ClientThread: got %d bytes instead of %u\n", rd, PacketHeader::size);
        return Error::PrematureEndOfStream;
    }
    PacketHeader hdr(header, PacketHeader::size);
    if (hdr.isValid())
    {
        // ��������� ����� � ����������� (� ����������� �� ������!)
        if (hdr.length > MAX_BODY_SIZE)
        {
            return Error::SizeTooBig;
        }
        if (hdr.length > inputBufferAllocated)
        {
            // ������ �������� ������������ ����� �����.
            if (inputBuffer != NULL)
            {
                delete inputBuffer;
                inputBuffer = NULL;
            }
            inputBuffer = new byte[hdr.length];
            if (inputBuffer == NULL)
            {
                return Error::SizeTooBig;                      
            }
            inputBufferAllocated = hdr.length;
        }
        // ����� � ��� ������� ����� ��� ������ ������������ ������� bodySize, �� ��� ����� hdr.size();
        uint32 readSize = conn->read(inputBuffer, hdr.length);
        if (readSize != hdr.length)
        {
            return Error::PrematureEndOfStream;
        }
        if (hdr.flags != 0)
        {
            return Error::YetNotImplemented;
        }
        inputBufferUsed = hdr.length;
		if (hdr.timestamp + 1 > serv->getTimestamp()) {
			serv->setTimestamp(hdr.timestamp + 1);
		}
		//printf("Server timestamp = %d\n", serv->getTimestamp());
        // ����� ������� ����������� ����� ������.
        // @@����� ��������� ��� crc32 
//        fprintf(stderr,"ClientThread: read %u bytes\n", inputBufferUsed);
    }
    return Error::OK;
}

uint32
ServerClientContext::sendResults()
{
	PacketHeader ph(outputResults.size(), 0, 0, serv->getTimestamp());
	serv->setTimestamp(serv->getTimestamp() + 1);
    bytevector phb = ph.serialize();
    SerializerRaw op;
    op.putBytevector(&phb[0], phb.size());
    op.putBytevector(outputResults, outputResults.size());
    uint32 wr = conn->write(op, op.size());
    return Error::OK;
}


} // End namespace DS

