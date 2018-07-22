#ifndef _SERIALIZER_H_ 
#define _SERIALIZER_H_ 1

#include <memory.h>
#include "Exception.h"
#include <vector>
#include <stdio.h>

namespace DS {
// Часть реализации сериализатора/десериализатора
class SerialTypes 
{
public:
  enum type 
  {
    NoneType,
    CharType,
    WcharType,
    ByteType,
    StringType,
    WstringType,
    Int32Type, 
    Uint32Type,
    Int64Type,
	Uint64Type,
    BytevectorType,
    SerializerType,
	DoubleType,
    // ...
    EndOfFile // Полезно для определения границы данных в буфере
    
  };
};

class Serializer 
{
public:
    Serializer()
    {

    }

    void putInt32(int32 q) 
    {
        buf.push_back((byte)SerialTypes::Int32Type); // типа int32
        buf.push_back((byte)(q & 0xFF)); // Младший байт 
        buf.push_back((byte)((q >> 8) & 0xFF));
        buf.push_back((byte)((q >> 16) & 0xFF));
        buf.push_back((byte)((q >> 24) & 0xFF));
    }

    void putUint32(uint32 q) 
    {
        buf.push_back((byte)SerialTypes::Uint32Type); // типа uint32
        buf.push_back((byte)(q & 0xFF)); // Младший байт 
        buf.push_back((byte)((q >> 8) & 0xFF));
        buf.push_back((byte)((q >> 16) & 0xFF));
        buf.push_back((byte)((q >> 24) & 0xFF));
    }

	void putUint64(uint64 q) 
    {
        buf.push_back((byte)SerialTypes::Uint64Type); // типа uint64
        buf.push_back((byte)(q & 0xFF)); // Младший байт 
        buf.push_back((byte)((q >> 8) & 0xFF));
        buf.push_back((byte)((q >> 16) & 0xFF));
        buf.push_back((byte)((q >> 24) & 0xFF));
		buf.push_back((byte)((q >> 32) & 0xFF));
		buf.push_back((byte)((q >> 40) & 0xFF));
		buf.push_back((byte)((q >> 48) & 0xFF));
		buf.push_back((byte)((q >> 56) & 0xFF));
    }

    void putString(string const &s)
    {
        buf.push_back((byte)SerialTypes::StringType);
        for (size_t i = 0; i < s.size(); i++)
        {
            buf.push_back((byte)s[i]);
        }
        buf.push_back((byte)0);
    }

    void putBytevector(const byte *b, uint32 size)
    {
        buf.push_back((byte)SerialTypes::BytevectorType);
        for (size_t i = 0; i < size; i++)
        {
            buf.push_back((byte)b[i]);
        }
    }

    void putSerializer(Serializer const &ser)
    {
        buf.push_back((byte)SerialTypes::SerializerType);
        uint32 q = ser.size();
        buf.push_back((byte)(q & 0xFF)); // Младший байт 
        buf.push_back((byte)((q >> 8) & 0xFF));
        buf.push_back((byte)((q >> 16) & 0xFF));
        buf.push_back((byte)((q >> 24) & 0xFF));
        for (size_t i = 0; i < ser.buf.size(); i++)
        {
            buf.push_back((byte)ser.buf[i]);
        }
    }

	void putDouble(double val)
	{
		buf.push_back((byte)SerialTypes::DoubleType);
		const byte *b = (const byte *)&val;
		for (size_t i = 0; i < 8; i++)
		{
			buf.push_back((byte)b[i]);
		}
	}

    operator const byte *() const
    {
        return buf.size() > 0 ? &buf[0] : (const byte *)"";
    }

    bytevector get()  const
    {
        return buf;
    }

    uint32 size() const
    {
        return buf.size();
    }

    void clear() 
    {
        buf.clear();
    }
private:
    bytevector buf;
};

class SerializerRaw
{
public:
    SerializerRaw()
    {

    }

