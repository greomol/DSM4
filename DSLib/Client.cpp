#include "Client.h"
#include "Error.h"
#include "TransportConnectionTCPClient.h"
#include "PacketHeader.h"

namespace DS {

Client::Client(void)
{
    conn = NULL;
	_timestamp = 0;
}

Client::~Client(void)
{
}

uint32 
Client::connect(string const &name, string const &resource)
{
    if (conn != NULL)
    {
        return Error::ResourceInUse;
    }
    conn = new TransportConnectionTCPClient(name, resource);
    return Error::OK;
    
}

uint32 
Client::disconnect(string const & /*name*/)
{
    if (conn == NULL)
    {
        return Error::ObjectIsNULL;
    }
    conn->close();
    delete conn;
    conn = NULL;
    return Error::OK;
}

uint32 
Client::call( string const &name, Serializer const &ser, Deserializer &des )
{
	try
	{
		if (conn == NULL)
		{
			return Error::NotConnected;
		}
		Serializer ip;
		ip.putString(name);
		ip.putSerializer(ser);
		PacketHeader ph(ip.size(), 0, 0, _timestamp);
		_timestamp++;
		bytevector phb = ph.serialize();
		SerializerRaw op;
		// byte *inputBuffer = NULL;
		op.putBytevector(&phb[0], phb.size());
		op.putBytevector(ip, ip.size());
		uint32 wr = conn->write(op, op.size()); wr = wr;
		int rd;
		// Читаем результат
		byte header[PacketHeader::size];
		if ((rd = conn->read(header, PacketHeader::size)) != (int)PacketHeader::size)
		{
			// Ошибка чтения, завершаем работу с сервером?
			fprintf(stderr, "Client:call: got %d bytes instead of %u\n", rd, PacketHeader::size);
			return Error::PrematureEndOfStream;
		}
		PacketHeader hdr(header, PacketHeader::size);
		const int MAX_BODY_SIZE = 65536*2;
		if (hdr.isValid())
		{
			// Считываем пакет с информацией (в зависимости от флагов!)
			if (hdr.length > MAX_BODY_SIZE)
			{
				return Error::SizeTooBig;
			}
			byte *inputBuffer = new byte[hdr.length];
			if (inputBuffer == NULL)
			{
				return Error::SizeTooBig;                      
			}
			uint32 readSize = conn->read(inputBuffer, hdr.length);
			if (readSize != hdr.length)
			{
				return Error::PrematureEndOfStream;
			}
			if (hdr.flags != 0)
			{
				delete [] inputBuffer;
				return Error::YetNotImplemented;
			}
			if (hdr.timestamp + 1 > _timestamp) {
				_timestamp = hdr.timestamp + 1;
			}
			//printf("Client timestamp = %d\n", _timestamp);
	//        fprintf(stderr,"Client::call: read %u bytes\n", hdr.length);
			// Забираем серию
			des.refill(inputBuffer, hdr.length);
			delete [] inputBuffer;
		}
		return Error::OK;
	} catch (Exception const &e)
	{
		return e.getCode();
	}
}

} // end of namespace DS;
