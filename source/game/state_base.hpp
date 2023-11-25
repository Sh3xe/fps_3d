#pragma once

#include "application.hpp"

class State
{
public:
	State( Application *app ): m_app(app) {}
	~State() {}

	virtual void on_update( float s_dt ) = 0;
	virtual void on_create() = 0;
	virtual void on_shutdown() = 0;

protected:
	Application *m_app;
	bool m_should_close = false;
};