    void putInt32(int32 q) 
    {
        buf.push_back((byte)(q & 0xFF)); // Младший байт 
        buf.push_back((byte)((q >> 8) & 0xFF));
        buf.push_back((byte)((q >> 16) & 0xFF));
        buf.push_back((byte)((q >> 24) & 0xFF));
    }

    void putUint32(uint32 q) 
    {
        buf.push_back((byte)(q & 0xFF)); // Младший байт 
        buf.push_back((byte)((q >> 8) & 0xFF));
        buf.push_back((byte)((q >> 16) & 0xFF));
        buf.push_back((byte)((q >> 24) & 0xFF));
    }

	void putUint64(uint64 q) 
    {
        // Увы, на процессорах Intel сдвижка на 40 разрядов сдвигает на 8 
        union {
            uint32 i32[2];
            uint64 i64;
        } u;
        u.i64 = q;
        putUint32(u.i32[0]);
        putUint32(u.i32[1]);
    }

    void putString(string const &s)
    {
        for (size_t i = 0; i < s.size(); i++)
        {
            buf.push_back((byte)s[i]);
        }
        buf.push_back((byte)0);
    }

    void putSerializer(Serializer const &ser)
    {
        const byte *b = (const byte *)(const void *)ser;
        putUint32(ser.size());
        for (size_t i = 0; i < ser.size(); i++)
        {
            buf.push_back((byte)b[i]);
        }
    }

    void putBytevector(const byte *b, uint32 size)
    {
        for (size_t i = 0; i < size; i++)
        {
            buf.push_back((byte)b[i]);
        }
    }

	void putDouble(double val)
	{
		const byte *b = (const byte *)&val;
		for (size_t i = 0; i < 8; i++)
		{
			buf.push_back((byte)b[i]);
		}
	}

    bytevector get()  const
    {
        return buf;
    }

    operator const void *() const
    {
        return buf.size() > 0 ? &buf[0] : (const byte *)"";
    }

    uint32 size() const
    {
        return buf.size();
    }

    void clear() 
    {
        buf.clear();
    }

private:
    bytevector buf;
};

class Deserializer;

class DeserializerRaw 
{
public:
    void refill(byte const *v, uint32 size)
    {
        ptr = 0;
        buf.resize(size);
        if (size > 0)
        {
            ::memcpy(&buf[0], v, size);
        }
    }

    DeserializerRaw(bytevector const &v) 
    { 
        refill(&v[0], v.size());
    }

    ~DeserializerRaw()
    {
    }
 
    DeserializerRaw(byte const *v = NULL, uint32 _size = 0) 
    { // v - нечто, что было сериализовано
        buf.clear();
        refill(v, _size);
    }

    int32 getInt32() const
    { // Получаем число в нужном порядке байт
        if (ptr+4 > buf.size())
            throw Exception(Error::ReadAttemptOutOfBounds,
            "Deserializer.getInt32");
        int32 ret = buf[ptr++];
        ret |= (buf[ptr++] << 8);
        ret |= (buf[ptr++] << 16);
        ret |= (buf[ptr++] << 24);
        return ret;
    }

    uint32 getUint32() const
    { // Получаем число в нужном порядке байт
        if (ptr+4 > buf.size())
            throw Exception(Error::ReadAttemptOutOfBounds,
            "Deserializer.getUint32");
        uint32 ret = buf[ptr++];
        ret |= (buf[ptr++] << 8);
        ret |= (buf[ptr++] << 16);
        ret |= (buf[ptr++] << 24);
        return ret;
    }

	uint64 getUint64() const
    { // Получаем число в нужном порядке байт
        if (ptr+8 > buf.size())
            throw Exception(Error::ReadAttemptOutOfBounds,
            "Deserializer.getUint64");
         union {
            uint32 i32[2];
            uint64 i64;
         } u;
         u.i32[0] = getUint32();
         u.i32[1] = getUint32();
         return u.i64;
    } 

    string getString() const
    {
        string ret;
        while (ptr < buf.size() && buf[ptr] != 0)
        {
            ret.push_back(buf[ptr]);
            ptr++;
        }
        if (ptr >= buf.size())
        {
            throw Exception(Error::ReadAttemptOutOfBounds,
                "Deserializer.getString");
        }
        ptr++; // trailing 0
        return ret;
    }

