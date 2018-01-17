#pragma once
#include <assert.h>

class StringToEnumConverter;
class StringToEnumConverterLocator
{
public:
	StringToEnumConverterLocator() {}
	StringToEnumConverterLocator(const StringToEnumConverterLocator&) = delete;
	StringToEnumConverterLocator& operator=(const StringToEnumConverterLocator&) = delete;
	StringToEnumConverterLocator(StringToEnumConverterLocator&&) = delete;
	StringToEnumConverterLocator&& operator=(StringToEnumConverterLocator&&) = delete;
	
	static void provide(StringToEnumConverter& stringToEnumConverter)
	{
		m_stringToEnumConverter = &stringToEnumConverter;
	}

	static StringToEnumConverter& get()
	{
		assert(m_stringToEnumConverter);
		return *m_stringToEnumConverter;
	}

private:
	static StringToEnumConverter* m_stringToEnumConverter;
};