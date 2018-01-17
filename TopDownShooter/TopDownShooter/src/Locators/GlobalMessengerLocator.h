#pragma once

#include <Game\GlobalMessage.h>
#include <assert.h>

class GlobalMessenger;
class GlobalMessengerLocator
{
public:
	static void provide(GlobalMessenger& globalMessenger)
	{
		m_globalMessenger = &globalMessenger;
	}

	static GlobalMessenger& get()
	{
		assert(m_globalMessenger);
		return *m_globalMessenger;
	}

private:
	static GlobalMessenger* m_globalMessenger;
};