	double getDouble() const
	{ 
		// Wrong code, works ONLY on homogenous architectures, TODO
		if (ptr+8 > buf.size())
			throw Exception(Error::ReadAttemptOutOfBounds,
			"Deserializer.getUint32");
		double ret;
		byte *b = (byte *)&ret;
		*b++ = buf[ptr++];
		*b++ = buf[ptr++];
		*b++ = buf[ptr++];
		*b++ = buf[ptr++];
		*b++ = buf[ptr++];
		*b++ = buf[ptr++];
		*b++ = buf[ptr++];
		*b   = buf[ptr++];
		return ret;
	}
    inline void getDeserializer(Deserializer &d) const; 

protected:
    vector<byte> buf;
    mutable uint32 ptr;
};


class Deserializer : public DeserializerRaw 
{
public:
  Deserializer(bytevector const &v) :  DeserializerRaw(v)
  { 
  }

  Deserializer(byte const *v = NULL, uint32 size = 0) : DeserializerRaw(v, size) 
  { 
  }

  int32 getInt32() const
  { // Получаем число в нужном порядке байт
    if (ptr+5 > buf.size())
      throw Exception(Error::ReadAttemptOutOfBounds,
        "Deserializer.getInt32");
    if (buf[ptr] != SerialTypes::Int32Type)
      throw Exception(Error::NotExpectedType,
        "Deserializer.getInt32");
    ptr++;
    return DeserializerRaw::getInt32();
  }

  uint32 getUint32() const
  { // Получаем число в нужном порядке байт
      if (ptr+5 > buf.size())
          throw Exception(Error::ReadAttemptOutOfBounds,
          "Deserializer.getUint32");
      if (buf[ptr] != SerialTypes::Uint32Type) {
		  printf("%d", buf[ptr]);
          throw Exception(Error::NotExpectedType,
			  "Deserializer.getInt32"); }
      ptr++;
      return DeserializerRaw::getUint32();
  }

  uint64 getUint64() const
  { // Получаем число в нужном порядке байт
      if (ptr+9 > buf.size())
          throw Exception(Error::ReadAttemptOutOfBounds,
          "Deserializer.getUint64");
      if (buf[ptr] != SerialTypes::Uint64Type) {
		  printf("%d", buf[ptr]);
          throw Exception(Error::NotExpectedType,
			  "Deserializer.getUint64"); }
      ptr++;
      return DeserializerRaw::getUint64();
  }

  string getString() const
  {
      if (buf[ptr] != SerialTypes::StringType)
          throw Exception(Error::NotExpectedType,
          "Deserializer.getString");
      ptr++;
      return DeserializerRaw::getString();
  }

  double getDouble() const
  {
	  if (buf[ptr] != SerialTypes::DoubleType)
		  throw Exception(Error::NotExpectedType,
		  "Deserializer.getDouble");
	  ptr++;
	  return DeserializerRaw::getDouble();
  }

  void getDeserializer(Deserializer &arg) const
  {
      if (buf[ptr] != SerialTypes::SerializerType)
          throw Exception(Error::NotExpectedType,
          "Deserializer.getDeserializer");
      ptr++;
      DeserializerRaw::getDeserializer(arg);
  }

  SerialTypes::type peekType() const
  {                             // Определить тип очередного значения 
                                // в буфере, не продвигая ptr
    if (ptr >= buf.size()) 
      throw Exception(Error::ReadAttemptOutOfBounds,
       "Deserializer.peekType");
      return (SerialTypes::type)(buf[ptr]);
  }
};

void
DeserializerRaw::getDeserializer(Deserializer &d) const
{
    uint32 q = getUint32();
    if (ptr + q <= buf.size())
    {
		d.refill(q == 0 ? NULL : &buf[ptr], q);
        ptr += q;
    }
    else
    {
        throw Exception(Error::ReadAttemptOutOfBounds,
            "Deserializer.getDeserializer");
    }
}


} // end of namespace

#endif
